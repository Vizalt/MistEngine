#pragma once
#include "Globals.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "imgui.h"

#include <vector>
#include <string>

enum class ComponentType;
class Component;
class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(GameObject* parent);

	void InspectorWindow();

	void CreateComponent(Component* type);

	GameObject* GetParent();
	CMesh* ReturnMeshComp();

	Transform* transform;

	std::string name;
	char string[128] = "gameObject";
	std::vector<Component*> components;
	GameObject* parent;
	std::vector<GameObject*> children;

};
