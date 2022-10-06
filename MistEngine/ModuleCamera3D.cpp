#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleWindow.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 1.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
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
	
	
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0,0,0);
	float speed = 3.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	/*if(App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
	if(App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;


	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;*/

	Position += newPos;
	Reference += newPos;

	
	
	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		click = true;
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;

		Position -= Reference;

		if(dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if(dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if(Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * length(Position);
	}
	
	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);	

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

void ModuleCamera3D::PrintLicense() {

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