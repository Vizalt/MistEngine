#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"

#include "MathGeoLib.h"
#include "glew.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

#define MAX_LIGHTS 8

class GameObject;
class CCamera;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

public:
	ImGuiIO* io = nullptr;

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	float3x3 NormalMatrix;
	float4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	GameObject* GameCamera;
	CCamera* mainCam;
};