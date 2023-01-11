#pragma once

class GameObject;

enum class ComponentType
{
	NONE,
	TRANSFORM,
	MESH,
	TEXTURE,
	CAMERA,
	EMITTER,
};

class Component
{
public:
	Component(GameObject* owner);
	virtual ~Component();

	virtual void Inspector();

	ComponentType type;
	bool active;
	GameObject* owner;
};
