#include "LightingManager.h"
#pragma once
std::vector<LightData*> lightsList;
//LightObject::LightEntities.size();
//Camera* Cameron = new Camera();
// 
// shadow mapping  







int PointLightShaderSetting(Shader* shader, LightData* aLightData) // done
{
	
	for (int lObjs = 0; lObjs < Lighting::pointLights.size(); lObjs++)
	{
		std::string number = std::to_string(lObjs);
		//pointLightPositions.push_back(&aLightData->lightPos);
		//shader->SetInt("NR_POINTLIGHTS", lObjs);
		//shader->SetInt("PLight[" + number + "]", 0.0f);
		shader->SetInt("NumPointLights", Lighting::pointLights.size());

		shader->SetFloat("pointLight[" + number + "].constant", aLightData->constant); // Something wrong with these sets
		shader->SetFloat("pointLight[" + number + "].linear", aLightData->linear);
		shader->SetFloat("pointLight[" + number + "].quadratic", aLightData->quadtric);

		std::string temp1 = "pointLight[";  temp1.append(number);
		std::string temp2 = "pointLight["; temp2.append(number);
		std::string temp3 = "pointLight["; temp3.append(number);
		std::string temp4 = "pointLight["; temp4.append(number);

		std::string tempAmb = "].ambient";
		std::string tempDiff = "].diffuse";
		std::string tempSpec = "].specular";
		std::string tempPos = "].position";
		std::string ambient = temp1.append(tempAmb);
		std::string diffuse = temp2.append(tempDiff);
		std::string specular = temp3.append(tempSpec);
		std::string position = temp4.append(tempPos);


		shader->SetVec3(ambient.c_str(), *Lighting::ambients[lObjs]); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), *Lighting::diffuses[lObjs]);

		shader->SetVec3(specular.c_str(), *Lighting::speculars[lObjs]);

		shader->SetVec3(position.c_str(), *Lighting::pointLightPositions[lObjs]);
		
		/*shader->SetVec3("pointLight[0].position", glm::vec3(4, 3, 1));
		shader->SetVec3("pointLight[1].position", glm::vec3(1, -3, 1));
		shader->SetVec3("pointLight[2].position", glm::vec3(7, 0, 2));*/
	}
	
	
	
	//std::cout << "obj" << std::endl;
	
	//b++;
	
	//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
	


	return 0;
}

int SpotLightShaderSetting(Shader* shader, LightData* aLightData)
{
	glm::vec3 positions[] = { aLightData->lightDir };
	
	for (int lObjs = 0; lObjs < Lighting::spotLights.size(); lObjs++)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		//shader->SetInt("NR_SPOTLIGHTS", lObjs);
		
		shader->SetInt("NumSpotLights", Lighting::spotLights.size());
		shader->SetFloat("spotLight[" + number + "].constant", aLightData->constant);
		shader->SetFloat("spotLight[" + number + "].linear", aLightData->linear);
		shader->SetFloat("spotLight[" + number + "].quadratic", aLightData->quadtric);
		shader->SetFloat("spotLight[" + number + "].cutOff", glm::cos(glm::radians(aLightData->cutOff)));
		shader->SetFloat("spotLight[" + number + "].outerCutOff", aLightData->outerCutOff);

		std::string temp1 = "spotLight[";  temp1.append(number);
		std::string temp2 = "spotLight["; temp2.append(number);
		std::string temp3 = "spotLight["; temp3.append(number);
		std::string temp4 = "spotLight["; temp4.append(number);
		std::string temp5 = "spotLight["; temp5.append(number);

		std::string tempAmb = "].ambient";
		std::string tempDiff = "].diffuse";
		std::string tempSpec = "].specular";
		std::string tempPos = "].position";
		std::string tempDir = "].direction";
		std::string ambient = temp1.append(tempAmb);
		std::string diffuse = temp2.append(tempDiff);
		std::string specular = temp3.append(tempSpec);
		std::string position = temp4.append(tempPos);
		std::string direction = temp5.append(tempDir);


		shader->SetVec3(ambient.c_str(), aLightData->ambient); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), aLightData->diffuse);

		shader->SetVec3(specular.c_str(), aLightData->specular);

		shader->SetVec3(position.c_str(), aLightData->lightPos);

		shader->SetVec3(direction.c_str(), aLightData->lightDir);



	}
	return 0;
}

int DirectionalLightSetting(Shader* shader, LightData* aLightData)
{
	for (int lObjs = 0; lObjs < Lighting::dirLights.size(); lObjs++)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);

		//shader->SetInt("NR_DIRLIGHTS", lObjs);
		shader->SetInt("NumDirectionalLights", Lighting::dirLights.size());
		shader->SetFloat("dirLight[" + number + "].constant", aLightData->constant);
		shader->SetFloat("dirLight[" + number + "].linear", aLightData->linear);
		shader->SetFloat("dirLight[" + number + "].quadratic", aLightData->quadtric);
		//shader->SetInt("DLight[" + number + "].lights", lObjs);

		std::string temp1 = "dirLight[";  temp1.append(number);
		std::string temp2 = "dirLight["; temp2.append(number);
		std::string temp3 = "dirLight["; temp3.append(number);
		std::string temp4 = "dirLight["; temp4.append(number);
		std::string temp5 = "dirLight["; temp5.append(number);

		std::string tempAmb = "].ambient";
		std::string tempDiff = "].diffuse";
		std::string tempSpec = "].specular";
		std::string tempDir = "].direction";
		std::string ambient = temp1.append(tempAmb);
		std::string diffuse = temp2.append(tempDiff);
		std::string specular = temp3.append(tempSpec);
		std::string direction = temp4.append(tempDir);
		std::string uniform = temp5.append("]");

		shader->SetVec3(ambient.c_str(), aLightData->ambient); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), aLightData->diffuse);

		shader->SetVec3(specular.c_str(), aLightData->specular);

		shader->SetVec3(direction.c_str(), aLightData->lightDir);

		//shader->SetMatrix(uniform.c_str(), lObjs);
		//std::cout << "Directional lights: " + number << std::endl;


	}
	return 0;
}
LightData* LightingManager::InitDefaultLighting()
{
	DefaultLighting = new LightData();
	return DefaultLighting;
}
LightData* LightingManager::Create(std::string name, Shader* shader, LightData* aLightData)
{
	aLightData = new LightData();
	aLightData->Name = name;


	SetPoint(aLightData, NULL);
	//SetDirectional(light, NULL);
	//InitialiseLightData(shader, light);
	
	return aLightData;
}

LightData* LightingManager::SetDirectional(LightData* aLightData, Object* obj)
{
	if (!obj == NULL) {

		aLightData = obj->Entities[obj->SelectedEntity]->myLightData;
	}
	Lighting::dirLights.push_back(aLightData);
	aLightData->lightDir = { -0.2f, -1.0f, -0.3f };
	std::cout << "Directional light" << std::endl;
	aLightData->LightVar = aLightData->DirLight;
	return aLightData;
}

LightData* LightingManager::SetPoint(LightData* aLightData, Object* obj)
{
	Lighting::pointLightPositions.push_back(&aLightData->lightPos);
	Lighting::speculars.push_back(&aLightData->specular);
	Lighting::diffuses.push_back(&aLightData->diffuse);
	Lighting::ambients.push_back(&aLightData->ambient);
	Lighting::constants.push_back(&aLightData->constant);
	Lighting::quadtrics.push_back(&aLightData->quadtric);

	//Lighting::pointLightPositions->length();
	if (!obj == NULL) {
		
		aLightData = obj->Entities[obj->SelectedEntity]->myLightData;
	}
	
	Lighting::pointLights.push_back(aLightData);
	
	obj->Entities[obj->SelectedEntity]->Position = aLightData->lightPos;
	aLightData->ambient = { 0.3, 0.3, 0.3 };
	aLightData->diffuse = { 0.3, 0.3, 0.3 };
	aLightData->specular = { 0.3, 0.3, 0.3 };
	aLightData->constant = 0.3;
	aLightData->linear = 0.3;
	aLightData->quadtric = 0.3;

	
	std::cout << "Pointlight" << std::endl;
	aLightData->LightVar = aLightData->PointLight;
	return aLightData;
}

LightData* LightingManager::SetSpot(LightData* aLightData, Object* obj)
{
	if (!obj == NULL) {

		aLightData = obj->Entities[obj->SelectedEntity]->myLightData;
	}
	Lighting::spotLights.push_back(aLightData);
	std::cout << "Spotlight" << std::endl;
	aLightData->LightVar = aLightData->SpotLight;
	return aLightData;
}

glm::vec3 zeros = { 0.0f,0.0f,0.0f };

LightData* LightingManager::RunLightData(Shader* shader, LightData* aLightData, Camera* aCamera)
{
	
	
	//int lightSpaceMatrixLocation;

	if (aLightData == NULL)
	{
		return 0;
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}
	
	//glm::mat4 lightProjection = ; // X, Y, Z, W ?
	//// the light wouldn't have this if it's a point light, cause point light is not directional

	//glm::mat4 view = aCamera->GetViewMatrix();
	//shader->SetMatrix("view", view);
	
	
	//glUniform1f(aLightData->, )
	PointLightShaderSetting(shader, aLightData);

	
	/*DirectionalLightSetting(shader, aLightData);

	
	SpotLightShaderSetting(shader, aLightData);*/


	




	//}
	return 0;
}



void LightingManager::Destroy(Lighting* light, LightData* lightData)
{
	Destroy(light, lightData);
}
