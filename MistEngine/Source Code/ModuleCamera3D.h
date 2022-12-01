#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

//#include "Math/Quat.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	//void LookAt(const vec3 &Spot);
	//void Move(const vec3 &Movement);
	float* GetViewMatrix();
	float* GetProjectionMatrix();
	//void PrintLicense();

private:

	//void CalculateViewMatrix();
	bool click = false;
public:
	
	//vec3 X, Y, Z, Position, Reference;
	Frustum FrustumCam;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	
	unsigned int cameraBuffer;
	unsigned int frameBuffer;

private:

	unsigned int renderObjBuffer;
	//mat4x4 ViewMatrix, ViewMatrixInverse;
	/*bool config = true, about = false;
	int width = SCREEN_WIDTH * SCREEN_SIZE;
	int height = SCREEN_HEIGHT * SCREEN_SIZE;*/

};