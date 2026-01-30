#include <Object.h>
#include "Physics.h"
#include <cassert>
#include <glad.h>
#include <thread>
#include <mutex>
#include "Texture.h" 

std::mutex mtx;

using namespace std;

vector<Object*> Object::Entities;
int Object::SelectedEntity;
//vector<Object*> SelectedEntityVec;
int LightObject::SelectedLightEntity;
vector<LightObject*> LightObject::LightEntities;
vector<CameraObject*> CameraObject::CameraEntities;
// Objects should hold all my meshes and lights
// Meshes should hold meshses like teapots, fishes and cubes
// Lighting should have lights, like directional, pointlight and spotlight etc (is that lightdata?)



Object::Object(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, Rigidbody* rb = NULL)
{
	
	ObjType = Type_Mesh;
		// Name
	if (_namn != "new_object")
	{
		this->namn = _namn;
	}

		//Components
	if (Mesh)
	{
		SetMesh(*Mesh);
		
	}
	else {
		std::cout << "No mesh assigned to object: " << _namn << "\n";
	}
	if (aTexture)
	{
		SetTexture(*aTexture);

	}
	else {
		std::cout << "No texture assigned to object: " << _namn << "\n";
	}
	if (aShader)
	{
		SetShader(*aShader);
	}
	else {
		std::cout << "No shader assigned to object: " << _namn << "\n";
	}
	if (aCollider)
	{
		SetCollider(*aCollider);
	}
	else {
		std::cout << "No collider assigned to object: " << _namn << "\n";
	}
	if(rb)
	{
		SetRigidbody(*rb);
	}
	else {
		std::cout << "No rigidbody assigned to object: " << _namn << "\n";
	}
	
}

LightObject::LightObject(std::string _namn = "new_lightObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, LightData* aLightData = NULL, Rigidbody* rb = NULL)
{
	ObjType = Type_Light;
	// Name
	if (_namn != "new_lightObject")
	{
		this->namn = _namn;
	}

	//Components
	if (Mesh)
	{
		SetMesh(*Mesh);
		//CreateMesh(Mesh);
	}
	else {
		std::cout << "No mesh assigned to light object: " << _namn << "\n";
	}
	if (aTexture)
	{
		SetTexture(*aTexture);
		//SetMaterial(*aTexture->myMaterial);
	}
	else {
		std::cout << "No texture assigned to light object: " << _namn << "\n";
	}
	if (aShader)
	{
		SetShader(*aShader);
	}
	else {
		std::cout << "No shader assigned to light object: " << _namn << "\n";
	}
	if (aCollider)
	{
		SetCollider(*aCollider);
	}
	else {
		std::cout << "No collider assigned to light object: " << _namn << "\n";
	}
	if (aLightData)
	{
		SetLightData(*aLightData);
	}
	else
	{
		std::cout << "No light data assigned to light object: " << _namn << "\n";
	}
	if (rb)
	{
		SetRigidbody(*rb);
	}
	else {
		std::cout << "No rigidbody assigned to object: " << _namn << "\n";
	}
}

CameraObject::CameraObject(std::string _namn = "new_cameraObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* _shader = NULL, Collider* coll = NULL, Camera* _camera = NULL, Rigidbody* rb = NULL)
{
	ObjType = Type_Camera;
	// Name
	if (_namn != "new_lightObject")
	{
		this->namn = _namn;
	}
	else {
		std::cout << "No name assigned to object: " << _namn << "\n";
	}
	// Camera
	if (_camera)
	{
		this->myCamera = _camera;
	}
	else {
		std::cout << "No camera assigned to object: " << _namn << "\n";
	}

	// shader
	if (_shader)
	{
		SetShader(*_shader);
	}
	else {
		std::cout << "No shader assigned to object: " << _namn << "\n";
	}
	//Components
	if (Mesh)
	{
		SetMesh(*Mesh);
		//CreateMesh(Mesh);
	}
	else {
		std::cout << "No mesh assigned to light object: " << _namn << "\n";
	}
	if (aTexture)
	{
		SetTexture(*aTexture);
		//SetMaterial(*aTexture->myMaterial);
	}
	else {
		std::cout << "No texture assigned to light object: " << _namn << "\n";
	}
	if (coll)
	{
		SetCollider(*coll);
	}
	else {
		std::cout << "No collider assigned to light object: " << _namn << "\n";

	}
	if (rb)
	{
		SetRigidbody(*rb);
	}
	else {
		std::cout << "No rigidbody assigned to object: " << _namn << "\n";
	}
}

void Object::SetCube(Cube& aCube)
{
	
	myCube = &aCube;
}

void Object::SetMesh(Mesh& mesh)
{
	myMesh = &mesh;
	
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
}

void Object::SetTexture(Texture& aTexture)
{
	myTexture = &aTexture;
}

void Object::SetShader(Shader& aShader)
{
	MyShader = &aShader;
}

void Object::SetCollider(Collider& aCollider)
{
	myCollider = &aCollider;
	myCollider->position = this->Position;
	
	myCollider->extents = Scale;
	//myCollider->SetTheCollision();
}

void LightObject::SetLightData(LightData& lightdata)
{
	
	myLightData = &lightdata;
	myLightData->lightPos = this->Position;
	
}

void LightObject::SetDirectional(LightData* aLightData)
{
	std::cout << "Directional light" << std::endl;
	aLightData->LightVar = aLightData->DirLight;
}

void LightObject::SetPoint(LightData* aLightData)
{
	std::cout << "Pointlight" << std::endl;
	aLightData->LightVar = aLightData->PointLight;
}

void LightObject::SetSpot(LightData* aLightData)
{
	std::cout << "Spotlight" << std::endl;
	aLightData->LightVar = aLightData->SpotLight;
}

//void Object::SetLighting(Lighting& myLighting)
//{
//	type = ObjectType::Type_Light;
//	//lighting = &myLighting;
//}

Mesh* Object::CreateMesh(Mesh* mesh) 
{
	
	mesh = new Mesh();
	mesh = myMesh;
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
	return mesh;
}

void Object::SetName(std::string name)
{
	namn = name;
}

void Object::SetRigidbody(Rigidbody& rb)
{
	myRigidbody = &rb;
	myRigidbody->isKinematic = false;
}

void CameraObject::SetCamera(Camera& cam)
{
	myCamera = &cam;
}

void Object::Draw(Camera* aCamera, Shader* myShader)
{
	DrawObject(aCamera, myShader);
	
}

void Object::DrawCube(Camera* aCamera, Shader* myShader)
{
	//thread T2(&Draw, this, aCamera);
	myCube->Draw(myShader, this, aCamera);
}

void Object::UpdateTransform(Shader* myShader)
{
	
	trans = Math::identity4;

	trans = glm::translate(trans, Position);

	trans = glm::rotate(trans, Rotation.x, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, Rotation.y, glm::vec3(0, 1, 0));
	trans = glm::rotate(trans, Rotation.z, glm::vec3(0, 0, 1));

	trans = glm::scale(trans, Scale);
	//MyShader->SetMatrix("transform", trans);
	
	IsTransformValid = true; 
}

void Object::DrawObject(Camera* aCamera, Shader* myShader)
{
		if (myMesh == NULL)
		{
			//std::cout << "No mesh to draw in Object: " << namn << "\n";
			return;
		}
		//Mesh* newMesh = new Mesh();
		//std::cout << "draw object in Object" << "\n";
		if (IsTransformValid == false)
		{
			/*thread T1(&Object::UpdateTransform);
			T1.join();*/
			UpdateTransform(myShader);

		}
		

		myShader->SetMatrix("transform", trans);

		
		myShader->SetMatrix("view", aCamera->myView);
		
		myShader->SetMatrix("projection", aCamera->projection);

		
		if (myTexture != NULL)
		{
			GL_CHECK(glActiveTexture(GL_TEXTURE0)); // Activate the texture unit before binding texture
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject));
			GL_CHECK(glActiveTexture(GL_TEXTURE0));
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject));

			
			GL_CHECK(glActiveTexture(GL_TEXTURE1));
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, myTexture->TextureObject));
			if (myTexture->myMaterial != NULL && myShader->ShaderProgram != 6)
			{
				MyShader->SetInt("material.diffuse", myTexture->myMaterial->diffuse);
				MyShader->SetInt("material.specular", myTexture->myMaterial->specular);
				MyShader->SetFloat("material.shininess", myTexture->myMaterial->shininess);
				MyShader->SetVec3("material.objectColor", myTexture->myMaterial->color);
			}
			

		}
		
		
		GL_CHECK(glBindVertexArray(myMesh->VAO));
		GL_CHECK(glDrawElements(GL_TRIANGLES, myMesh->elements.size(), GL_UNSIGNED_INT, (void*)0));
		
		GL_CHECK(glBindVertexArray(0));

		IsTransformValid = false;
}

