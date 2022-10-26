#ifndef ModuleGeoLoader_HEADER
#define ModuleGeoLoader_HEADER
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"


#include <vector>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Glew/libx86/glew32.lib")

using namespace std;

#define VERTICES 5

struct Mesh {
	uint id_indices = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertices = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	void Draw();
};

class ModuleGeoLoader : public Module
{
public:
	ModuleGeoLoader(Application* app, bool start_enabled = true);
	~ModuleGeoLoader();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	void LoadFile(string Path);
	void BufferMesh(Mesh* mesh);
	bool CleanUp();
	
	void Draw();

private:

public:
	vector<Mesh*> meshes;
	string file_path;

private:
	
}; 

#endif // ModuleGeoLoader