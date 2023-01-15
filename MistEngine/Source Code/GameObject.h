#pragma once
#include "Globals.h"
#include "imgui.h"
#include "MathGeoLib.h"

#include <vector>
#include <string>

enum class ComponentType;
class Component;
class Transform;
class CMesh;
class CCamera;
class CEmitter;

class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(GameObject* parent);

	void InspectorWindow();

	void CreateComponent(ComponentType type);

	void DeleteChild(GameObject* child);
	bool ChangeParent(GameObject* NewParent);
	bool CheckChildOf(GameObject* parent);

	//void DeleteChild(GameObject child);

	GameObject* GetParent();
	CMesh* GetComponentMesh();
	GameObject* GetCompMesh();
	CCamera* GetComponentCamera();
	CEmitter* GetComponentEmitter();

	void FixRotationYZ();

	void UpdateRecu();

	Transform* transform;
	
	bool fixed;
	std::string name;
	char string[128] = "gameObject";
	std::vector<Component*> components;
	GameObject* parent;
	std::vector<GameObject*> children;

	bool active = false, explosion = false;
	int LifeTime;
	float3 speed;

};
