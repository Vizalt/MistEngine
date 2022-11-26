#pragma once
#include "Globals.h"
#include "Component.h"
#include "glmath.h"
#include "imgui.h"

#include <vector>

class GameObject;
class Component;
struct Mesh;


class CMesh : public Component
{
public:

	CMesh();
	CMesh(GameObject* owner);
	~CMesh();

	std::vector<Mesh*> meshList;
	
	void Inspector();
};