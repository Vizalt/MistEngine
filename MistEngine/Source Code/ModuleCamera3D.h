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

	void Rotation();

	CCamera* sceneCam;
	float mouseSens = 0.50f;

	//void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	//void LookAt(const vec3 &Spot);
	//void Move(const vec3 &Movement);
	/*float* GetViewMatrix();
	float* GetProjectionMatrix();*/
	//void PrintLicense();

private:

	bool click = false;

};