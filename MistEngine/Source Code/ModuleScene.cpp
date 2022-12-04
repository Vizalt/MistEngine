#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"

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

	/*file_path = "Assets/BakerHouse.fbx";
	objdebug = App->loader->LoadFile(file_path);
	objdebug->name = "Baker House";*/

	/*for (int i = 0; i < objdebug->children.size(); i++) {
		objdebug->children[i]->transform->rotation = float3::zero;
		objdebug->children[i]->transform->scale = float3::one;
		objdebug->children[i]->transform->SetTransformMatrix();
	}*/

	file_path = "Assets/street/scene.DAE";
	objdebug = App->loader->LoadFile(file_path);
	objdebug->transform->rotation[0] = -90;
	objdebug->transform->SetTransformMatrix();
	objdebug->SetAllRotationZero();

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
	if (App->renderer3D->mainCam != nullptr) {
		App->renderer3D->mainCam->TransformCam();
	}

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

	//Prevent image stretching by setting new aspect ratio
	float aspectRatio = WindowSize.x / WindowSize.y;
	App->camera->sceneCam->FrustumCam.verticalFov = App->camera->sceneCam->FOV * DEGTORAD;
	App->camera->sceneCam->FrustumCam.horizontalFov = 2.0f * atanf(tanf(App->camera->sceneCam->FrustumCam.verticalFov / 2.0f) * aspectRatio);

	ImGui::Image((ImTextureID)App->camera->sceneCam->cameraBuffer, WindowSize, ImVec2(0, 1), ImVec2(1, 0));


	if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)) {

		ImVec2 mousePos = ImGui::GetMousePos(); //Get pos when clicking
		ImVec2 normalized = NormalizeMouse(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + ImGui::GetFrameHeight(), ImGui::GetWindowSize().x, ImGui::GetWindowSize().y - ImGui::GetFrameHeight());

		LineSegment my_ray = App->camera->sceneCam->FrustumCam.UnProjectLineSegment(normalized.x, normalized.y);

		std::vector<GameObject*> interVec;

		//for with all the meshes triangles
		for (size_t i = 0; i < App->loader->meshes.size(); i++)
		{
			if (my_ray.Intersects(App->loader->meshes[i]->obb)) {
				if (App->loader->meshes[i]->Owner != nullptr) 
				{
					interVec.push_back(App->loader->meshes[i]->Owner);
					//LOG("Mouse Clicked");
				}
				
			}
		};

		uint indexCount = 0;

		for (size_t j = 0; j < interVec.size(); j++) {
			for (size_t i = 0; i < interVec[j]->GetComponentMesh()->meshes.size(); i++) {
				Mesh* mesh = interVec[i]->GetComponentMesh()->meshes[i];				
				
				for (size_t b = 0; b < mesh->num_indices; b+=3) {				

					//PETA
					float3 tri1(&mesh->vertices[mesh->indices[b] * VERTICES]);
					float3 tri2(&mesh->vertices[mesh->indices[b + 1] * VERTICES]);
					float3 tri3(&mesh->vertices[mesh->indices[b + 2] * VERTICES]);

					Triangle triangle(tri1, tri2, tri3);
					float dist;

					LOG("thissssssssssssss");

					//LOG("%d", triangle);
					if (my_ray.Intersects(triangle, &dist, nullptr)) 
					{
						App->hierarchy->SetGameObject(interVec[j]);
						LOG("BBBBBBBBBBBBBBBBBBBBB");
					} 
				
				}
			}

		}
	}

	ImGui::End();
}

void ModuleScene::GameWindow()
{
	ImGui::Begin("Game");
	WindowSize = ImGui::GetContentRegionAvail();

	float aspectRatio = WindowSize.x / WindowSize.y;
	App->renderer3D->mainCam->FrustumCam.verticalFov = App->renderer3D->mainCam->FOV * DEGTORAD;
	App->renderer3D->mainCam->FrustumCam.horizontalFov = 2.0f * atanf(tanf(App->renderer3D->mainCam->FrustumCam.verticalFov / 2.0f) * aspectRatio);

	ImGui::Image((ImTextureID)App->renderer3D->mainCam->cameraBuffer, WindowSize, ImVec2(0, 1), ImVec2(1, 0));


	//if (ImGui::IsMouseClicked) {

	//	ImVec2 mousePos = ImGui::GetMousePos(); //Get pos when clicking

	//	ImVec2 normalized = NormalizeMouse(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

	//	picking = App->renderer3D->mainCam->FrustumCam.UnProjectLineSegment(normalized.x, normalized.y);
	//}



	ImGui::End();
}

GameObject* ModuleScene::createObj(GameObject* parent)
{
	GameObject* b = new GameObject(parent);

	return b;
}

GameObject* ModuleScene::createObjPrim(GameObject* parent, MeshType type)
{
	GameObject* b = new GameObject(parent);

	CMesh* prim = new CMesh(b, type);

	b->components.push_back(prim);

	return b;
}

GameObject* ModuleScene::createCamera(GameObject* parent)
{
	GameObject* b = new GameObject(parent);

	CCamera* cam = new CCamera(b);
	b->components.push_back(cam);
	b->name = "Camera";
	b->transform->SetTransformMatrix();

	return b;
}

ImVec2 ModuleScene::NormalizeMouse(float x, float y, float w, float h)
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