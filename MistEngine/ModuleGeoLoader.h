#ifndef ModuleGeoLoader_HEADER
#define ModuleGeoLoader_HEADER
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

class ModuleGeoLoader : public Module
{
public:
	ModuleGeoLoader(Application* app, bool start_enabled = true);
	~ModuleGeoLoader();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:

public:

private:
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
}; 

#endif // ModuleGeoLoader