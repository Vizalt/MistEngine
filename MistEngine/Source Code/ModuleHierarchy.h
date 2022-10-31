#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

#include <vector>
#include <string>

using namespace std;

class ModuleHierarchy : public Module
{
public:
	ModuleHierarchy(Application* app, bool start_enabled = true);
	~ModuleHierarchy();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
		
private:


};