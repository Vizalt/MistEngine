#pragma once
#include "Color.h"
#include "MathGeoLib.h"
#include "imgui.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:

	Primitive();
	Primitive(float4x4 _transform);

	virtual void	Render() const;
	virtual void	InnerRender() const;
	virtual void	Inspector();
	PrimitiveTypes	GetType() const;

public:
	
	Color color;
	float4x4 transform;
	bool axis,wire;

protected:
	PrimitiveTypes type;
};

// ============================================
class CubeC : public Primitive
{
public :
	CubeC();
	CubeC(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const;
	void Inspector();
public:
	float3 size;
	float3 pos;
};

class SphereC : public Primitive
{
public:
	SphereC();
	SphereC(float3 _pos, float _radius);
	void InnerRender() const;
	void Inspector();
public:
	float3 pos;
	float radius;
	
};

class CylinderC : public Primitive
{
public:
	CylinderC();
	CylinderC(float3 _pos, float _radius, float _height);
	void InnerRender() const;
	void Inspector();
public:
	float3 pos;
	float radius;
	float height;
};

class LineC : public Primitive
{
public:
	LineC();
	LineC(float3 _destination);
	LineC(float3 _origin, float3 _destination);
	void InnerRender() const;
	void Inspector();
public:
	float3 origin, destination;
};

class PlaneC : public Primitive
{
public:
	PlaneC();
	PlaneC(float3 _normal, float d);
	void InnerRender() const;
	void Inspector();
public:
	float3 pos;
	float3 normal;
	float constant;
};