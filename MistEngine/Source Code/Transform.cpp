#include "Transform.h"


Transform::Transform() : Component(nullptr)
{

}

Transform::Transform(GameObject* owner) : Component(owner)
{
	
}

Transform::~Transform()
{
}

void Transform::SetTransformMatrix(vec3 _position, vec3 _rotation, vec3 _scale)
{
	float x = _rotation.x * DEGTORAD;
	float y = _rotation.y * DEGTORAD;
	float z = _rotation.z * DEGTORAD;

	lTransform[0] = cos(y) * cos(z);
	lTransform[1] = -cos(x) * sin(z) + sin(y) * cos(z) * sin(x);
	lTransform[2] = sin(x) * sin(z) + sin(y) * cos(z) * cos(x);
	lTransform[3] = _position.x;

	lTransform[4] = cos(y) * sin(z);
	lTransform[5] = cos(x) * cos(z) + sin(y) * sin(z) * sin(z);
	lTransform[6] = -sin(x) * cos(z) + sin(y) * sin(z) * cos(x);
	lTransform[7] = _position.y;

	lTransform[8] = -sin(y);
	lTransform[9] = cos(y) * sin(x);
	lTransform[10] = cos(x) * sin(y);
	lTransform[11] = _position.z;

	lTransform[12] = 0;
	lTransform[13] = 0;
	lTransform[14] = 0;
	lTransform[15] = 1;

	lTransform[0] *= _scale.x;
	lTransform[5] *= _scale.y;
	lTransform[10] *= _scale.z;

	if (owner->parent->transform != nullptr) 
	{
		glTransform = owner->parent->transform->glTransform * lTransform;
		glTransformT = transpose(glTransform);
	}

}

void Transform::Inspector()
{
	ImGui::CollapsingHeader("Transform");
	ImGui::Text("Position\tX");
	ImGui::SameLine;
	ImGui::InputFloat("x", &position.x);
	ImGui::SameLine;
	ImGui::Text("Y");
	ImGui::SameLine;
	ImGui::InputFloat("y", &position.y);
	ImGui::SameLine;
	ImGui::Text("Z");
	ImGui::SameLine;
	ImGui::InputFloat("z", &position.z);

	ImGui::Text("Rotation\tX");
	ImGui::SameLine;
	ImGui::InputFloat("x", &rotation.x);
	ImGui::SameLine;
	ImGui::Text("Y");
	ImGui::SameLine;
	ImGui::InputFloat("y", &rotation.y);
	ImGui::SameLine;
	ImGui::Text("Z");
	ImGui::SameLine;
	ImGui::InputFloat("z", &rotation.z);

	ImGui::Text("Scale\tX");
	ImGui::SameLine;
	ImGui::InputFloat("x", &scale.x);
	ImGui::SameLine;
	ImGui::Text("Y");
	ImGui::SameLine;
	ImGui::InputFloat("y", &scale.y);
	ImGui::SameLine;
	ImGui::Text("Z");
	ImGui::SameLine;
	ImGui::InputFloat("z", &scale.z);

	SetTransformMatrix(position, rotation, scale);
}

