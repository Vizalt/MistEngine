#pragma once
#include "Globals.h"
#include "Component.h"
#include "Transform.h"

#include <vector>
#include <string>

enum class ComponentType;
class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(GameObject* parent);

	void CreateComponent(ComponentType type);

	Transform* transform;

	std::string name;
	std::vector<Component*> components;
	GameObject* parent;
	std::vector<GameObject*> children;
};
