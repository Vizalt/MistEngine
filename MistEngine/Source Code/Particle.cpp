#include "Application.h"
#include "Particle.h"
#include "Transform.h"
#include "GameObject.h"


Particle::Particle() {

	pos = float3::zero;
	speed = float3::zero;
	rot = 0;
	scale = 0;
	lifeTime = 2;
	elapsedTime = 0;
}

Particle::Particle(GameObject* owner) {
}

Particle::Particle(float3 pos, float rot, float scale, float3 speed, float gravity, float lifetime) {

	this->pos = pos;
	this->rot = rot;
	this->scale = scale;
	this->speed = speed;
	this->gravity = gravity;
	this->lifeTime = lifetime;

	this->elapsedTime = 0;
}

Particle::~Particle()
{

}

bool Particle::Update() {

	speed.y += gravity * Application::GetApp()->dt;
	float3 change = float3(speed);
	change.x *= Application::GetApp()->dt;
	change.y *= Application::GetApp()->dt;
	change.z *= Application::GetApp()->dt;

	pos += change;

	elapsedTime += Application::GetApp()->dt;

	return elapsedTime < lifeTime;
}