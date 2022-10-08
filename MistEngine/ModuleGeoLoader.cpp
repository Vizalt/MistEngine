#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleGeoLoader.h"
#include "ModuleWindow.h"

#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "Primitive.h"

ModuleGeoLoader::ModuleGeoLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleGeoLoader::~ModuleGeoLoader()
{

}

// -----------------------------------------------------------------
bool ModuleGeoLoader::Start()
{
	bool ret = true;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

// -----------------------------------------------------------------
update_status ModuleGeoLoader::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleGeoLoader::Update(float dt)
{

	

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleGeoLoader::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
bool ModuleGeoLoader::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}