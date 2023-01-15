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
	particleProps.beginScale = float3::one;
	particleProps.endScale = float3::zero;
	particleProps.speed = float3(0.0f, 1.0f, 0.0f);
	particleProps.speedVariation = float3::one;
	particleProps.Color = float4(255.0f, 255.0f, 255.0f, 1.0f); //r g b a
	particleProps.endColor = float4(0.0f, 0.0f, 0.0f, 0.0f); //r g b a

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
	particleProps.beginScale = float3::one;
	particleProps.endScale = float3::zero;
	particleProps.speed = float3(0.0f, 1.0f, 0.0f);
	particleProps.speedVariation = float3::one;
	particleProps.Color = float4(255.0f, 255.0f, 255.0f, 1.0f); //r g b a
	particleProps.endColor = float4(0.0f, 0.0f, 0.0f, 0.0f); //r g b a

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
	particleProps.pos = owner->transform->position;

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
		ImGui::InputFloat3("Particle Begin Scale", particleProps.beginScale.ptr());
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Particle End Scale", particleProps.endScale.ptr());
		ImGui::NewLine();
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Speed", particleProps.speed.ptr());
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Speed Variaton", particleProps.speedVariation.ptr());
		ImGui::InputFloat("Life Time", &particleProps.LifeTime);
		ImGui::NewLine();
		ImGui::ColorEdit4("Color", particleProps.Color.ptr());
		ImGui::ColorEdit4("End Color", particleProps.endColor.ptr());
		ImGui::Checkbox("Particle Texture\t", &particleProps.texture);
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
