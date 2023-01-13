#include "Application.h"
#include "Emitter.h"
#include "Transform.h"


CEmitter::CEmitter() : Component(nullptr)
{
	type = ComponentType::EMITTER;
	owner = nullptr;
}

CEmitter::CEmitter(GameObject* owner) : Component(owner)
{
	type = ComponentType::EMITTER;
	this->owner = owner;
}

CEmitter::~CEmitter()
{
	
}

void CEmitter::Inspector()
{
	if (ImGui::CollapsingHeader("Particle Emitter"))
	{
		
	}
}
