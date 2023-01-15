#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ParticleSystem.h"
#include "Emitter.h"
#include "GameObject.h"

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

	void castFirework();

public:

	vector<CEmitter*> emitterVector;

	vector<GameObject*> fireworksList;

private:

};