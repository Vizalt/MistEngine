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
	LOG("Setting up the hierarchy");
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

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

void ModuleHierarchy::DrawHierarchy()
{

	if (ImGui::Begin("Hierarchy")) {
		GameObjectTree(roots);
	}
	ImGui::End();


	

}

void ModuleHierarchy::GameObjectTree(GameObject* obj)
{
	ImGuiTreeNodeFlags flag_TNode = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (obj->children.size() == 0)
		flag_TNode |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	if (obj == objSelected)
		flag_TNode |= ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Selected;

	clown = ImGui::TreeNodeEx(obj, flag_TNode, obj->name.c_str());
	
	if (clown) {
		for (int i = 0; i < obj->children.size(); i++)
		{
			GameObjectTree(obj->children[i]);
		}
	}

}


//bool fuck=ImGui::TreeNodeEx(gameobject, flag, gameobject->name.c_str());


	//for (int i = 0; i < gameobject->children.size(); i++)
	//{
	//	GameObjectTree(gameobject->children[i],i);
	//}


/*
	if (gameobject->children.size() == 0)
		flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	*/







/*bool nOpen = ImGui::TreeNodeEx(gameobject, a, gameobject->name.c_str());*/

//if (ImGui::BeginDragDropTarget())
//{
//	if (const ImGuiPayload* PayLoad = ImGui::AcceptDragDropPayload("GameObj"))
//	{

//		//TargetDropped->AnotherParent(gameobject);
//		LOG("%s", TargetDropped->name.c_str());
//		TargetDropped = nullptr;
//	}
//	ImGui::EndDragDropTarget();
//}
