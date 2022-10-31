#include "Transform.h"

Transform::Transform() : Component(nullptr)
{

}

Transform::Transform(GameObject* owner) : Component(owner)
{
	
}

Transform::~Transform()
{
}

