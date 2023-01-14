#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
update_status ModuleParticles::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleParticles::Update(float dt)
{

	for (int i = 0; i < emitterVector.size(); i++) {		
		emitterVector[i]->Update();
	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleParticles::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	//Delete emitter array
	for (int i = 0; i < emitterVector.size(); i++) {
		delete emitterVector[i];
		emitterVector[i] = nullptr;
	}
	emitterVector.clear();

	return true;
}