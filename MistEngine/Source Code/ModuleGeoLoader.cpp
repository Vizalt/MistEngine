#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleGeoLoader.h"
#include "ModuleWindow.h"
#include "ModuleTexture.h"
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
#include "GameObject.h"
#include "Component.h"
#include "Primitive.h"


#include "ModuleHierarchy.h"
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

		GameObject* finalObj = ProcessNode(scene, scene->mRootNode, App->hierarchy->roots, Path);

		aiReleaseImport(scene);

		return finalObj;
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

void ModuleGeoLoader::RemoveMesh(Mesh* mesh)
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		if (meshes[i] == mesh) {
			meshes.erase(meshes.begin() + i);
			delete mesh;
			mesh = nullptr;
			return;
		}
	}

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

void ModuleGeoLoader::BoundingBox(Mesh* mesh)
{
	
	if (mesh == nullptr)return;

	mesh->obb = mesh->localAABB;
	mesh->obb.Transform(mesh->Owner->transform->GetTransformMatrix().Transposed());

	mesh->aabb.SetNegativeInfinity();
	mesh->aabb.Enclose(mesh->obb);

	//// Generate AABB
	//aabb.SetNegativeInfinity();
	//aabb.Enclose((float3*)mesh->vertices, mesh->num_vertices);
}

void ModuleGeoLoader::Draw()
{
	for (int i = 0; i< meshes.size(); i++) {
		meshes[i]->Draw();
	}

	for (int i = 0; i < gObjPrimList.size(); i++) {
		gObjPrimList[i]->Render();
	}

}

Mesh* ModuleGeoLoader::ImportMesh(aiMesh* aiMesh)
{
	Mesh* mesh = new Mesh();
	// copy vertices
	mesh->num_vertices = aiMesh->mNumVertices;
	mesh->vertices = new float[mesh->num_vertices * VERTICES];
	//memcpy(mesh->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * mesh->num_vertices * 3);

	for (int k = 0; k < mesh->num_vertices; k++) {

		mesh->vertices[k * VERTICES] = aiMesh->mVertices[k].x;
		mesh->vertices[k * VERTICES + 1] = aiMesh->mVertices[k].y;
		mesh->vertices[k * VERTICES + 2] = aiMesh->mVertices[k].z;

		mesh->vertices[k * VERTICES + 3] = aiMesh->mTextureCoords[0][k].x;
		mesh->vertices[k * VERTICES + 4] = 1 - aiMesh->mTextureCoords[0][k].y;

	}

	LOG("New mesh with %d vertices", mesh->num_vertices);

	// copy faces
	if (aiMesh->HasFaces())
	{
		mesh->num_indices = aiMesh->mNumFaces * 3;
		mesh->indices = new uint[mesh->num_indices]; // assume each face is a triangle

		for (uint j = 0; j < aiMesh->mNumFaces; j++)
		{
			if (aiMesh->mFaces[j].mNumIndices != 3) {
				LOG("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&mesh->indices[j * 3], aiMesh->mFaces[j].mIndices, 3 * sizeof(uint));
			}

		}

		//meshes.push_back(mesh);
		BufferMesh(mesh);

		return mesh;
	}
	else {

		delete mesh;

		return nullptr;
	}

}

string ModuleGeoLoader::ImportTexture(const aiScene* scene, int index, string path)
{

	if (scene->HasMaterials())
	{
		aiMaterial* MaterialIndex = scene->mMaterials[scene->mMeshes[index]->mMaterialIndex];
		if (MaterialIndex->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString TextPath;
			aiString AssetsPath;
			AssetsPath.Set("Assets/");
			MaterialIndex->GetTexture(aiTextureType_DIFFUSE, 0, &TextPath);

			AssetsPath.Append(TextPath.C_Str());

			return AssetsPath.C_Str();
		}
	}

	return "";
}

GameObject* ModuleGeoLoader::ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, string Path)
{

	if (node->mNumMeshes == 0 && node->mNumChildren == 0) return nullptr;

	GameObject* gObj = new GameObject(parent);

	gObj->name = node->mName.C_Str();

	//node->mTransformation

	if (node->mNumMeshes != 0) {

		CMesh* component = new CMesh(gObj);

		
		string texture_path = "";


		for (int i = 0; i < node->mNumMeshes; i++)
		{
			Mesh* mesh = ImportMesh(scene->mMeshes[node->mMeshes[i]]);

			if (mesh == nullptr) {
				LOG("Error loading scene %s", Path);
				continue;
			}

			mesh->Owner = gObj;
			component->meshes.push_back(mesh);

			if (texture_path == "") texture_path = ImportTexture(scene, node->mMeshes[i], Path);

		}

		gObj->components.push_back(component);
		gObj->fixed = true;

		gObj->transform->SetTransformMatrix();

		if (texture_path != "") {
		CTexture* componentT = new CTexture(gObj);
		gObj->components.push_back(componentT);
		componentT->LinkTexture(texture_path);
		}
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(scene, node->mChildren[i], gObj, Path);
	}

	return gObj;
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
		glMultMatrixf(Owner->transform->GetTransformMatrix().ptr());
	}

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	//cleaning texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
	
}
