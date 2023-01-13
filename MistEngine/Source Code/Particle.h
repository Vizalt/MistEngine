#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"

class GameObject;
class Component;

class Particle {

	float3 pos = float3::zero;
	float3 speed = float3::zero;
	float lifeTime = 0;
	float elapsedTime = 0;
	float gravity = 0;
	float rot = 0, scale = 0;

	Particle();
	Particle(float3 pos, float rot, float scale, float3 speed, float gravity, float lifetime);
	Particle(GameObject* owner);
	~Particle();

	bool Update();
};