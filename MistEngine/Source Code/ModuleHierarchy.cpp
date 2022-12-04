#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "Mesh.h"

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

	ImGui::Begin("Inspector");

	if (objSelected != nullptr) {
		if (objSelected->parent != nullptr) objSelected->InspectorWindow();
	}

	ImGui::End();

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

		GameObjectTree(roots, 0);
		if (objSelected != nullptr) {// don't show the option of creating a gameobj if nothing it's selected :)
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::Selectable("Create Empty Object")) {
					GameObject* parent = objSelected;
					App->scene->createObj(parent);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Selectable("Create Cube")) {
					GameObject* parent = objSelected;
					App->scene->createObjPrim(parent, MeshType::CUBE);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Selectable("Create Sphere")) {
					GameObject* parent = objSelected;
					App->scene->createObjPrim(parent, MeshType::SPHERE);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Selectable("Create Cylinder")) {
					GameObject* parent = objSelected;
					App->scene->createObjPrim(parent, MeshType::CYLINDER);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Selectable("Create Line")) {
					GameObject* parent = objSelected;
					App->scene->createObjPrim(parent, MeshType::LINE);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Selectable("Create Camera")) {
					GameObject* parent = objSelected;
					App->scene->createCamera(parent);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}		
		}
	}
	ImGui::End();


}

void ModuleHierarchy::GameObjectTree(GameObject* obj, int index)
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
		clown = ImGui::TreeNodeEx((void*)(intptr_t)index, flag_TNode, obj->name.c_str(), index);

	else {
		flag_TNode |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx((void*)(intptr_t)index, flag_TNode, obj->name.c_str(), index);
		clown = false;
	}

	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("GameObject", obj, sizeof(GameObject*));
		
		TargetDropped = obj;
		ImGui::Text("Changing...");
		ImGui::EndDragDropSource();
	}

	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
	{
		objHovered = obj;
		if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
		{
			SetGameObject(obj);
		}
	}
	
	if (ImGui::IsWindowHovered())
	{
		if (!ImGui::IsAnyItemHovered())
		{
			if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
			{
				objSelected = nullptr;
			}
		}
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GameObject")) {

			if (!TargetDropped->fixed || !objHovered->fixed) {
				TargetDropped->ChangeParent(objHovered);
			}
		}
		ImGui::EndDragDropTarget();
	}

	if (clown)
	{
		if (!obj->children.empty()) {
			for (unsigned int i = 0; i < obj->children.size(); i++)
			{
				GameObjectTree(obj->children[i], i);
			}
		}
		ImGui::TreePop();
	}
	
}

void ModuleHierarchy::SetGameObject(GameObject* obj)
{
	objSelected = obj;
}
