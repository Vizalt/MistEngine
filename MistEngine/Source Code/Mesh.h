#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "Primitive.h"

#include <vector>

class GameObject;
class Component;
struct Mesh;

enum class MeshType
{
	FBX,
	CUBE,
	SPHERE,
	CYLINDER,
	LINE,
	PLANE,
};

class CMesh : public Component
{
public:

	CMesh();
	CMesh(GameObject* owner);
	CMesh(GameObject* owner, MeshType _meshType);
	~CMesh();

	MeshType meshType;

	//Mesh* mesh;

	std::vector<Mesh*> meshes;

	Primitive* GObjPrim;
	
	void Inspector();
	void CreatePrimitive();
	void RenderPrimitive();
};