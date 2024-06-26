#include "Application.h"
#include "ModuleEditor.h"
#include<string>
#include "Globals.h"
#include "Random.h"

extern Application* externalapp = nullptr;

Application* Application::GetApp()
{
	if (externalapp == nullptr)
	{
		externalapp = new Application();
	}
	return externalapp;
}

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	gui = new ModuleGui(this);
	loader = new ModuleGeoLoader(this);
	texture = new ModuleTexture(this);
	scene = new ModuleScene(this);
	hierarchy = new ModuleHierarchy(this);
	editor = new ModuleEditor(this);
	particle = new ModuleParticles(this);

	LOG("...");

	// The order of calls is very important!
	// Modules will Init() Start() and UpdateAABB in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);

	AddModule(texture);
	AddModule(particle);
	AddModule(loader);	
	AddModule(hierarchy);
	AddModule(scene);
	AddModule(gui);
	AddModule(editor);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (int i = list_modules.size() - 1; i >= 0; i--)
	{
		delete list_modules[i];
		list_modules[i] = nullptr;
	}
	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	LOG("Application Init --------------");
	Random::Init();
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		ret = list_modules[i]->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		ret = list_modules[i]->Start();
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();

	//switch (editor->TimeStatus) {
	//case 1:
	//	editor->Play();
	//	break;
	//case 2:
	//	editor->Stop();
	//	break;
	//case 3:
	//	editor->Pause();
	//	break;
	//}
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	MsFrame = ms_timer.Read();     
	float FrameWait = (1000.f / (float)fps) - (float)MsFrame;     
	SDL_Delay(static_cast<Uint32>(fabs(FrameWait)));
}

// Call PreUpdate, UpdateAABB and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PreUpdate(dt);
	}

	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->Update(dt);
	}

	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PostUpdate(dt);
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = list_modules.size() - 1; i >= 0; i--)
	{
		list_modules[i]->CleanUp();
		delete list_modules[i];
		list_modules[i] = nullptr;
	}

	list_modules.clear();
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}