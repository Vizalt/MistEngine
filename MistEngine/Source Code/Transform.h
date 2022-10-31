#pragma once
#include "Component.h"
#include "glmath.h"

class GameObject;
class Component;

class Transform : public Component
{
public:

	Transform();
	Transform(GameObject* owner);
	~Transform();

	mat4x4 glTransform, glTransformT;
	mat4x4 lTransform;

	vec3 position, scale, rotation;

	void SetTransformMatrix(vec3 _position, vec3 _rotation, vec3 _localScale);

};