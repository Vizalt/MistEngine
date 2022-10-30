#include "GameObject.h"

Component::Component()
{
	type = ComponentType::TRANSFORM;
	active = false;
	owner = nullptr;
}

Component::~Component()
{
	active = false;
	owner = nullptr;
}

GameObject::GameObject()
{
	name = "gameObject";
	parent = nullptr;
}

GameObject::~GameObject()
{
	name = "";
	parent = nullptr;
}

void GameObject::CreateComponent(ComponentType type)
{
	Component* newComponent = new Component();

	newComponent->type = type;
	newComponent->active = true;
	newComponent->owner = this;

	Components.push_back(newComponent);
	delete newComponent;
}

