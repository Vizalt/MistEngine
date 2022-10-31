#include "GameObject.h"

GameObject::GameObject()
{
	name = "gameObject";
	parent = nullptr;
}

GameObject::GameObject(GameObject* parent)
{
	name = "gameObject";
	this->parent = parent;
}

GameObject::~GameObject()
{
	name = "";
	parent = nullptr;
}

void GameObject::CreateComponent(ComponentType type)
{
	Component* newComponent = new Component(this);
	Transform* newTransform = new Transform(this);

	switch (type)
	{
	case ComponentType::NONE:

		newComponent->type = type;
		newComponent->active = true;

		components.push_back(newComponent);

		break;

	case ComponentType::TRANSFORM:

		newTransform->type = type;
		newTransform->active = true;

		components.push_back(newTransform);

		break;

	default:
		break;
	}

	delete newComponent;
	delete newTransform;
}

