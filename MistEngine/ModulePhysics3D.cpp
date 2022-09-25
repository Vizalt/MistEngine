#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"

#include "Primitive.h"

//#ifdef _DEBUG
//	#pragma comment (lib, "Bullet/libx86/BulletDynamics_debug.lib")
//	#pragma comment (lib, "Bullet/libx86/BulletCollision_debug.lib")
//	#pragma comment (lib, "Bullet/libx86/LinearMath_debug.lib")
//#else
//	#pragma comment (lib, "Bullet/libx86/BulletDynamics.lib")
//	#pragma comment (lib, "Bullet/libx86/BulletCollision.lib")
//	#pragma comment (lib, "Bullet/libx86/LinearMath.lib")
//#endif

ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;

	
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
	
}

// Render not available yet----------------------------------
bool ModulePhysics3D::Init()
{
	LOG("Creating 3D Physics simulation");
	bool ret = true;

	return ret;
}

// ---------------------------------------------------------
bool ModulePhysics3D::Start()
{
	LOG("Creating Physics environment");


	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::Update(float dt)
{
		

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics3D::CleanUp()
{
	LOG("Destroying 3D Physics simulation");

	

	return true;
}



// --------------------------------------------------------