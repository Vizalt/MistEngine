#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "Camera.h"
#include "Transform.h"

#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleEditor::~ModuleEditor()
{}

//-----------------------------------------------------------------
bool ModuleEditor::Start()
{
	bool ret = true;
	f = 1.0f;
	return ret;
}

update_status ModuleEditor::PreUpdate(float dt)
{	
	switch (TimeStatus) {
	case 1: //playing
		deltaT = (float)GameTimer.Read() / 1000.0f;
		GameTimer.Stop();
		GameTimer.Start();
		break;
	case 2: //stop
		GameTimer.Stop();
		App->renderer3D->mainCam->owner->transform->rotation.y = 0;
		App->renderer3D->mainCam->owner->transform->SetTransformMatrix();
		deltaT = 0;
		rotation = 0;
		playing = false;
		break;
	case 3: //pause	
		playing = false;
		break;
	case 4:
		//Step();
		break;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float dt)
{
	rotation = 1;
	f += deltaT;

	if (TimeStatus == 1) 
	{	
		if (f > 0.03f) {
			App->renderer3D->mainCam->owner->transform->rotation.y += rotation;
			App->renderer3D->mainCam->owner->transform->SetTransformMatrix();
			if (App->renderer3D->mainCam->owner->transform->rotation.y == 360) {
				App->renderer3D->mainCam->owner->transform->rotation.y = 0;
			}
			f = 0.0f;
		}		
	}
	
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	return true;
}

void ModuleEditor::Play()
{	
	if (playing == false) {
		LOG("PLAYING");
		playing = true;
		TimeStatus = 1;
		
	}
	else if (playing == true) { //stopping the game if the game was already playing
		LOG("NOT PLAYING");		
		TimeStatus = 2;
		deltaT = 0;
		GameTimer.Stop();
		playing = false;
	}	
}

void ModuleEditor::Stop()
{	
	deltaT = 0;
	ImGui::SetWindowFocus("Scene");
	TimeStatus = 2;
}

void ModuleEditor::Pause()
{
	if (paused == true) {		
		TimeStatus = 1;
		paused = false;
	}
	else {
		TimeStatus = 3;
		paused = true;
	}
}

void ModuleEditor::Step()
{
	/*Play();
	Stop();*/
}