#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"

class GameObject;
class Component;
struct Mesh;

class CMesh : public Component
{
public:

	CMesh();
	CMesh(GameObject* owner);
	~CMesh();

	Mesh* mesh;
	
	void Inspector();
};