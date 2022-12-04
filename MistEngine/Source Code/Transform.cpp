#include "Transform.h"



Transform::Transform() : Component(nullptr)
{
	
}

Transform::Transform(GameObject* owner) : Component(owner)
{
	type = ComponentType::TRANSFORM;
	this->owner = owner;

	lTransform = float4x4::identity;

	position = float3::zero;
	rotation = float3::zero;
	scale = float3::one;
}

Transform::~Transform()
{
}

void Transform::SetTransformMatrix()
{
	float x = rotation.x * DEGTORAD;
	float y = rotation.y * DEGTORAD;
	float z = rotation.z * DEGTORAD;

	Quat q = Quat::FromEulerXYZ(x, y, z);

	lTransform = float4x4::FromTRS(position, q, scale).Transposed();
}

void Transform::Inspector()
{
	if (owner->parent != nullptr) {


		if (ImGui::CollapsingHeader("Transform"))
		{
			ImGui::Text("X\t\t Y\t\t Z");
			ImGui::InputFloat3("Position", position.ptr());

			ImGui::Text("X\t\t Y\t\t Z");
			ImGui::InputFloat3("Rotation", rotation.ptr());

			ImGui::Text("X\t\t Y\t\t Z");
			ImGui::InputFloat3("Scale", scale.ptr());
		}
		SetTransformMatrix();

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
	}
		
}

float4x4 Transform::GetTransformMatrix()
{
	if (owner->parent == nullptr) {
		return lTransform;
	}
	else {
		return lTransform * owner->parent->transform->GetTransformMatrix();
	}
}