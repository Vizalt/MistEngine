//#pragma once
#include "Globals.h"
#include "MathGeoLib.h"

#include <vector>
#include <string>

struct Particle
{
	float3 pos;
	Quat rot;
	float3 scale;
	float lifetime;
	float4 speed;
};

class ParticleSystem {

	std::vector<ParticleEmitter> emitters;

};

class ParticleEmitter {

	std::string name;


	
};