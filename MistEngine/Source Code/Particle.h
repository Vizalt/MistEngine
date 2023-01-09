#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"

class GameObject;
class Component;

class Particle {

	float3 pos, rot, scale;
	float speed;
	float lifetime;
	float elapsedtime;

	Particle();
	Particle(float3 pos, float3 rot, float3 scale, float speed, float lifetime);
	Particle(GameObject* owner);
	~Particle();

	bool Update();
};