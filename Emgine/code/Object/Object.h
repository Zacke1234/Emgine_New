#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Shader\Lighting.h"
#include "Collider.h"
#include <vector>
#include <iostream>
#include "MeshManager.h"
#include <Cube.h>
#include "Util/GLChecking.h"
#include <Rigidbody.h>



class Cube;
struct Mesh;
struct LightData;

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		__debugbreak();
	}
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif


class Object
{
private:


	Shader* MyShader;
	Cube* myCube;

public:

	Object(std::string _namn, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* coll, Rigidbody* rb);

	static std::vector<Object*> Entities;
	static int SelectedEntity;

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
	void SetShader(Shader& aShader);
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
	
	LightObject(std::string _namn, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* coll, LightData* myLightData, Rigidbody* rb);

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

	CameraObject(std::string _namn, Mesh* Mesh, Texture* aTexture, Shader* aShader, Collider* coll, Camera* cam, Rigidbody* rb);

	static std::vector<CameraObject*> CameraEntities;
	static int SelectedCameraEntity;

	void SetCamera(Camera& cam);
	
};