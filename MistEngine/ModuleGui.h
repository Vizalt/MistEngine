#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

#include "imGui/imgui.h"
#include "imGui/backends/imgui_impl_sdl.h"
#include "imGui/backends/imgui_impl_opengl3.h"

class ModuleGui : public Module
{
public:
	ModuleGui(Application* app, bool start_enabled = true);
	~ModuleGui();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void PrintLicense();

private:

public:


private:

	bool config = true, about = false, github=false;
	int width = SCREEN_WIDTH * SCREEN_SIZE;
	int height = SCREEN_HEIGHT * SCREEN_SIZE;
	ImVec2 MousePos;
	ImVec2 MouseDelta;
	char* data_path = NULL;

};