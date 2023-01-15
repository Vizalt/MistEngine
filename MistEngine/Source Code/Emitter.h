#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "MathGeoLib.h"
#include "ParticleSystem.h"

class GameObject;
class Component;

class CEmitter : public Component
{
public:

	CEmitter();
	CEmitter(GameObject* owner);
	~CEmitter();

	void Update();

	void RenderParticles();

	void Inspector();

	void RefreshParticleText();

	

	bool PrintText = true;

	GLuint textureID = 0;

	ParticleProps particleProps;
	ParticleSystem particleSystem;
};