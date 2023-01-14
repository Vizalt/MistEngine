#include "Application.h"
#include "Emitter.h"
#include "Transform.h"
#include "ModuleParticles.h"


CEmitter::CEmitter() : Component(nullptr)
{
	type = ComponentType::EMITTER;
	owner = nullptr;

	//Default Particle
	particleProps.pos = float3::zero;
	particleProps.rot = float3::zero;
	particleProps.scale = float3::one;
	particleProps.speed = float3::one;
	particleProps.speedVariation = float3::one;
	particleProps.Color = float4(255.0f, 255.0f, 255.0f, 1.0f); //r g b a

	particleProps.LifeTime = 1.0f;

	textureID = Application::GetApp()->texture->checkerID;
	particleSystem.textID = Application::GetApp()->texture->checkerID;
	particleSystem.ParticleBuffer();

	Application::GetApp()->particle->emitterVector.push_back(this);
}

CEmitter::CEmitter(GameObject* owner) : Component(owner)
{
	type = ComponentType::EMITTER;
	this->owner = owner;

	//Default Particle
	particleProps.pos = owner->transform->position;
	particleProps.rot = float3::zero;
	particleProps.scale = float3::one;
	particleProps.speed = float3::one;
	particleProps.speedVariation = float3::one;
	particleProps.Color = float4(255.0f, 255.0f, 255.0f, 1.0f); //r g b a

	particleProps.LifeTime = 1.0f;

	textureID = Application::GetApp()->texture->checkerID;
	particleSystem.textID = Application::GetApp()->texture->checkerID;
	particleSystem.ParticleBuffer();

	Application::GetApp()->particle->emitterVector.push_back(this);
}

CEmitter::~CEmitter()
{
	
}

void CEmitter::Update()
{	
	particleSystem.Emit(particleProps);

	particleSystem.Update();

}

void CEmitter::RenderParticles()
{
	particleSystem.Render();
}

void CEmitter::Inspector()
{

	if (ImGui::CollapsingHeader("Particle Emitter"))
	{
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Particle Scale", particleProps.scale.ptr());
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Speed", particleProps.speed.ptr());
		ImGui::InputFloat("Life Time", &particleProps.LifeTime);
		ImGui::ColorEdit4("Birth Color", particleProps.Color.ptr());

		if (ImGui::Checkbox("Particle Texture\t", &particleProps.texture));
	}

	RefreshParticleText();

	ImGui::NewLine();
	ImGui::Separator();
	ImGui::NewLine();
}

void CEmitter::RefreshParticleText()
{
	uint text = 0;

	if (particleProps.texture) {
		text = textureID;
	}
	else {
		text = 0;
	}
	
	particleSystem.textID = text;
}
