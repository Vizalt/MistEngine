#pragma once
#include "SDL.h"
#include <vector>
#include <string>

enum class ComponentType
{
	TRANSFORM,
	MESH,
	TEXTURE,
};

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void CreateComponent(ComponentType type);

	std::string name;
	std::vector<Component*> Components;
	GameObject* parent;
	std::vector<GameObject*> children;
};


class Component
{
public:
	Component();
	~Component();

	ComponentType type;
	bool active;
	GameObject* owner;
};
