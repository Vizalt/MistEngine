#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"
#include "il.h"
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

	bool GenTexture(GLuint* imgData, GLuint width, GLuint height);

	bool LoadTexture(string path);

	void FreeTexture();

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	GLuint textureID = 0, 
		textureWidth = 0,
		textureHeight = 0;
	string texPath = "";
};