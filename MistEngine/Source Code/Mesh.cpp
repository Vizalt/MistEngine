#include "Application.h"
#include "Mesh.h"
#include "GameObject.h"
#include "ModuleGeoLoader.h"
#include "Transform.h"


CMesh::CMesh() : Component(nullptr)
{
	type = ComponentType::MESH;
	meshType = MeshType::FBX;
	owner = nullptr;
	mesh = nullptr;
}

CMesh::CMesh(GameObject* owner) : Component(owner)
{
	type = ComponentType::MESH;
	meshType = MeshType::FBX;
	this->owner = owner;
	CreatePrimitive();
	mesh = nullptr;
}

CMesh::CMesh(GameObject* owner, MeshType _meshType) : Component(owner)
{
	type = ComponentType::MESH;
	meshType = _meshType;
	this->owner = owner;
	CreatePrimitive();
	mesh = nullptr;
}

CMesh::~CMesh()
{
	Application::GetApp()->loader->RemoveMesh(mesh);
	mesh = nullptr;
	delete GObjPrim;
}


void CMesh::Inspector()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImGui::LabelText("##%f", "Number of vertex:");
		ImGui::SameLine();
		if (mesh == nullptr) return;
		ImGui::Text("%d", mesh->num_vertices);
	}
}

void CMesh::CreatePrimitive()
{
	switch (meshType)
	{

	case(MeshType::FBX):
		break;

	case(MeshType::CUBE):
		GObjPrim = new CubeC();
		GObjPrim->transform = owner->transform->lTransform;
		break;

	case(MeshType::SPHERE):
		GObjPrim = new SphereC();
		GObjPrim->transform = owner->transform->lTransform;
		break;

	case(MeshType::CYLINDER):
		GObjPrim = new CylinderC();
		GObjPrim->transform = owner->transform->lTransform;
		break;

	case(MeshType::LINE):
		GObjPrim = new LineC();
		GObjPrim->transform = owner->transform->lTransform;
		break;

	case(MeshType::PLANE):
		GObjPrim = new PlaneC();
		GObjPrim->transform = owner->transform->lTransform;
		break;

	default:
		break;
	}
}

