#include "Application.h"
#include "Mesh.h"
#include "GameObject.h"
#include "ModuleGeoLoader.h"


CMesh::CMesh() : Component(nullptr)
{
	type = ComponentType::MESH;
	owner = nullptr;
	mesh = nullptr;
}

CMesh::CMesh(GameObject* owner) : Component(owner)
{
	type = ComponentType::MESH;
	this->owner = owner;
	mesh = nullptr;

}

CMesh::~CMesh()
{
	Application::GetApp()->loader->RemoveMesh(mesh);
	mesh = nullptr;
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

