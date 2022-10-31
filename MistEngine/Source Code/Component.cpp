#include "Component.h"

Component::Component(GameObject* owner)
{
	type = ComponentType::NONE;
	active = true;
	this->owner = owner;
}

Component::~Component()
{
}

void Component::Inspector()
{
}
