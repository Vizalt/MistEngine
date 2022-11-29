#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"

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

	return ret;
}

update_status ModuleEditor::PreUpdate(float dt)
{
	switch (TimeStatus) {
	case 1: //playing
		GameTimer.Start();
		break;
	case 2: //stop
		GameTimer.Stop();
		deltaT = 0;
		break;
	case 3: //pause	
		GameTimer.Stop();
		break;
	case 4:
		//Step();
		break;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float dt)
{
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
		deltaT = (float)GameTimer.Read() / 1000.0f;
	}
	else if (playing == true) { //stopping the game if the game was already playing
		LOG("NOT PLAYING");		
		TimeStatus = 2;	
		playing = false;
	}	
}

void ModuleEditor::Stop()
{	
	TimeStatus = 2;
}

void ModuleEditor::Pause()
{
	if (paused == true) {		
		TimeStatus = 1;
		paused = false;
		deltaT = (float)GameTimer.Read() / 1000.0f;
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