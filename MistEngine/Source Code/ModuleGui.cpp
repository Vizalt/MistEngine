#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "Camera.h"
#include "Mesh.h"

#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"

ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleGui::~ModuleGui()
{}

// -----------------------------------------------------------------
bool ModuleGui::Start()
{
	LOG("Setting up the UI");
	bool ret = true;
	
	return ret;
}

// -----------------------------------------------------------------
bool ModuleGui::CleanUp()
{
	LOG("Cleaning UI");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleGui::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

vector<float> ModuleGui::fps_log;
vector<float> ModuleGui::ms_log;
vector<float> ModuleGui::stackfps = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
vector<float> ModuleGui::stackms = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

// -----------------------------------------------------------------
update_status ModuleGui::Update(float dt)
{
	float FPS = 1 / dt;
	fps_log.push_back(FPS);
	float MS = 1000.0f * dt;
	ms_log.push_back(MS);

	//ImGui::ShowDemoWindow();
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Quit", "ESC")) {
				ImGui::EndMenu();
				return UPDATE_STOP;
				
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View")) {
			ImGui::MenuItem("Configuration", NULL, &config);
			ImGui::MenuItem("Console", NULL, &console);
			ImGui::MenuItem("Hierarchy", NULL, &hierarchy);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Objects")) {

			if (ImGui::MenuItem("Create Empty Object")) {
				if (App->hierarchy->objSelected != nullptr) {
					GameObject* parent = App->hierarchy->objSelected;
					App->scene->createObj(parent);
				}
				else {
					App->scene->createObj(App->hierarchy->roots);
				}
			}
			if (ImGui::MenuItem("Create Cube")) {
				if (App->hierarchy->objSelected != nullptr) {
					GameObject* parent = App->hierarchy->objSelected;
					App->scene->createObjPrim(parent, MeshType::CUBE);
				}
				else {
					App->scene->createObjPrim(App->hierarchy->roots, MeshType::CUBE);
				}
			}
			if (ImGui::MenuItem("Create Sphere")) {
				if (App->hierarchy->objSelected != nullptr) {
					GameObject* parent = App->hierarchy->objSelected;
					App->scene->createObjPrim(parent, MeshType::SPHERE);
				}
				else {
					App->scene->createObjPrim(App->hierarchy->roots, MeshType::SPHERE);
				}
			}
			if (ImGui::MenuItem("Create Cylinder")) {
				if (App->hierarchy->objSelected != nullptr) {
					GameObject* parent = App->hierarchy->objSelected;
					App->scene->createObjPrim(parent, MeshType::CYLINDER);
				}
				else {
					App->scene->createObjPrim(App->hierarchy->roots, MeshType::CYLINDER);
				}
			}
			if (ImGui::MenuItem("Create Line")) {
				if (App->hierarchy->objSelected != nullptr) {
					GameObject* parent = App->hierarchy->objSelected;
					App->scene->createObjPrim(parent, MeshType::LINE);
				}
				else {
					App->scene->createObjPrim(App->hierarchy->roots, MeshType::LINE);
				}
			}
			if (ImGui::MenuItem("Create Camera")) {
				if (App->hierarchy->objSelected != nullptr) {
					GameObject* parent = App->hierarchy->objSelected;
					App->scene->createCamera(parent);
				}
				else {
					App->scene->createCamera(App->hierarchy->roots);
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			ImGui::MenuItem("About", NULL, &about);
			ImGui::MenuItem("Documentation", NULL, &github);
			ImGui::MenuItem("Download latest", NULL, &releases);
			ImGui::MenuItem("Report a bug", NULL, &issues);
			ImGui::EndMenu();
		}
		if (ImGui::Button("PLAY")) {
			LOG("PLAYING SCENE");
			App->editor->Play();
			if(!App->editor->playing)
				ImGui::SetWindowFocus("Game");
		}
		if (ImGui::Button("STOP")) {
			LOG("STOP SCENE");
			App->editor->Stop();
			ImGui::SetWindowFocus("Scene");
		}
		if (ImGui::Button("PAUSE")) {
			LOG("PAUSE SCENE");
			App->editor->Pause();
		}
		ImGui::EndMainMenuBar();
	}
	if (about) {
		if (ImGui::Begin("About")) {
			ImGui::Text("MIST ENGINE ~ ~");
			ImGui::Separator();
			ImGui::NewLine();
			ImGui::Text("A 3D Game Engine made by students of CITM.");
			ImGui::Text("By Marina Albala and David Benages");
			ImGui::NewLine();
			ImGui::Text("3rd Partie Libraries:");
			ImGui::BulletText("SDL 2.0");
			ImGui::BulletText("ImGui 1.88");
			ImGui::BulletText("Glew 2.1.0");
			ImGui::BulletText("MathGeoLib 1.5");
			ImGui::BulletText("OpenGL 3.1");
			ImGui::BulletText("PhysFS");
			ImGui::BulletText("Assimp");
			ImGui::NewLine();
			ImGui::Text("License:");
			ImGui::NewLine();
			PrintLicense();
		}
		ImGui::End();
	}
	if (github) {
		if (ImGui::Begin("GitHub")) {
			ShellExecute(NULL, "open", "https://github.com/Vizalt/MistEngine", NULL, NULL, SW_SHOWNORMAL);
			github = false;
		}
		ImGui::End();
	}
	if (releases) {
		if (ImGui::Begin("GitHub")) {
			ShellExecute(NULL, "open", "https://github.com/Vizalt/MistEngine/releases", NULL, NULL, SW_SHOWNORMAL);
			releases = false;
		}
		ImGui::End();
	}
	if (issues) {
		if (ImGui::Begin("Report a bug")) {
			ShellExecute(NULL, "open", "https://github.com/Vizalt/MistEngine/issues", NULL, NULL, SW_SHOWNORMAL);
			issues = false;
		}
		ImGui::End();
	}
	if (config) {
		if (ImGui::Begin("Configuration")) {
			if (ImGui::CollapsingHeader("Application")) {
				static char string[128] = "Mist Engine ~ ~";
				ImGui::InputText("Engine Name", string, IM_ARRAYSIZE(string));
				static char string2[128] = "CITM UPC";
				ImGui::InputText("Organization", string2, IM_ARRAYSIZE(string2));
		
				ImGui::SliderInt("FPS", &App->fps , 1, 120);
								
				char title[25];
				sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
				ImGui::PlotHistogram("##Framerate", &fps_log[0], stackfps.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));

				sprintf_s(title, 25, "Miliseconds %0.1f", ms_log[fps_log.size() - 1]);
				ImGui::PlotHistogram("##Miliseconds", &ms_log[0], stackms.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
				

				if (fps_log.size() >= 20)
				{
					stackfps[0] = fps_log[fps_log.size() - 1];
					stackms[0] = ms_log[ms_log.size() - 1];
				}

				for (int j = 0; j < fps_log.size() - 1; j++)
				{
					fps_log[j] = fps_log[j + 1];
					ms_log[j] = ms_log[j + 1];
				}


				//Debug
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
					1000.0 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			if (ImGui::CollapsingHeader("Window")) {
				if (ImGui::Checkbox("Full Screen\t", &App->window->fullScreen)) {
					App->window->resizable = false; App->window->borderless = false; App->window->desktop = false;
					App->window->SwitchScreen();
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Resizable", &App->window->resizable)) {
					App->window->fullScreen = false; App->window->borderless = false; App->window->desktop = false;
					App->window->SwitchScreen();
				}
				if (ImGui::Checkbox("Borderless \t", &App->window->borderless)) {
					App->window->fullScreen = false; App->window->resizable = false; App->window->desktop = false;
					App->window->SwitchScreen();
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Full Desktop", &App->window->desktop)) {
					App->window->fullScreen = false; App->window->resizable = false; App->window->borderless = false;
					App->window->SwitchScreen();
				}
				ImGui::SliderFloat("Brightness", &brightness,minBright, maxBright);
				ImGui::SliderInt("Width", &width, 640, 1920);
				ImGui::SliderInt("Height", &height, 480, 1080);
				SDL_SetWindowSize(App->window->window, width, height);
				SDL_SetWindowBrightness(App->window->window, brightness);
			}
			if (ImGui::CollapsingHeader("Camera"))
			{
				ImGui::Text("");
				ImGui::Text("Rendered objects: %d", App->camera->sceneCam->printCount);
				ImGui::Text("");
				if (ImGui::SliderInt("FOV", &App->camera->sceneCam->FOV, 5, 180)) {
					App->camera->sceneCam->FrustumCam.verticalFov = App->camera->sceneCam->FOV * DEGTORAD;
					App->camera->sceneCam->FrustumCam.horizontalFov = 2.0f * atanf(tanf(App->camera->sceneCam->FrustumCam.verticalFov / 2.0f) * 1.7f);
				}
				if (ImGui::Button("Reset FOV")) {
					App->camera->sceneCam->FOV = 60.0f;

					App->camera->sceneCam->FrustumCam.verticalFov = App->camera->sceneCam->FOV * DEGTORAD;
					App->camera->sceneCam->FrustumCam.horizontalFov = 2.0f * atanf(tanf(App->camera->sceneCam->FrustumCam.verticalFov / 2.0f) * 1.7f);
				}


				ImGui::SliderFloat("Near Distance", &App->camera->sceneCam->FrustumCam.nearPlaneDistance, 0.1f, App->camera->sceneCam->FrustumCam.farPlaneDistance);
				if (ImGui::Button("Reset Near Distance")) {
					App->camera->sceneCam->FrustumCam.nearPlaneDistance = 0.1f;
				}

				ImGui::InputFloat("Far Distance", &App->camera->sceneCam->FrustumCam.farPlaneDistance);
				if (ImGui::Button("Reset Far Distance")) {
					App->camera->sceneCam->FrustumCam.farPlaneDistance = 500.f;
				}
			}
			if (ImGui::CollapsingHeader("File System")) {
				/*if(ImGui::Checkbox("Active\t")){}*/
				char* base_path = SDL_GetBasePath();
				ImGui::Text("Base Path:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", base_path);
				//ImGui::Text("Read Path:");

				//ImGui::Text("Write Path:");
			}
			if (ImGui::CollapsingHeader("Input")) {
				ImGuiIO& io = ImGui::GetIO();
				int count = IM_ARRAYSIZE(io.MouseDown);
				ImGui::Text("Mouse Position:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%g, %g", io.MousePos.x, io.MousePos.y);
				ImGui::Text("Mouse Motion:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%g, %g", io.MouseDelta.x, io.MouseDelta.y);
				ImGui::Text("Mouse Wheel:");
				ImGui::Text("Mouse down:");         for (int i = 0; i < count; i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f),"b%d (%.02f secs)", i, io.MouseDownDuration[i]); }

			}
			if (ImGui::CollapsingHeader("Hardware")) {

				SDL_version compiled;
				SDL_version linked;

				SDL_VERSION(&compiled);
				SDL_GetVersion(&linked);
				ImGui::Text("SDL Version:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u.%u.%u\n",
					compiled.major, compiled.minor, compiled.patch);

				ImGui::Separator();

				float ram = SDL_GetSystemRAM();
				ImGui::Text("RAM size:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fGb", ram/1024);

				int cpu_count = SDL_GetCPUCount(); //number of logical cpu cores
				ImGui::Text("CPUs:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d (Cache: %dkb)", cpu_count, SDL_GetCPUCacheLineSize());

				ImGui::Separator();

				const char* platform = SDL_GetPlatform();
				ImGui::Text("Platform:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s\n", platform);

				int display_num = SDL_GetNumVideoDisplays();
				ImGui::Text("Display Count:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d\n", display_num);

				for (int i = 0; i < display_num; i++)
				{
					const char* name = SDL_GetDisplayName(i);
					ImGui::Text("Display:"); ImGui::SameLine();
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s\n", name);
				}
			}
		}
		ImGui::End();
	}

	PrintConsole();

	
	
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleGui::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

void ModuleGui::PrintLicense() {

	ImGui::Text("MIT License");
	ImGui::NewLine();
	ImGui::Text("Copyright(c) 2022 Marina Albala & David Benages");
	ImGui::NewLine();
	ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
	ImGui::Text("of this softwareand associated documentation files(the 'Software'), to deal");
	ImGui::Text("in the Software without restriction, including without limitation the rights");
	ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell");
	ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
	ImGui::Text("furnished to do so, subject to the following conditions :");
	ImGui::NewLine();
	ImGui::Text("The above copyright noticeand this permission notice shall be included in all");
	ImGui::Text("copies or substantial portions of the Software.");
	ImGui::NewLine();
	ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
	ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
	ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
	ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
	ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
	ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
	ImGui::Text("SOFTWARE.");
}

void ModuleGui::savelogs(string log)
{
	logs.push_back(log);
}

void ModuleGui::PrintConsole()
{
	if (console) {
		if (ImGui::Begin("console")) {
			string infolog = " ";
			for (int i = 0; i < logs.size(); i++) {
				ImGui::Text(logs[i].c_str());
			}
		}
		ImGui::End();
	}
}
