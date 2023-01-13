#include "Application.h"
#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() {
	
	ParticleList.resize(1000);	
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::Update() {

	for (int i = 0; i < ParticleList.size(); i++)
	{
		if (!ParticleList[i].Active)
			continue;

		if (ParticleList[i].LifeTime <= 0.0f)
		{
			ParticleList[i].Active = false;
			continue;
		}

		ParticleList[i].LifeTime -= Application::GetApp()->dt;
		ParticleList[i].pos += ParticleList[i].speed * Application::GetApp()->dt;		
	}
}

void ParticleSystem::Render() {

}

void Particle::SetTransformMatrix()
{
	float x = rot.x * DEGTORAD;
	float y = rot.y * DEGTORAD;
	float z = rot.z * DEGTORAD;

	Quat q = Quat::FromEulerXYZ(x, y, z);

	transformMat = float4x4::FromTRS(pos, q, scale).Transposed();
}

float4x4 Particle::GetTransformMatrix()
{
	return transformMat;
}