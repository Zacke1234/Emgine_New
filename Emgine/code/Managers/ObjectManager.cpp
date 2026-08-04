#include "ObjectManager.h"
#include <ShaderManager.h>



Object* ObjectManager::Create(std::string _namn = "new_object", Mesh* Mesh = NULL, Texture* aTexture = NULL,  Collider* aCollider = NULL, Rigidbody* rb = NULL)
{
	
	obj = new Object(_namn, Mesh, aTexture, aCollider, rb);
	
	Object::Entities.push_back(obj);
	
	return obj;
}


void ObjectManager::Destroy(Object* thisObject) {
	
	int MaxSize = Object::Entities.size();

	
	Object::Entities.erase(Object::Entities.begin() + Object::SelectedEntity);
	delete(thisObject);
	
	if (MaxSize == Object::SelectedEntity + 1)
	{
		
		Object::SelectedEntity -= 1;
		
	}
	int b = 0;
	
	
}

void ObjectManager::DestroyLight(Object* obj, Shader* aShader, LightingManager aLightManager)
{
	if (Object::Entities[Object::SelectedEntity]->ObjType == 1)
	{

		aLightManager.Destroy(aShader, obj);
		Object::Entities.erase(Object::Entities.begin() + Object::SelectedEntity);

		if (Object::SelectedEntity >= Object::Entities.size())
		{
			if (Object::SelectedEntity != 0)
			{
				Object::SelectedEntity -= 1;
			}

		}
	}
	
}

LightObject* ObjectManager::CreateLight(std::string aName = "new_lightObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Collider* aCollider = NULL, LightData* aLightData = NULL, Rigidbody* rb = NULL)
{
	if (aLightData == NULL)
	{
		aLightData = new LightData();
	}
	LightObject* lightObj = new LightObject(aName, Mesh, aTexture, aCollider, aLightData, rb);
	 aLightData->lightPos = lightObj->Position;
	Object::Entities.push_back(lightObj);
	LightObject::LightEntities.push_back(lightObj);
	return lightObj;
}

CameraObject* ObjectManager::CreateCamera(std::string aName = "new_cameraObject", Mesh* Mesh = NULL, Texture* aTexture = NULL, Collider* aCollider = NULL, Camera* aCamera = NULL, Rigidbody* rb = NULL)
{
	if (aCamera == NULL)
	{
		aCamera = new Camera(NULL, "createdCamera");
	}
	CameraObject* cameraObj = new CameraObject(aName, Mesh, aTexture, aCollider, aCamera, rb);
	Object::Entities.push_back(cameraObj);
	CameraObject::CameraEntities.push_back(cameraObj);
	return cameraObj;
}

TerrainObject* ObjectManager::CreateTerrain(std::string aName = "newTerrainObject", Terrain* terr = NULL, Texture* aTexture = NULL, Collider* aCollider = NULL)
{
	if (terr == NULL)
	{
		terr = new Terrain();
	}
	
	TerrainObject* terrObj = new TerrainObject(aName, terr, aTexture, aCollider);
	terrObj->Scale = glm::vec3(1, 1, 1);
	terr->terrainMesh->isTerrain = true;
	
	/*terr->terrainMesh->InitialiseMesh();
	MeshManager::MeshList.push_back(terrObj->namn);
	MeshManager::MeshCache.push_back(*terr->terrainMesh);*/
	 
	Object::Entities.push_back(terrObj);
	TerrainObject::TerrainObjects.push_back(terrObj);
	return terrObj;
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