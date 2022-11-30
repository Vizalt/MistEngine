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
	//objPicked = nullptr;
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

		if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
			objPicked = nullptr;
		}
		GameObjectTree(roots);
		if (objSelected != nullptr) {// don't show the option of creating a gameobj if nothing it's selected :)
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::Selectable("Create Empty")) {
					GameObject* parent = objSelected;
					App->scene->createObj(parent);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}		
		}
	}
	ImGui::End();
}

void ModuleHierarchy::GameObjectTree(GameObject* obj)
{
	ImGuiTreeNodeFlags flag_TNode = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;
	
	bool clown;

	if (obj->parent == nullptr) {
		flag_TNode |= ImGuiTreeNodeFlags_DefaultOpen;
	}
	else {
		flag_TNode |= ImGuiTreeNodeFlags_OpenOnArrow;
	}

	if (obj == objSelected) {
		flag_TNode |= ImGuiTreeNodeFlags_Selected;
	}

	if (obj->children.size() != 0)
		clown = ImGui::TreeNodeEx(obj, flag_TNode, obj->name.c_str());

	else {
		flag_TNode |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx(obj, flag_TNode, obj->name.c_str());
		clown = false;
	}

	if (obj->parent != nullptr) {

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("GameObject", obj, sizeof(GameObject*));

			objPicked = obj;//the obj we move
			ImGui::EndDragDropSource();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
		{
			objDropped = obj;
			SetGameObject(obj);
			/*if (objSelected != obj) {
				SetGameObject(objSelected);
			}	*/
		}		
	}

	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* PL = ImGui::AcceptDragDropPayload("GameObject")) {			
			objPicked->NewChild(objDropped);
			//objPicked = nullptr;
		}
		ImGui::EndDragDropTarget();
	}
	if (clown)
	{
		if (!obj->children.empty()) {
			for (unsigned int i = 0; i < obj->children.size(); i++)
			{
				GameObjectTree(obj->children[i]);
			}
		}
		ImGui::TreePop();
	}	
}

void ModuleHierarchy::SetGameObject(GameObject* obj)
{
	objSelected = obj;
}
