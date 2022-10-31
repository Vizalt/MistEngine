#pragma once

class GameObject;

enum class ComponentType
{
	NONE,
	TRANSFORM,
	MESH,
	TEXTURE,
};

class Component
{
public:
	Component(GameObject* owner);
	virtual ~Component();

	ComponentType type;
	bool active;
	GameObject* owner;
};
