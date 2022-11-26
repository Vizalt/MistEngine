#pragma once
#include "Globals.h"
#include "Component.h"
#include "Transform.h"
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

	void CreateComponent(ComponentType type);

	GameObject* GetParent();
	GameObject* ToParent(GameObject* NParent);//Move obj to new parent
	GameObject* NewChild(GameObject* childObj);//Adds the child to the parent
	void DeleteChild(GameObject* child);
	bool checkChild(GameObject* obj);

	Transform* transform;

	std::string name;
	char string[128] = "gameObject";
	std::vector<Component*> components;
	GameObject* parent;
	std::vector<GameObject*> children;

};
