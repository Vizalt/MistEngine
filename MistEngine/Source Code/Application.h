#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleGui.h"
#include "ModuleGeoLoader.h"
#include "ModuleTexture.h"
#include "ModuleScene.h"
#include "ModuleHierarchy.h"
#include "ModuleEditor.h"

#include <vector>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleGui* gui;
	ModuleGeoLoader* loader;
	ModuleTexture* texture;
	ModuleScene* scene;
	ModuleHierarchy* hierarchy;
	ModuleEditor* editor;

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

	static Application* app;

public:

	int fps = 60;
	Uint32 MsFrame;

	Application();
	~Application();

	static Application* GetApp();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* externalapp;