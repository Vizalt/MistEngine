#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Start();

	bool CleanUp();

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	GLuint textureID;
};