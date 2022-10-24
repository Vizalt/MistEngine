#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleGeoLoader.h"
#include "ModuleWindow.h"

#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "Primitive.h"



ModuleGeoLoader::ModuleGeoLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleGeoLoader::~ModuleGeoLoader()
{

}

// -----------------------------------------------------------------
bool ModuleGeoLoader::Start()
{
	bool ret = true;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	file_path = "Assets/BakerHouse.fbx";

	LoadFile(file_path);

	return ret;
}

// -----------------------------------------------------------------
update_status ModuleGeoLoader::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleGeoLoader::Update(float dt)
{

	

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleGeoLoader::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

void ModuleGeoLoader::LoadFile(std::string Path)
{
	const aiScene* scene = aiImportFile(Path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh* mesh = new Mesh();
			// copy vertices
			mesh->num_vertices = scene->mMeshes[i]->mNumVertices;
			mesh->vertices = new float[mesh->num_vertices * 3];
			memcpy(mesh->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * mesh->num_vertices * 3);
			LOG("New mesh with %d vertices", mesh->num_vertices);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				mesh->num_indices = scene->mMeshes[i]->mNumFaces * 3;
				mesh->indices = new uint[mesh->num_indices]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");
					}	
					else 
					{
						memcpy(&mesh->indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
						
				}
				//meshes.push_back(mesh);
				BufferMesh(mesh);
			}
			else {
				
				delete mesh;
			}
		}
		aiReleaseImport(scene);
	}
	else {
		LOG("Error loading scene %s", Path);
	}
}

void ModuleGeoLoader::BufferMesh(Mesh* mesh)
{
	//Fill buffers with vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, (GLuint*)&(mesh->id_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_vertices * 3, mesh->vertices, GL_STATIC_DRAW);

	//Fill buffers with indices
	glGenBuffers(1, (GLuint*)&(mesh->id_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->num_indices, mesh->indices, GL_STATIC_DRAW);

	glDisableClientState(GL_VERTEX_ARRAY);

	//Add mesh to meshes vector
	meshes.push_back(mesh);
}

// -----------------------------------------------------------------
bool ModuleGeoLoader::CleanUp()
{
	//Delete Meshes array
	for (int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
		meshes[i] = nullptr;
	}
	meshes.clear();
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}

void ModuleGeoLoader::Draw()
{
	for (int i = 0; i< meshes.size(); i++) {
		meshes[i]->Draw();
	}
}

void Mesh::Draw()
{
	//Vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// … bind and use other buffers
	

	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	/*glBegin(GL_TRIANGLES);

	for (int i = 0; i < num_indices; i++) 
	{
		glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
	}

	glEnd();*/

	
}
