#include "Application.h"
#include "Mesh.h"
#include "GameObject.h"
#include "ModuleGeoLoader.h"


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
	
	switch (meshType)
	{
	case(MeshType::FBX):
		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::LabelText("##%f", "Number of vertex:");
			ImGui::SameLine();
			if (mesh == nullptr) return;
			ImGui::Text("%d", mesh->num_vertices);
		}
		break;
	case(MeshType::CUBE):
		if (ImGui::CollapsingHeader("Cube"))
		{
			GObjPrim->Inspector();
		}
		break;
	case(MeshType::SPHERE):
		if (ImGui::CollapsingHeader("Sphere"))
		{
			GObjPrim->Inspector();
		}
		break;
	case(MeshType::CYLINDER):
		if (ImGui::CollapsingHeader("Cylinder"))
		{
			GObjPrim->Inspector();
		}
		break;
	case(MeshType::LINE):
		if (ImGui::CollapsingHeader("Line"))
		{
			GObjPrim->Inspector();
		}
		break;
	case(MeshType::PLANE):
		if (ImGui::CollapsingHeader("Plane"))
		{
			GObjPrim->Inspector();
		}
		break;
	default:
		break;
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
		Application::GetApp()->loader->gObjPrimList.push_back(GObjPrim);
		owner->name = "Cube";
		break;

	case(MeshType::SPHERE):
		GObjPrim = new SphereC();
		Application::GetApp()->loader->gObjPrimList.push_back(GObjPrim);
		owner->name = "Sphere";
		break;

	case(MeshType::CYLINDER):
		GObjPrim = new CylinderC();
		Application::GetApp()->loader->gObjPrimList.push_back(GObjPrim);
		owner->name = "Cylinder";
		break;

	case(MeshType::LINE):
		GObjPrim = new LineC();
		Application::GetApp()->loader->gObjPrimList.push_back(GObjPrim);
		owner->name = "Line";
		break;

	case(MeshType::PLANE):
		GObjPrim = new PlaneC();
		Application::GetApp()->loader->gObjPrimList.push_back(GObjPrim);
		owner->name = "Plane";
		break;

	default:
		break;
	}
}

