#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "il.h"
#include "ilu.h"
#include "backends/imgui_impl_opengl3.h"

using namespace std;

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Start();

	bool CleanUp();

	GLuint GenTexture(GLuint* imgData, GLuint width, GLuint height);

	GLuint LoadTexture(string path);

	void FreeTexture(GLuint ID);

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	GLuint checkerID = 0;
	string texPath;
};