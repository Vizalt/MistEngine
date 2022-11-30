#pragma once
#include "Globals.h"
#include "imgui.h"

#include "Transform.h"
#include "Mesh.h"

#include <vector>
#include <string>

enum class ComponentType;
class Component;
class Transform;
class CMesh;

class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(GameObject* parent);

	void InspectorWindow();

	void CreateComponent(ComponentType type);

	//void DeleteChild(GameObject child);

	GameObject* GetParent();
	CMesh* GetComponentMesh();

	Transform* transform;

	std::string name;
	char string[128] = "gameObject";
	std::vector<Component*> components;
	GameObject* parent;
	std::vector<GameObject*> children;

};
