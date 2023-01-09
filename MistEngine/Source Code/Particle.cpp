#include "Application.h"
#include "Particle.h"
#include "Transform.h"
#include "GameObject.h"


Particle::Particle() {
	pos = float3::zero;
	rot = float3::zero;
	scale = float3::zero;
	speed = 1;
	lifetime = 2;
	elapsedtime = 0;
}

Particle::Particle(GameObject* owner) {
}

Particle::~Particle()
{

}