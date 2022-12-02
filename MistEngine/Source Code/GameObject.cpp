#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"

GameObject::GameObject()
{
	name = "gameObject";
	parent = nullptr;
	fixed = false;

	transform = new Transform(this);
	components.push_back(transform);
}

GameObject::GameObject(GameObject* parent)
{
	name = "gameObject";
	this->parent = parent;
	fixed = false;

	if(parent!= nullptr){
		parent->children.push_back(this);
	}

	transform = new Transform(this);
	components.push_back(transform);
}

GameObject::~GameObject()
{
	if (parent != nullptr) {

		for (size_t i = 0; i < parent->children.size(); i++)
		{
			if (parent->children[i] == this) {
				parent->children.erase(parent->children.begin() + i);
				parent = nullptr;
			}
		}
	}

	transform = nullptr;

	while (!components.empty())
	{
		delete components[0];
	}
	components.clear();

	while (!children.empty())
	{
		delete children[0];
	}
	children.clear();
}

void GameObject::InspectorWindow()
{

	strcpy(string, name.c_str());

	ImGui::SameLine;
	ImGui::InputText("Name", string, IM_ARRAYSIZE(string), ImGuiInputTextFlags_EnterReturnsTrue);
	
	if(ImGui::IsKeyDown(ImGuiKey_Enter))
		name = string;

	for (size_t i = 0; i < components.size(); i++)
	{
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		components[i]->Inspector();
	}
}

void GameObject::CreateComponent(ComponentType type)
{
	Component* newComponent = new Component(this);

	newComponent->type = type;
	newComponent->active = true;

	components.push_back(newComponent);

	delete newComponent;
}

void GameObject::DeleteChild(GameObject* child)
{
	for (int i = 0; i < children.size(); i++) {
		if (children[i] == child) {
			children.erase(children.begin() + i);
			child->parent = nullptr;
		}
	}
}

bool GameObject::ChangeParent(GameObject* NewParent)
{
	if (parent != nullptr) {
		if (NewParent->CheckChildOf(this)) return false;

		parent->DeleteChild(this);
	}

	parent = NewParent;
	NewParent->children.push_back(this);

	return true;
}

bool GameObject::CheckChildOf(GameObject* parent)
{
	if (parent->children.empty()) return false;

	for (int i = 0; i < parent->children.size(); i++) {

		if (children[i] == this) return true;

	}
	return false;
}

GameObject* GameObject::GetParent()
{
	return parent;
}

CMesh* GameObject::GetComponentMesh()
{
	for (int i = 0; i < components.size(); i++) {

		if (components[i]->type == ComponentType::MESH)
		{ 
			return (CMesh*)components[i]; 
		}
	}

	return nullptr;
}

CCamera* GameObject::GetComponentCamera()
{
	for (int i = 0; i < components.size(); i++) {

		if (components[i]->type == ComponentType::CAMERA)
		{
			return (CCamera*)components[i];
		}
	}

	return nullptr;
}
