#include "Transform.h"



Transform::Transform() : Component(nullptr)
{
	
}

Transform::Transform(GameObject* owner) : Component(owner)
{
	type = ComponentType::TRANSFORM;
	this->owner = owner;

	position = { 0, 0, 0 };
	rotation = { 0, 0, 0 };
	scale = { 1, 1, 1 };
}

Transform::~Transform()
{
}

void Transform::SetTransformMatrix(float3 _position, float3 _rotation, float3 _scale)
{
	float x = _rotation.x * DEGTORAD;
	float y = _rotation.y * DEGTORAD;
	float z = _rotation.z * DEGTORAD;

	lTransform[0][0] = cos(y) * cos(z);
	lTransform[1][0] = -cos(x) * sin(z) + sin(y) * cos(z) * sin(x);
	lTransform[2][0] = sin(x) * sin(z) + sin(y) * cos(z) * cos(x);
	lTransform[3][0] = _position.x;

	lTransform[0][1] = cos(y) * sin(z);
	lTransform[1][1] = cos(x) * cos(z) + sin(y) * sin(z) * sin(z);
	lTransform[2][1] = -sin(x) * cos(z) + sin(y) * sin(z) * cos(x);
	lTransform[3][1] = _position.y;

	lTransform[0][2] = -sin(y);
	lTransform[1][2] = cos(y) * sin(x);
	lTransform[2][2] = cos(x) * cos(y);
	lTransform[3][2] = _position.z;

	lTransform[0][3] = 0;
	lTransform[1][3] = 0;
	lTransform[2][3] = 0;
	lTransform[3][3] = 1;

	lTransform[0][0] *= _scale.x;
	lTransform[1][1] *= _scale.y;
	lTransform[2][2] *= _scale.z;


	if (owner->parent->transform != nullptr) 
	{
		glTransformT = owner->parent->transform->glTransformT * lTransform;
		//glTransformT = glTransformT.Transposed();
	}
	else {
		glTransformT = lTransform;
	}

	for(int i = 0; i < owner->children.size(); i++) 
	{
		Transform* childTransf = owner->children[i]->transform;
		childTransf->SetTransformMatrix(position, rotation, scale);
	}

}

void Transform::Inspector()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Position", position.ptr());

		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Rotation", rotation.ptr());

		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Scale", scale.ptr());
	}
	

	SetTransformMatrix(position, rotation, scale);
}

void Transform::BoxMesh()
{
	if (mesh == nullptr)return;

	//mesh->obb = mesh->localAABB;
	//mesh->obb.Transform(owner);
}

void Transform::RefreshTransformMatrix()
{
	SetTransformMatrix(position, rotation, scale);
}

