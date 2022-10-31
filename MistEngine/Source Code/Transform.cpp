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

void Transform::SetTransformMatrix(vec3 position, vec3 rotation, vec3 scale)
{
	float x = rotation.x * DEGTORAD;
	float y = rotation.y * DEGTORAD;
	float z = rotation.z * DEGTORAD;

	lTransform[0] = cos(y) * cos(z);
	lTransform[1] = -cos(x) * sin(z) + sin(y) * cos(z) * sin(x);
	lTransform[2] = sin(x) * sin(z) + sin(y) * cos(z) * cos(x);
	lTransform[3] = position.x;

	lTransform[4] = cos(y) * sin(z);
	lTransform[5] = cos(x) * cos(z) + sin(y) * sin(z) * sin(z);
	lTransform[6] = -sin(x) * cos(z) + sin(y) * sin(z) * cos(x);
	lTransform[7] = position.y;

	lTransform[8] = -sin(y);
	lTransform[9] = cos(y) * sin(x);
	lTransform[10] = cos(x) * sin(y);
	lTransform[11] = position.z;

	lTransform[12] = 0;
	lTransform[13] = 0;
	lTransform[14] = 0;
	lTransform[15] = 1;

	lTransform[0] *= scale.x;
	lTransform[5] *= scale.y;
	lTransform[10] *= scale.z;
}

