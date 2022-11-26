#include "GameObject.h"

GameObject::GameObject()
{
	name = "gameObject";
	parent = nullptr;

	components.push_back(transform);
}

GameObject::GameObject(GameObject* parent)
{
	name = "gameObject";
	this->parent = parent;

	if(parent!= nullptr){
		parent->children.push_back(this);
	}

	transform = new Transform(this);
	components.push_back(transform);
}

GameObject::~GameObject()
{
	name = "";
	parent = nullptr;

	transform = nullptr;

	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
	components.clear();	
}

void GameObject::InspectorWindow()
{
	ImGui::Begin("Inspector");
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
	ImGui::End();
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
	children.erase(std::find(children.begin(), children.end(), child));
}

bool GameObject::checkChild(GameObject* obj)
{
	if (obj == nullptr) {
		return false;
	}
	if (obj == this)
		return true;
	else {
		return checkChild(obj->parent);
	}



	return false;
}

GameObject* GameObject::GetParent()
{
	return parent;
}

//GameObject* GameObject::ToParent(GameObject* newP)
//{
//	parent->DeleteChild(this); //deletes the actual parent
//	
//	NewChild(newP);
//
//	return nullptr;
//}

GameObject* GameObject::NewChild(GameObject* childObj)
{
	if (parent != nullptr) {
		parent->DeleteChild(this);
	}

	if (checkChild(childObj))
		return false;

	parent = childObj;
	if(childObj->parent != nullptr)
		parent->children.push_back(this);
	return nullptr;
}
