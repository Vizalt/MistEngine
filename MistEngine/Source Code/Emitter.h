#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"

class GameObject;
class Component;

struct Particle {

	float3 pos;
	Quat rot;
	float3 scale;
	float speed;
	float lifetime;

	float elapsedtime;
};

class CEmitter : public Component

{
public:

	CEmitter();
	CEmitter(GameObject* owner);
	~CEmitter();

	bool Update();

	void Inspector();

};