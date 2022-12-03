#include "Application.h"
#include "Texture.h"
#include "Mesh.h"
#include "GameObject.h"
#include "ModuleGeoLoader.h"


CTexture::CTexture() : Component(nullptr)
{
	type = ComponentType::TEXTURE;
	owner = nullptr;
}

CTexture::CTexture(GameObject* owner) : Component(owner)
{
	type = ComponentType::TEXTURE;
	this->owner = owner;
}

CTexture::~CTexture()
{
	
}

void CTexture::LinkTexture(std::string path)
{
	if (textureID != 0)
	{
		Application::GetApp()->texture->FreeTexture(textureID);
	}
	textureID = Application::GetApp()->texture->LoadTexture(path);

	RefreshTexture();
}

void CTexture::RefreshTexture()
{
	CMesh* rt = owner->GetComponentMesh();

	if (PrintLoaded)
	{
		rt->mesh->id_texture = textureID;
		return;
	}
	
	rt->mesh->id_texture = Application::GetApp()->texture->checkerID;

}

void CTexture::Inspector()
{
	if (ImGui::CollapsingHeader("Texture"))
	{
		if (ImGui::Checkbox("Loaded Texture\t", &PrintLoaded));
	}
	RefreshTexture();

	ImGui::NewLine();
	ImGui::Separator();
	ImGui::NewLine();
}