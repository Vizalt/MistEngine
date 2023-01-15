#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"

#include <vector>

class GameObject;
class Component;

struct ParticleProps
{
	float3 pos, rot;
	float3 speed, speedVariation;
	float4 Color, endColor;

	float3 beginScale, endScale, scaleVariaton;

	bool texture = true;

	float LifeTime = 1.0f;
};

struct Particle
{
	float3 pos, rot, scale;
	float4x4 transformMat = float4x4::identity;
	float3 speed;

	float3 beginScale, endScale;

	float LifeTime = 1.0f, LifeRemaining = 0.0f;

	bool Active = false;

	void SetTransformMatrix();
	float4x4 GetTransformMatrix();
};

class ParticleSystem {
public:

	ParticleSystem();
	~ParticleSystem();

	void Update();

	void Emit(ParticleProps& particleProps);

	void ParticleBuffer();
	void Render();

	bool text = true;

	std::vector<Particle> ParticleList;
	uint32_t ListIndex = 999;

	uint id_indices = 0;
	uint id_vertices = 0;
	GLuint textID = 0;
	float4 Color = float4(255.0f, 255.0f, 255.0f, 1.0f);
	float4 endColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 printColor = float4(255.0f, 255.0f, 255.0f, 1.0f);

};