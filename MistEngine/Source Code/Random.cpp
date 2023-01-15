#include "Random.h"

void Random::Init()
{
	srand(static_cast <unsigned> (time(0)));
}

float Random::RandomFloat()
{
	//Random number from 0.0 to 1.0
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	return r;
}
