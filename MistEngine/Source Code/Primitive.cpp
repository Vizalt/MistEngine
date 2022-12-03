#include "Globals.h"
#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Primitive.h"


// ------------------------------------------------------------
Primitive::Primitive() : transform(float4x4::identity), color(White), wire(false), axis(false), type(PrimitiveTypes::Primitive_Point)
{}

Primitive::Primitive(float4x4 _transform) : transform(_transform), color(White), wire(false), axis(false), type(PrimitiveTypes::Primitive_Point)
{}

// ------------------------------------------------------------
PrimitiveTypes Primitive::GetType() const
{
	return type;
}

// ------------------------------------------------------------
void Primitive::Render() const
{
	glPushMatrix();
	glMultMatrixf(transform.ptr());

	if(axis == true)
	{
		// Draw Axis Grid
		glLineWidth(2.0f);

		glBegin(GL_LINES);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
		glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
		glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
		glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

		glEnd();

		glLineWidth(1.0f);
	}

	glColor3f(color.r, color.g, color.b);

	if(wire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	InnerRender();

	glPopMatrix();
}

// ------------------------------------------------------------
void Primitive::InnerRender() const
{
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glPointSize(1.0f);
}

void Primitive::Inspector()
{
}


// CUBE ============================================
CubeC::CubeC() : Primitive(), size(1.0f, 1.0f, 1.0f), pos(0, 0, 0)
{
	type = PrimitiveTypes::Primitive_Cube;
}

CubeC::CubeC(float sizeX, float sizeY, float sizeZ) : Primitive(), size(sizeX, sizeY, sizeZ), pos(0, 0, 0)
{
	type = PrimitiveTypes::Primitive_Cube;
}

void CubeC::InnerRender() const
{	
	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;
	float sz = size.z * 0.5f;

	glTranslatef(pos[0], pos[1], pos[2]);
	glBegin(GL_QUADS);

	//glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-sx, -sy, sz);
	glVertex3f( sx, -sy, sz);
	glVertex3f( sx,  sy, sz);
	glVertex3f(-sx,  sy, sz);

	//glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f( sx, -sy, -sz);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx,  sy, -sz);
	glVertex3f( sx,  sy, -sz);

	//glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(sx, -sy,  sz);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(sx,  sy, -sz);
	glVertex3f(sx,  sy,  sz);

	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx, -sy,  sz);
	glVertex3f(-sx,  sy,  sz);
	glVertex3f(-sx,  sy, -sz);

	//glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-sx, sy,  sz);
	glVertex3f( sx, sy,  sz);
	glVertex3f( sx, sy, -sz);
	glVertex3f(-sx, sy, -sz);

	//glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f( sx, -sy, -sz);
	glVertex3f( sx, -sy,  sz);
	glVertex3f(-sx, -sy,  sz);


	glEnd();
}

void CubeC::Inspector()
{
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Position", pos.ptr());
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Size", size.ptr());
}

// SPHERE ============================================
SphereC::SphereC() : Primitive(), radius(1.0f), pos(0, 0, 0)
{
	type = PrimitiveTypes::Primitive_Sphere;
}

SphereC::SphereC(float3 _pos, float _radius) : Primitive(), radius(_radius), pos(_pos)
{
	type = PrimitiveTypes::Primitive_Sphere;
}

void SphereC::InnerRender() const
{
	GLUquadric* glQ = gluNewQuadric();
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	gluSphere(glQ, radius, 25, 25);
	gluDeleteQuadric(glQ);
}

void SphereC::Inspector()
{
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Position", pos.ptr());
	ImGui::Text("");
	ImGui::InputFloat("Radius", &radius);
}

// CYLINDER ============================================
CylinderC::CylinderC() : Primitive(), radius(1.0f), pos(0, 0, 0), height(3.0f)
{
	type = PrimitiveTypes::Primitive_Cylinder;
}

CylinderC::CylinderC(float3 _pos, float _radius, float _height) : Primitive(), radius(_radius), pos(_pos), height(_height)
{
	type = PrimitiveTypes::Primitive_Cylinder;
}

void CylinderC::InnerRender() const
{
	GLUquadric* glQ = gluNewQuadric();
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	gluCylinder(glQ, radius, radius, height, 30, 1);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(glQ, 0.0f, radius, 30, 1);
	glPopMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluDisk(glQ, 0.0f, radius, 30, 1);
	gluDeleteQuadric(glQ);
}

void CylinderC::Inspector()
{
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Position", pos.ptr());
	ImGui::Text("");
	ImGui::InputFloat("Radius", &radius);
	ImGui::Text("");
	ImGui::InputFloat("Height", &height);
}

// LINE ==================================================
LineC::LineC() : Primitive(), origin(0, 0, 0), destination(1, 1, 1)
{
	type = PrimitiveTypes::Primitive_Line;
}

LineC::LineC(float3 _destination) : Primitive(), origin(0, 0, 0), destination(_destination)
{
	type = PrimitiveTypes::Primitive_Line;
}

LineC::LineC(float3 _origin, float3 _destination) : Primitive(), origin(_origin), destination(_destination)
{
	type = PrimitiveTypes::Primitive_Line;
}

void LineC::InnerRender() const
{
	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glVertex3f(origin.x, origin.y, origin.z);
	glVertex3f(destination.x, destination.y, destination.z);

	glEnd();

	glLineWidth(1.0f);
}

void LineC::Inspector()
{
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Origin", origin.ptr());
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Destination", destination.ptr());
}

// PLANE ==================================================
PlaneC::PlaneC() : Primitive(), normal(0, 1, 0), constant(1), pos(0, 0, 0)
{
	type = PrimitiveTypes::Primitive_Plane;
}

PlaneC::PlaneC(float3 _normal, float d) : Primitive(), normal(_normal), constant(d), pos(0, 0, 0)
{
	type = PrimitiveTypes::Primitive_Plane;
}

void PlaneC::InnerRender() const
{
	glLineWidth(1.0f);
	
	glBegin(GL_LINES);

	glTranslatef(pos[0], pos[1], pos[2]);

	float d = 200.0f;

	for(float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
}

void PlaneC::Inspector()
{
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Position", pos.ptr());
	ImGui::Text("X\t\t Y\t\t Z");
	ImGui::InputFloat3("Normal", normal.ptr());
	ImGui::Text("");
	ImGui::InputFloat("Constant", &constant);

}
