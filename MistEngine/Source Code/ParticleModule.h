#pragma once
#include "Globals.h"
#include "MathGeoLib.h"

#include <vector>
#include <string>

enum class ParticleType
{
	SCREEN,
	WORLD,
	AXIS,
};

class ParticleModule {
	
	void Spawn();
	void Update();
};