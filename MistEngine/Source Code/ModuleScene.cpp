#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"

#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"
#include "Texture.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleScene::~ModuleScene()
{}

// -----------------------------------------------------------------
bool ModuleScene::Start()
{
	LOG("Setting up the Scene");
	bool ret = true;

	file_path = "Assets/BakerHouse.fbx";
	objdebug = App->loader->LoadFile(file_path);
	objdebug->name = "Baker House";

	return ret;
}

// -----------------------------------------------------------------
update_status ModuleScene::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleScene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleScene::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
bool ModuleScene::CleanUp()
{
	LOG("Cleaning Scene");

	delete objdebug;

	return true;
}

GameObject* ModuleScene::createObj(GameObject* parent)
{
	GameObject* b = new GameObject(parent);

	return b;
}

void ModuleScene::OnSave()
{



}