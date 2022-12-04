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

	//lTransform[0][0] = cos(y) * cos(z) * scale.x;
	//lTransform[1][0] = -cos(x) * sin(z) + sin(y) * cos(z) * sin(x);
	//lTransform[2][0] = sin(x) * sin(z) + sin(y) * cos(z) * cos(x);
	//lTransform[3][0] = position.x;

	//lTransform[0][1] = cos(y) * sin(z);
	//lTransform[1][1] = cos(x) * cos(z) + sin(y) * sin(z) * sin(z) * scale.y;
	//lTransform[2][1] = -sin(x) * cos(z) + sin(y) * sin(z) * cos(x);
	//lTransform[3][1] = position.y;

	//lTransform[0][2] = -sin(y);
	//lTransform[1][2] = cos(y) * sin(x);
	//lTransform[2][2] = cos(x) * cos(y) * scale.z;
	//lTransform[3][2] = position.z;

	//lTransform[0][3] = 0;
	//lTransform[1][3] = 0;
	//lTransform[2][3] = 0;
	//lTransform[3][3] = 1;
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



//void Transform::BoxMesh()
//{
//	if (mesh == nullptr)return;
//
//	//mesh->obb = mesh->localAABB;
//	//mesh->obb.Transform(owner);
//}
