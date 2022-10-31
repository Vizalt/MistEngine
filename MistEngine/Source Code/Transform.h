#pragma once
#include "Component.h"
#include "Math/float4x4.h"
#include "Math/float3.h"
#include "Math/Quat.h"

class GameObject;
class Component;

class Transform : public Component
{
public:

	Transform();
	Transform(GameObject* owner);
	~Transform();

	float4x4 glTransform, glTransformT;
	float4x4 lTransform;

	float3 position, scale;
	Quat rotation;

	void SetTransformMatrix(float3 _position, Quat _rotation, float3 _localScale);

};