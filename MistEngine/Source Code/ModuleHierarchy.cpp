#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"

#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"

ModuleHierarchy::ModuleHierarchy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	roots = nullptr;
	TargetDropped = nullptr;
	objSelected = nullptr;
}

ModuleHierarchy::~ModuleHierarchy()
{}

 //-----------------------------------------------------------------
bool ModuleHierarchy::Start()
{
	//LOG("Setting up the hierarchy");
	bool ret = true;

	roots = new GameObject(); //con esto no peta xD
	roots->name = "Scene";

	return ret;
}

// -----------------------------------------------------------------
bool ModuleHierarchy::CleanUp()
{
	LOG("Cleaning Hierarchy");
	delete roots;
	return true;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::Update(float dt)
{
	DrawHierarchy();
	//objSelected->InspectorWindow();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

void ModuleHierarchy::DrawHierarchy()
{
	if (ImGui::Begin("GameObjects Hierarchy")) {
		GameObjectTree(roots);
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Create Object")) {
				GameObject* parent = objSelected;
				App->scene->createObj(parent);

				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}		
	}
	ImGui::End();


}

void ModuleHierarchy::GameObjectTree(GameObject* obj)
{
	//if (obj->chooseChild /*|| SDL_SCANCODE_0==KEY_DOWN*/) objSelected->InspectorWindow();

	ImGuiTreeNodeFlags flag_TNode = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (obj->children.size() == 0)
		flag_TNode |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	if (obj == objSelected)
		flag_TNode |= ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Selected;

	bool clown = ImGui::TreeNodeEx(obj, flag_TNode, obj->name.c_str());
			
	if (clown)
	{
		if (!obj->children.empty()) {
			for (int i = 0; i < obj->children.size(); i++)
			{
				GameObjectTree(obj->children[i]);
			}
			ImGui::TreePop();
		}


		//if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Right || ImGuiMouseButton_::ImGuiMouseButton_Left)) {
		//	objSelected = obj;
		//}
	}

	//if (ImGui::BeginDragDropSource())
	//{
	//	ImGui::SetDragDropPayload("GameObj", obj, sizeof(GameObject*));

	//	TargetDropped = obj;
	//	ImGui::Text("aaaaaaaaa");
	//	ImGui::EndDragDropSource();
	//}

	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left, true))
	{
		if (objSelected != obj) {
			objSelected = obj;

		}
		GameObjectTree(obj);
	}	

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* PayLoad = ImGui::AcceptDragDropPayload("GameObj"))
		{
			//TargetDropped->AnotherParent(obj);
			TargetDropped = nullptr;
		}
		ImGui::EndDragDropTarget();
	}



}