#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Shader\Lighting.h"
#include "Collider.h"
#include <vector>
#include <iostream>
#include "MeshManager.h"
#include "GLChecking.h"
#include <Rigidbody.h>

struct Mesh;
struct LightData;

class Object
{
private:


	Shader* MyShader;
	Cube* myCube;

public:

	Object(std::string _namn, Mesh* Mesh, Texture* aTexture, Collider* coll, Rigidbody* rb);

	static std::vector<Object*> Entities;
	static unsigned int SelectedEntity;

	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;
	glm::vec3 v;
	enum ObjectType
	{

		Type_NULL = 0,
		Type_Light = 1,
		Type_Mesh = 2,
		Type_Cube = 3,
		Type_Camera = 4
	};

	ObjectType ObjType;

	std::string namn;
	bool IsTransformValid;

	glm::mat4 trans;
	Collider* myCollider;

	Mesh* myMesh;
	Rigidbody* myRigidbody;
	Texture* myTexture;
	Camera* myCamera;
	LightData* myLightData;
	
	void SetCube(Cube& aCube); 
	void SetMesh(Mesh& mesh);
	void SetTexture(Texture& aTexture);
	
	void SetCollider(Collider& collider);
	void SetMaterial(Material& material);
	void SetName(std::string name);
	void SetRigidbody(Rigidbody& rb);
	void Draw(Shader* myShader);
	void DrawObject(Shader* myShader);
	void UpdateTransform(Shader* myShader);

	Mesh* CreateMesh(Mesh* mesh);

};

class LightObject : public Object
{
public:
	
	LightObject(std::string _namn, Mesh* Mesh, Texture* aTexture, Collider* coll, LightData* myLightData, Rigidbody* rb);

	static std::vector<LightObject*> LightEntities;
	static int SelectedLightEntity;

	void SetLightData(LightData& lightdata);
	
	void SetDirectional(LightData* aLightData);
	void SetPoint(LightData* aLightData);
	void SetSpot(LightData* aLightData);
	
};

class CameraObject : public Object
{
public:

	CameraObject(std::string _namn, Mesh* Mesh, Texture* aTexture, Collider* coll, Camera* cam, Rigidbody* rb);

	static std::vector<CameraObject*> CameraEntities;
	static int SelectedCameraEntity;

	void SetCamera(Camera& cam);
	
};