#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"

class GameObject;
class Component;

class Particle {

	float3 pos, rot, scale;
	float3 speed;
	float lifetime;
	float elapsedtime;
	float gravity;

	Particle();
	Particle(float3 pos, float3 rot, float3 scale, float3 speed, float gravity, float lifetime);
	Particle(GameObject* owner);
	~Particle();

	bool Update();
};