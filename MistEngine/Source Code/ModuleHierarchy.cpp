#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"

#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"

ModuleHierarchy::ModuleHierarchy(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleHierarchy::~ModuleHierarchy()
{}

 //-----------------------------------------------------------------
bool ModuleHierarchy::Start()
{
	//LOG("Setting up the hierarchy");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleHierarchy::CleanUp()
{
	LOG("Cleaning Hierarchy");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::Update(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

