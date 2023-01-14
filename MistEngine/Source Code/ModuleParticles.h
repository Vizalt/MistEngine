#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ParticleSystem.h"
#include "Emitter.h"

#include <vector>

class ModuleParticles : public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


public:

	vector<CEmitter*> emitterVector;

private:

};