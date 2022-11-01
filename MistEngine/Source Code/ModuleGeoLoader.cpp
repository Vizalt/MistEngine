#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleGeoLoader.h"
#include "ModuleWindow.h"
#include "ModuleTexture.h"
#include "GameObject.h"

#include "ModuleRenderer3D.h"
#include "glew.h"
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

GameObject* ModuleGeoLoader::LoadFile(std::string Path)
{
	const aiScene* scene = aiImportFile(Path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		GameObject* gObj = new GameObject(App->hierarchy->roots);

		for (int i = 0; i < scene->mNumMeshes; i++)
		{

			Mesh* mesh = new Mesh();
			// copy vertices
			mesh->num_vertices = scene->mMeshes[i]->mNumVertices;
			mesh->vertices = new float[mesh->num_vertices * VERTICES];
			//memcpy(mesh->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * mesh->num_vertices * 3);
			
			for (int k = 0; k < mesh->num_vertices; k++) {

				mesh->vertices[k * VERTICES] = scene->mMeshes[i]->mVertices[k].x;
				mesh->vertices[k * VERTICES + 1] = scene->mMeshes[i]->mVertices[k].y;
				mesh->vertices[k * VERTICES + 2] = scene->mMeshes[i]->mVertices[k].z;

				mesh->vertices[k * VERTICES + 3] = scene->mMeshes[i]->mTextureCoords[0][k].x;
				mesh->vertices[k * VERTICES + 4] = 1 - scene->mMeshes[i]->mTextureCoords[0][k].y;

			}

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

				mesh->id_texture = App->texture->textureID;
				mesh->texture_height = App->texture->textureWidth;
				mesh->texture_width = App->texture->textureWidth;

				//meshes.push_back(mesh);
				BufferMesh(mesh);
				CMesh* component = new CMesh(gObj);
				component->mesh = mesh;
				gObj->components.push_back(component);

			}
			else {
				
				delete mesh;
			}
		}
		aiReleaseImport(scene);

		return gObj;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_vertices * VERTICES, mesh->vertices, GL_STATIC_DRAW);

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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);

	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTICES, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTICES, (void*)(sizeof(float) * 3));
	// � bind and use other buffers

	glBindTexture(GL_TEXTURE_2D, id_texture);
	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);

	glPushMatrix();

	if (Owner != nullptr) {
		glMultMatrixf(&Owner->transform->lTransform);
	}

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	//cleaning texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
	
}
