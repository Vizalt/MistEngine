#pragma once
#include "Globals.h"
#include "imgui.h"

#include <vector>
#include <string>

enum class ComponentType;
class Component;
class Transform;
class CMesh;
class CCamera;

class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(GameObject* parent);

	void InspectorWindow();

	void CreateComponent(ComponentType type);

	void DeleteChild(GameObject* child);
	bool ChangeParent(GameObject* NewParent);
	bool CheckChildOf(GameObject* parent);

	//void DeleteChild(GameObject child);

	GameObject* GetParent();
	CMesh* GetComponentMesh();
	CCamera* GetComponentCamera();

	Transform* transform;
	
	bool fixed;
	std::string name;
	char string[128] = "gameObject";
	std::vector<Component*> components;
	GameObject* parent;
	std::vector<GameObject*> children;

};
