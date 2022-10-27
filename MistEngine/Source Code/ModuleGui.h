#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

#include <vector>
#include <string>

using namespace std;


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
	void savelogs(string log);

	void PrintConsole();

private:

	bool config = true, about = false, github=false, console=true, releases = false, issues=false;
	int width = SCREEN_WIDTH * SCREEN_SIZE;
	int height = SCREEN_HEIGHT * SCREEN_SIZE;
	float brightness = 1.0f;
	float maxBright = 0.0f;
	float minBright = 1.0f;
	ImVec2 MousePos;
	ImVec2 MouseDelta;
	char* data_path = NULL;

	vector<string> logs;
	string logstring[4096];
};