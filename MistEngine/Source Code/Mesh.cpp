#include "Mesh.h"
#include "GameObject.h"
#include "ModuleGeoLoader.h"

CMesh::CMesh() : Component(nullptr)
{
	owner = nullptr;
}

CMesh::CMesh(GameObject* owner) : Component(owner)
{
	this->owner = owner;
}

CMesh::~CMesh()
{
	for (int i = 0; i < meshList.size(); i++) {
		delete meshList[i];
		meshList[i] = nullptr;
	}
	meshList.clear();
}


void CMesh::Inspector()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		for (int i = 0; i < meshList.size(); i++) {
			ImGui::Text("Mesh %d", i + 1);
			ImGui::LabelText("##%f", "-Number of vertex:");
			ImGui::SameLine();
			if (meshList[i] == nullptr) return;
			ImGui::Text("%d", meshList[i]->num_vertices);
		}
	}
}

