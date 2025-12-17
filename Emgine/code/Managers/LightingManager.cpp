#include "LightingManager.h"
#pragma once
std::vector<LightData*> lightsList;
//LightObject::LightEntities.size();
//Camera* Cameron = new Camera();
// 
// shadow mapping  


glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};




int PointLightShaderSetting(Shader* shader, LightData* aLightData) // done
{
	


	for (int lObjs = 0; lObjs < LightData::pointLights.size(); lObjs++)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		
		//shader->SetInt("NR_POINTLIGHTS", lObjs);
		//shader->SetInt("PLight[" + number + "]", 0.0f);
		shader->SetInt("NumPointLights", lObjs);
		shader->SetFloat("pointLight[" + number + "].constant", aLightData->constant);
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


		shader->SetVec3(ambient.c_str(), aLightData->ambient); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), aLightData->diffuse);

		shader->SetVec3(specular.c_str(), aLightData->specular);

		shader->SetVec3(position.c_str(), aLightData->lightPos);




	}


	return 0;
}

int SpotLightShaderSetting(Shader* shader, LightData* aLightData)
{
	for (int lObjs = 0; lObjs <= LightData::spotLights.size(); lObjs++)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		//shader->SetInt("NR_SPOTLIGHTS", lObjs);
		
		shader->SetInt("NumSpotLights", LightData::spotLights.size());
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
	for (int lObjs = 0; lObjs < LightData::dirLights.size(); ++lObjs)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);

		//shader->SetInt("NR_DIRLIGHTS", lObjs);
		shader->SetInt("NumDirectionalLights", LightData::dirLights.size());
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
LightData* LightingManager::Create(std::string name, Shader* shader, LightData* light)
{
	light = new LightData();
	light->Name = name;
	
	SetPoint(light, NULL);
	//SetDirectional(light, NULL);
	//InitialiseLightData(shader, light);
	
	return light;
}

LightData* LightingManager::SetDirectional(LightData* aLightData, Object* test)
{
	if (!test == NULL) {

		aLightData = test->Entities[test->SelectedEntity]->myLightData;
	}
	LightData::dirLights.push_back(aLightData);
	aLightData->lightDir = { -0.2f, -1.0f, -0.3f };
	std::cout << "Directional light" << std::endl;
	aLightData->LightVar = aLightData->DirLight;
	return aLightData;
}

LightData* LightingManager::SetPoint(LightData* aLightData, Object* test)
{
	if (!test == NULL) {
		
		aLightData = test->Entities[test->SelectedEntity]->myLightData;
	}
	LightData::pointLights.push_back(aLightData);
	test->Entities[test->SelectedEntity]->Position = aLightData->lightPos;
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

LightData* LightingManager::SetSpot(LightData* aLightData, Object* test)
{
	if (!test == NULL) {

		aLightData = test->Entities[test->SelectedEntity]->myLightData;
	}
	LightData::spotLights.push_back(aLightData);
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
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}
	
	//glm::mat4 lightProjection = ; // X, Y, Z, W ?
	//// the light wouldn't have this if it's a point light, cause point light is not directional

	//glm::mat4 view = aCamera->GetViewMatrix();
	//shader->SetMatrix("view", view);
	
	
	//glUniform1f(aLightData->, )
	PointLightShaderSetting(shader, aLightData);

	
	DirectionalLightSetting(shader, aLightData);

	
	SpotLightShaderSetting(shader, aLightData);


	




	//}
	return 0;
}



void LightingManager::Destroy(Lighting* light, LightData* lightData)
{
	Destroy(light, lightData);
}
