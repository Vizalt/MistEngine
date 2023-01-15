#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleGeoLoader.h"
#include "ModuleRenderer3D.h"

#include<string>

using namespace std;

class GameObject;
enum class MeshType;

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

	void SceneWindow();
	void GameWindow();

	GameObject* createObj(GameObject* parent);

	GameObject* createObjPrim(GameObject* parent, MeshType type);

	GameObject* createCamera(GameObject* parent);

	GameObject* createEmitter(GameObject* parent);

	ImVec2 WindowSize;

	ImVec2 NormalizeMouse(float x, float y, float w, float h, ImVec2 pos);

	void OnSave();

	bool sceneSelected = false;

private:
	std::string file_path;
	std::string texture_path;
	GameObject* objdebug;
	LineSegment picking;
};

#endif