#include "GameObject.h"

GameObject::GameObject()
{
	name = "gameObject";
	parent = nullptr;

	transform = new Transform();
	components.push_back(transform);
}

GameObject::GameObject(GameObject* parent)
{
	name = "gameObject";
	this->parent = parent;

	transform = new Transform();
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
	ImGui::InputText("Game Object", string, IM_ARRAYSIZE(string));
	
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

GameObject* GameObject::GetParent()
{
	return parent;
}

