#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"

#include "glew.h"
#include "ModuleRenderer3D.h"
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

void ModuleScene::SceneWindow()
{
	ImGui::Begin("Scene");
	WindowSize = ImGui::GetContentRegionAvail();

	ImGui::Image((ImTextureID)App->camera->cameraBuffer, WindowSize, ImVec2(0, 1), ImVec2(1, 0));

	ImVec2 mousePos = ImGui::GetMousePos();

	ImVec2 normalized = NormalizeMouse(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y, mousePos);


	if (ImGui::IsMouseClicked) {
		picking = App->camera->FrustumCam.UnProjectLineSegment(normalized.x, normalized.y);
	}



	ImGui::End();
}

GameObject* ModuleScene::createObj(GameObject* parent)
{
	GameObject* b = new GameObject(parent);

	return b;
}

ImVec2 ModuleScene::NormalizeMouse(float x, float y, float w, float h, ImVec2 pos)
{
	//	w = with of the viewport
	//	h = height of the viewport
	//	x = X position of the mouse
	//	y = Y position ot the mouse

	//GLfloat ndc_x = 2.0 * x / w - 1.0;
	//GLfloat ndc_y = 1.0 - 2.0 * y / h; // invert Y axis

	ImVec2 normalizedPos;

	normalizedPos.x = 2.0 * x / w - 1.0;
	normalizedPos.y = 1.0 - 2.0 * y / h;

	return normalizedPos;
}

void ModuleScene::OnSave() {}