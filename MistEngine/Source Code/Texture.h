#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"

#include<string>

class GameObject;
class Component;

class CTexture : public Component
{
public:

	CTexture();
	CTexture(GameObject* owner);
	~CTexture();

	GLuint textureID;

	bool PrintLoaded = true;

	void LinkTexture(std::string path);

	void RefreshTexture();

	void Inspector();
};
