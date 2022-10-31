#pragma once
#include "Globals.h"
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

	void SetTransformMatrix(vec3 position, vec3 rotation, vec3 scale);

};