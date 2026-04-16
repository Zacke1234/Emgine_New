#include "ObjectManager.h"
#include <ShaderManager.h>



Object* ObjectManager::Create(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, Rigidbody* rb = NULL)
{
	
	Object* obj = new Object(_namn, Mesh, aTexture, aShader, aCollider, rb);
	
	Object::Entities.push_back(obj);
	
	return obj;
}

void ObjectManager::Destroy(Object* obj, Shader* aShader, LightingManager aLightManager) {
	
	if (Object::Entities[Object::SelectedEntity]->ObjType == 1)
	{
		
		aLightManager.Destroy(aShader, obj);
	}
	Object::Entities.erase(Object::Entities.begin() + Object::SelectedEntity);
	// everything with a higher number in the list of the object that was deleted. moves a spot down, everything with a lower number stays still
	// current this has the effect of the object that now has the same index as the old one, will receive all the variables (position, rotation, texture etc) instead of keeping their own variables (FIXED)
	// Still have the problem with crashing if the last object in the list is deleted ( FIXED)
	
	if (Object::SelectedEntity >= Object::Entities.size())
	{
		if (Object::SelectedEntity != 0)
		{
			Object::SelectedEntity -= 1;
		}
		
	}

	
}

LightObject* ObjectManager::CreateLight(std::string aName = "new_lightObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Shader* aShader = NULL, Collider* aCollider = NULL, LightData* aLightData = NULL, Rigidbody* rb = NULL)
{
	LightObject* lightObj = new LightObject(aName, Mesh, aTexture, aShader, aCollider, aLightData, rb);
	 aLightData->lightPos = lightObj->Position;
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