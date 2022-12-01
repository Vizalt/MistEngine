#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "GameObject.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"


class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void Play();
	void Stop();
	void Pause();
	void Step();

	Timer GameTimer;

	bool paused = false;
	bool playing = false;

	int TimeStatus = 0; //default is paused
	float deltaT = 0.f;
};