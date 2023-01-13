#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"

class GameObject;
class Component;

class CEmitter : public Component
{
public:

	CEmitter();
	CEmitter(GameObject* owner);
	~CEmitter();

	bool Update();

	void Inspector();

};