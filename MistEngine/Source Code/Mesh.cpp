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
	//mesh = nullptr;
}

CMesh::CMesh(GameObject* owner) : Component(owner)
{
	type = ComponentType::MESH;
	meshType = MeshType::FBX;
	this->owner = owner;
	CreatePrimitive();
	//mesh = nullptr;
}

CMesh::CMesh(GameObject* owner, MeshType _meshType) : Component(owner)
{
	type = ComponentType::MESH;
	meshType = _meshType;
	this->owner = owner;
	CreatePrimitive();
	//mesh = nullptr;
}

CMesh::~CMesh()
{
	//Delete Meshes array
	for (int i = 0; i < meshes.size(); i++) {
		Application::GetApp()->loader->RemoveMesh(meshes[i]);
		delete meshes[i];
		meshes[i] = nullptr;
	}
	meshes.clear();
	
	//mesh = nullptr;
	delete GObjPrim;
}


void CMesh::UpdateAABB()
{
	for (int i = 0; i < meshes.size(); i++) {
		if (meshes[i] == nullptr)return;

		meshes[i]->obb = meshes[i]->localAABB;
		meshes[i]->obb.Transform(owner->transform->GetTransformMatrix().Transposed());

		meshes[i]->aabb.SetNegativeInfinity();
		meshes[i]->aabb.Enclose(meshes[i]->obb);
	}
}

void CMesh::Inspector()
{
	
	switch (meshType)
	{
	case(MeshType::FBX):
		if (ImGui::CollapsingHeader("Mesh"))
		{
			for (int i = 0; i < meshes.size(); i++) {
			ImGui::LabelText("##%f", "Mesh %i - Vertex num:", i+1);
			ImGui::SameLine();
			ImGui::Text("%d", meshes[i]->num_vertices);
			}
		}
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		break;

	case(MeshType::CUBE):
		if (ImGui::CollapsingHeader("Cube"))
		{
			GObjPrim->Inspector();
		}
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		break;

	case(MeshType::SPHERE):
		if (ImGui::CollapsingHeader("Sphere"))
		{
			GObjPrim->Inspector();
		}
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		break;

	case(MeshType::CYLINDER):
		if (ImGui::CollapsingHeader("Cylinder"))
		{
			GObjPrim->Inspector();
		}
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		break;

	case(MeshType::LINE):
		if (ImGui::CollapsingHeader("Line"))
		{
			GObjPrim->Inspector();
		}
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		break;

	case(MeshType::PLANE):
		if (ImGui::CollapsingHeader("Plane"))
		{
			GObjPrim->Inspector();
		}
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
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

