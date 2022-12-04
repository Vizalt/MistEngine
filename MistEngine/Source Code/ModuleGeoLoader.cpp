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
#include "Camera.h"


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


void Mesh::InnitAABB() {
	float* vertices_positions = new float[num_vertices * 3];
	for (size_t i = 0; i < num_vertices; i++)
	{
		vertices_positions[i * 3] = vertices[i * VERTICES];
		vertices_positions[i * 3 + 1] = vertices[i * VERTICES + 1];
		vertices_positions[i * 3 + 2] = vertices[i * VERTICES + 2];
	}

	localAABB.SetNegativeInfinity();
	localAABB.Enclose((float3*)vertices_positions, num_vertices);
	delete[] vertices_positions;
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


		finalObj->FixRotationYZ();

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


void ModuleGeoLoader::Draw()
{
	App->camera->sceneCam->printCount = 0;

	for (int i = 0; i< meshes.size(); i++) {

		if (!App->camera->sceneCam->ContainsAaBox(meshes[i])) continue;

		meshes[i]->Draw();
		App->camera->sceneCam->printCount ++;
	}

	for (int i = 0; i < gObjPrimList.size(); i++) {
		gObjPrimList[i]->Render();
	}

}

void ModuleGeoLoader::DrawGame()
{
	App->renderer3D->mainCam->printCount = 0;

	for (int i = 0; i < meshes.size(); i++) {

		if (!App->renderer3D->mainCam->ContainsAaBox(meshes[i])) continue;

		meshes[i]->Draw();
		App->renderer3D->mainCam->printCount++;
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

		if (aiMesh->mTextureCoords[0] == nullptr) continue;
		mesh->vertices[k * VERTICES + 3] = aiMesh->mTextureCoords[0][k].x;
		mesh->vertices[k * VERTICES + 4] = aiMesh->mTextureCoords[0][k].y;

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

		mesh->InnitAABB();

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
			MaterialIndex->GetTexture(aiTextureType_DIFFUSE, 0, &TextPath);

			for (int i = 0; i < path.size(); i++)
			{
				if (path[i] == '\\')
				{
					path[i] = '/';
				}
			}

			string NormTextPath = TextPath.C_Str();

			for (int i = 0; i < NormTextPath.size(); i++)
			{
				if (NormTextPath[i] == '\\')
				{
					NormTextPath[i] = '/';
				}
			}

			string AssetsPath = path;
			uint AssetsPos = AssetsPath.find("Assets/");

			AssetsPath = AssetsPath.substr(AssetsPos, AssetsPath.find_last_of("/") - AssetsPos);
			AssetsPath.append("/").append(TextPath.C_Str());

			return AssetsPath;
		}
	}

	return "";
}

GameObject* ModuleGeoLoader::ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, string Path)
{

	if (node->mNumMeshes == 0 && node->mNumChildren == 0) return nullptr;

	GameObject* gObj = new GameObject(parent);

	gObj->name = node->mName.C_Str();


	aiMatrix4x4 TransformMat = node->mTransformation;

	aiVector3D scale, position, rotation;
	aiQuaternion QuatRotation;

	TransformMat.Decompose(scale, QuatRotation, position);
	rotation = QuatRotation.GetEuler();

	gObj->transform->scale = float3(scale.x, scale.y, scale.z);
	gObj->transform->position = float3(position.x, position.y, position.z);
	gObj->transform->rotation = float3(rotation.x * RADTODEG, rotation.y * RADTODEG, rotation.z * RADTODEG);
	gObj->transform->SetTransformMatrix();

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
