#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleGeoLoader.h"
#include "ModuleRenderer3D.h"

#include<string>

using namespace std;

class GameObject;

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	GameObject* createObj(GameObject* parent);

private:
	std::string file_path;
	std::string texture_path;
	GameObject* objdebug;
};

#endif