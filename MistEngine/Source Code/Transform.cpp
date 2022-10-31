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

void Transform::SetTransformMatrix(float3 _position, Quat _rotation, float3 _localScale)
{
}
