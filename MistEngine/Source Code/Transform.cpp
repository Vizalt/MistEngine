#include "Transform.h"


Transform::Transform() : Component(nullptr)
{

}

Transform::Transform(GameObject* owner) : Component(owner)
{
	this->owner = owner;

	position = { 0, 0, 0 };
	rotation = { 0, 0, 0 };
	scale = { 1, 1, 1 };
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
	lTransform[10] = cos(x) * cos(y);
	lTransform[11] = _position.z;

	lTransform[12] = 0;
	lTransform[13] = 0;
	lTransform[14] = 0;
	lTransform[15] = 1;

	lTransform[0] *= _scale.x;
	lTransform[5] *= _scale.y;
	lTransform[10] *= _scale.z;


	/*if (owner->parent->transform != nullptr) 
	{
		glTransform = owner->parent->transform->glTransform * lTransform;
		glTransformT = transpose(glTransform);
	}*/

	lTransform = transpose(lTransform);

}

void Transform::Inspector()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Position", &position);

		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Rotation", &rotation);

		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Scale", &scale);
	}
	

	SetTransformMatrix(position, rotation, scale);
}

