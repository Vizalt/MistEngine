#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib.h"
#include "imgui.h"
//#include "Mesh.h"

class GameObject;
class Component;
//struct Mesh;

class Transform : public Component
{
public:

	Transform();
	Transform(GameObject* owner);
	~Transform();

	float4x4 lTransform;

	float3 position, scale, rotation;

	void SetTransformMatrix();
	void Inspector();

	

	float4x4 GetTransformMatrix();

	//void BoxMesh();

	//Mesh* mesh;
};