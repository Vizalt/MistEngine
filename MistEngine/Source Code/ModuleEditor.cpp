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
	case 1:
		Play();
		break;
	case 2:
		Stop();
		break;
	case 3:
		Pause();
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
	GameTimer.Start();
	LOG("Timer Starting...");
	LOG("%f", GameTimer.Read() / 1000.0f);
}

void ModuleEditor::Stop()
{
	GameTimer.Stop();
	LOG("Timer Stopped...");
}

void ModuleEditor::Pause()
{
	Paused = true;
	LOG("Paused Time");
}
