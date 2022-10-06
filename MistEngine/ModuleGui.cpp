#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"

#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
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

// -----------------------------------------------------------------
update_status ModuleGui::Update(float dt)
{

	ImGui::ShowDemoWindow();
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Quit ESC")) {
				return UPDATE_STOP;
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View")) {
			ImGui::MenuItem("Configuration", NULL, &config);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			ImGui::MenuItem("About", NULL, &about);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (about) {
		if (ImGui::Begin("About")) {
			ImGui::Text("MIST ENGINE ~ ~");
			ImGui::Separator();
			ImGui::NewLine();
			ImGui::Text("A 3D Game Engine made by studients of CITM.");
			ImGui::Text("By Marina Albala and David Benages");
			ImGui::NewLine();
			ImGui::Text("3rd Partie Libraries:");
			ImGui::BulletText("SDL 2.0");
			ImGui::BulletText("ImGui 1.88");
			ImGui::BulletText("Glew ");
			ImGui::BulletText("MathGeoLib");
			ImGui::BulletText("OpenGL");
			ImGui::NewLine();
			ImGui::Text("License:");
			ImGui::NewLine();
			PrintLicense();
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
				//ImGui::SliderInt("Brightness", );
				ImGui::SliderInt("Width", &width, 640, 1920);
				ImGui::SliderInt("Height", &height, 480, 1080);
				SDL_SetWindowSize(App->window->window, width, height);
			}
		}
		ImGui::End();
	}
	
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