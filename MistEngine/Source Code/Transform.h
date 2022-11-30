#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib.h"
#include "imgui.h"

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

	float3 position, scale, rotation;

	void SetTransformMatrix(float3 _position, float3 _rotation, float3 _scale);
	void Inspector();
};