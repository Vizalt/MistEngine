#include "Application.h"
#include "Particle.h"
#include "Transform.h"
#include "GameObject.h"


Particle::Particle() {
	pos = float3::zero;
	rot = float3::zero;
	scale = float3::zero;
	speed = float3::zero;
	lifetime = 2;
	elapsedtime = 0;
}

Particle::Particle(GameObject* owner) {
}

Particle::Particle(float3 pos, float3 rot, float3 scale, float3 speed, float gravity, float lifetime) {
	this->pos = pos;
	this->rot = rot;
	this->scale = scale;
	this->speed = speed;
	this->gravity = gravity;
	this->lifetime = lifetime;
}

Particle::~Particle()
{

}

bool Particle::Update() {
	
	speed.y += gravity * Application::GetApp()->MsFrame;
	float3 change = float3(speed);
	change.x *= Application::GetApp()->MsFrame;
	change.y *= Application::GetApp()->MsFrame;
	change.z *= Application::GetApp()->MsFrame;

	return true;
}