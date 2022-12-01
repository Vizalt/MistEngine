#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"

class GameObject;
class Component;

class CCamera : public Component
{
public:

	CCamera();
	CCamera(GameObject* owner);
	~CCamera();

	void SetCam();
	void GenBuffer();

	float* GetViewMatrix();
	float* GetProjectionMatrix();

	void TransformCam();

	void Inspector();

	Frustum FrustumCam;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;

	int FOV = 60.0f;

	unsigned int cameraBuffer;
	unsigned int frameBuffer;

private:

	unsigned int renderObjBuffer;
};