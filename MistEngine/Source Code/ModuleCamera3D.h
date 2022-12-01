#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

//#include "Math/Quat.h"

class CCamera;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	CCamera* sceneCam;

	GameObject* GameCamera;
	CCamera* mainCam;

	//void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	//void LookAt(const vec3 &Spot);
	//void Move(const vec3 &Movement);
	/*float* GetViewMatrix();
	float* GetProjectionMatrix();*/
	//void PrintLicense();

private:

	bool click = false;

};