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

	roots = new GameObject();
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

	if (App->input->GetKey(SDL_SCANCODE_DELETE))
	{
		delete objSelected;
		objSelected = nullptr;
	}

	if(objSelected != nullptr)
		objSelected->InspectorWindow();	

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
	ImGuiTreeNodeFlags flag_TNode = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

	if (obj->children.size() == 0)
		flag_TNode |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	if (obj == objSelected)
		flag_TNode |= ImGuiTreeNodeFlags_Selected;

	bool clown = ImGui::TreeNodeEx(obj, flag_TNode, obj->name.c_str());
			
	if (clown)
	{
		if (!obj->children.empty()) {
			for (unsigned int i = 0; i < obj->children.size(); i++)
			{
				GameObjectTree(obj->children[i]);
			}
			ImGui::TreePop();
		}
	}

	if (obj->parent != nullptr) {

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("GameObject", obj, sizeof(GameObject*));

			TargetDropped = obj;
			ImGui::Text("Changing...");
			ImGui::EndDragDropSource();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
		{
				SetGameObject(obj);
				if (objSelected != obj) {
					SetGameObject(objSelected);
				}

	
		}
	}
	
}

void ModuleHierarchy::SetGameObject(GameObject* obj)
{
	objSelected = obj;
}
