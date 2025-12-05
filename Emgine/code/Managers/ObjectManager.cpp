#include "ObjectManager.h"

Object* ObjectManager::Create(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, Rigidbody* rb = NULL)
{
	
	Object* obj = new Object(_namn, Mesh, aTexture, aShader, aCollider, rb);
	
	Object::Entities.push_back(obj);
	
	return obj;
}

void ObjectManager::Destroy(Object* obj) {
	
	/*obj->myMesh = NULL;
	obj->myCollider = NULL;*/
	
	for (int i = Object::Entities.size() - 1; i >= 0; i--)
	{
		if (Object::Entities[i]) // crashes if i delete the last object int the list
		{
			Object::SelectedEntity = i;
			obj->Entities.erase(std::remove(obj->Entities.begin(), obj->Entities.end(), obj), obj->Entities.end());
			//++i;
			std::cout << "Object destroyed\n";
			
		}
	}
	//
	//  room.erase(room.begin()+2);
	//Object::Entities.erase(obj->Entities.at());
	//Object::Entities.pop_back();
	
}

LightObject* ObjectManager::CreateLight(std::string aName = "new_lightObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, LightData* aLightData = NULL, Rigidbody* rb = NULL)
{
	LightObject* lightObj = new LightObject(aName, Mesh, aTexture, aShader, aCollider, aLightData, rb);
	Object::Entities.push_back(lightObj);
	LightObject::LightEntities.push_back(lightObj);
	return lightObj;
}

CameraObject* ObjectManager::CreateCamera(std::string aName = "new_cameraObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, Camera* aCamera = NULL, Rigidbody* rb = NULL)
{
	CameraObject* cameraObj = new CameraObject(aName, Mesh, aTexture, aShader, aCollider, aCamera, rb);
	Object::Entities.push_back(cameraObj);
	CameraObject::CameraEntities.push_back(cameraObj);
	return cameraObj;
}

Object* ObjectManager::FindAndSetProperties(std::string aName, glm::vec3 aPos, glm::vec3 aScale, glm::vec3 aRot)
{
	for (Object* object : Object::Entities)
	{
		if (object->namn == aName)
		{
			std::cout << "Object found: " << aName << "\n";
			object->Position = aPos;
			object->Scale = aScale;
			object->Rotation = aRot;
			return object;
		}
	}
	std::cout << "Object not found: " << aName << "\n";
	return nullptr;
}

// Lightdata is part of Object Yes?
// So Do I have lightdata in object.h/cpp?
// and slash or?
// ponder on this

// Obviously I want a object to be able to hold a light, depending on whatever
// that light is 