#ifndef ModuleGeoLoader_HEADER
#define ModuleGeoLoader_HEADER
#include "Module.h"
#include "Globals.h"
#include "SDL_opengl.h"
#include "MathGeoLib.h"


#include <vector>

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"
//#pragma comment (lib, "Source Code/External/Assimp/libx86/assimp.lib")
//#pragma comment (lib, "Source Code/External/Glew/libx86/glew32.lib")

using namespace std;

#define VERTICES 5

class GameObject;
class Primitive;

struct Mesh {
	uint id_indices = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertices = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	GLuint id_texture = 0;

	GameObject* Owner;

	AABB localAABB;
	AABB aabb;
	OBB obb;

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
	GameObject* LoadFile(string Path);
	void BufferMesh(Mesh* mesh);
	void RemoveMesh(Mesh* mesh);
	bool CleanUp();

	void BoundingBox(Mesh* mesh);
	
	void Draw();

private:

	Mesh* ImportMesh(aiMesh* aiMesh);
	string ImportTexture(const aiScene* scene, int index, string path);
	GameObject* ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, string Path);

public:
	vector<Mesh*> meshes;
	string file_path = "";
	vector<Primitive*> gObjPrimList;


private:
	
}; 

#endif // ModuleGeoLoader