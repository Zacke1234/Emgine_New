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
	


	for (int lObjs = 0; lObjs <= LightObject::LightEntities.size(); lObjs++)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		shader->SetInt("PLight[" + number + "]", 0.0f);
		shader->SetFloat("PLight[" + number + "].constant", aLightData->constant);
		shader->SetFloat("PLight[" + number + "].linear", aLightData->linear);
		shader->SetFloat("PLight[" + number + "].quadratic", aLightData->quadtric);

		std::string temp1 = "PLight[";  temp1.append(number);
		std::string temp2 = "PLight["; temp2.append(number);
		std::string temp3 = "PLight["; temp3.append(number);
		std::string temp4 = "PLight["; temp4.append(number);

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
	for (int lObjs = 0; lObjs <= LightObject::LightEntities.size(); lObjs++)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		shader->SetInt("NR_SPOTLIGHTS", lObjs);
		shader->SetFloat("SLight[" + number + "].constant", aLightData->constant);
		shader->SetFloat("SLight[" + number + "].linear", aLightData->linear);
		shader->SetFloat("SLight[" + number + "].quadratic", aLightData->quadtric);
		shader->SetFloat("SLight[" + number + "].cutOff", glm::cos(glm::radians(aLightData->cutOff)));
		shader->SetFloat("SLight[" + number + "].outerCutOff", aLightData->outerCutOff);

		std::string temp1 = "SLight[";  temp1.append(number);
		std::string temp2 = "SLight["; temp2.append(number);
		std::string temp3 = "SLight["; temp3.append(number);
		std::string temp4 = "SLight["; temp4.append(number);
		std::string temp5 = "Slight["; temp5.append(number);

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
	for (int lObjs = 0; lObjs < LightObject::LightEntities.size(); ++lObjs)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		
		shader->SetFloat("DLight[" + number + "].constant", aLightData->constant);
		shader->SetFloat("DLight[" + number + "].linear", aLightData->linear);
		shader->SetFloat("DLight[" + number + "].quadratic", aLightData->quadtric);
		//shader->SetInt("DLight[" + number + "].lights", lObjs);

		std::string temp1 = "DLight[";  temp1.append(number);
		std::string temp2 = "DLight["; temp2.append(number);
		std::string temp3 = "DLight["; temp3.append(number);
		std::string temp4 = "DLight["; temp4.append(number);
		std::string temp5 = "DirectionalLight["; temp5.append(number);

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
		std::cout << "Directional lights: " + number << std::endl;


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
	
	//SetPoint(light, NULL);
	SetDirectional(light, NULL);
	//InitialiseLightData(shader, light);
	
	return light;
}

LightData* LightingManager::SetDirectional(LightData* aLightData, Object* test)
{
	if (!test == NULL) {

		aLightData = test->Entities[test->SelectedEntity]->myLightData;
	}
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
	std::cout << "Spotlight" << std::endl;
	aLightData->LightVar = aLightData->SpotLight;
	return aLightData;
}

LightData* LightingManager::InitialiseLightData(Shader* shader, LightData* aLightData)
{
	float near_plane = 1.0f, far_plane = 7.5f;
	
	//int lightSpaceMatrixLocation;

	if (aLightData == NULL)
	{
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}

	glm::mat4 lightProjection = aLightData->projection; // X, Y, Z, W ?
	glm::mat4 lightView = glm::lookAt(glm::vec3(aLightData->lightDir.x, aLightData->lightDir.y, aLightData->lightDir.z),
		glm::vec3(aLightData->lightDir.x, aLightData->lightDir.y, aLightData->lightDir.z),
		glm::vec3(aLightData->lightDir.x, aLightData->lightDir.y, aLightData->lightDir.z));

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	switch (aLightData->LightVar)
	{
	case 0:

		//std::cout << "Null light" << std::endl;
		/*shader->SetVec3("baseLight.position", { 0,0,0 });
		shader->SetVec3("baseLight.direction", { 0,0,0 });
		shader->SetFloat("baseLight.cutOff", 0.0f);
		shader->SetFloat("baseLight.outerCutOff", 0.0f);
		shader->SetFloat("baseLight.constant", 0.0f);
		shader->SetFloat("baseLight.linear", 0.0f);
		shader->SetFloat("baseLight.quadratic", 0.0f);

		shader->SetVec3("baseLight.ambient", { 0,0,0 });
		shader->SetVec3("baseLight.diffuse", { 0,0,0 });
		shader->SetVec3("baseLight.specular", { 0,0,0 });*/
		break;
	case 1:
		//std::cout << "Point light" << std::endl;

		//PointLightShaderSetting(shader, aLightData);

		//shader->SetVec3("PLight[0].position", pointLightPositions[0]);
		//shader->SetVec3("PLight[0].ambient", aLightData->ambient);
		//shader->SetVec3("PLight[0].diffuse", aLightData->diffuse);
		//shader->SetVec3("PLight[0].specular", aLightData->specular);
		//shader->SetFloat("PLight[0].constant", aLightData->constant);
		//shader->SetFloat("PLight[0].linear", aLightData->linear);
		//shader->SetFloat("PLight[0].quadratic", aLightData->quadtric);
		//// point light 2
		//shader->SetVec3("PLight[1].position", pointLightPositions[1]);
		//shader->SetVec3("PLight[1].ambient", aLightData->ambient);
		//shader->SetVec3("PLight[1].diffuse", aLightData->diffuse);
		//shader->SetVec3("PLight[1].specular", aLightData->specular);
		//shader->SetFloat("PLight[1].constant", aLightData->constant);
		//shader->SetFloat("PLight[1].linear", aLightData->linear);
		//shader->SetFloat("PLight[1].quadratic", aLightData->quadtric);
		//// point light 3
		//shader->SetVec3("PLight[2].position", pointLightPositions[2]);
		//shader->SetVec3("PLight[2].ambient", aLightData->ambient);
		//shader->SetVec3("PLight[2].diffuse", aLightData->diffuse);
		//shader->SetVec3("PLight[2].specular", aLightData->specular);
		//shader->SetFloat("PLight[2].constant", aLightData->constant);
		//shader->SetFloat("PLight[2].linear", aLightData->linear);
		//shader->SetFloat("PLight[2].quadratic", aLightData->quadtric);
		//// point light 4
		//shader->SetVec3("PLight[3].position", pointLightPositions[3]);
		//shader->SetVec3("PLight[3].ambient", aLightData->ambient);
		//shader->SetVec3("PLight[3].diffuse", aLightData->diffuse);
		//shader->SetVec3("PLight[3].specular", aLightData->specular);
		////
		//shader->SetFloat("PLight[3].constant", aLightData->constant);
		//shader->SetFloat("PLight[3].linear", aLightData->linear);
		//shader->SetFloat("PLight[3].quadratic", aLightData->quadtric);
		//
		
		shader->SetVec3("baseLight.ambient", aLightData->ambient);
		shader->SetVec3("baseLight.diffuse", aLightData->diffuse);
		shader->SetVec3("baseLight.specular", aLightData->specular);

		shader->SetVec3("baseLight.position", aLightData->lightPos);

		shader->SetFloat("baseLight.constant", aLightData->constant);
		shader->SetFloat("baseLight.linear", aLightData->linear);
		shader->SetFloat("baseLight.quadratic", aLightData->quadtric);

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.01, 1.0f));

		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);

		break;
	case 2:
		//DirectionalLightSetting(shader, aLightData);
		//std::cout << "Directional light" << std::endl;

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.01, 1.0f));

		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
	
		shader->SetVec3("baseLight.ambient", aLightData->ambient);
		shader->SetVec3("baseLight.diffuse", aLightData->diffuse);
		shader->SetVec3("baseLight.specular", aLightData->specular);

		shader->SetVec3("baseLight.direction", aLightData->lightDir);

		break;
	case 3:
		//std::cout << "Spot light" << std::endl;
		//SpotLightShaderSetting(shader, aLightData);

		shader->SetVec3("baseLight.position", aLightData->lightPos);
		shader->SetVec3("baseLight.direction", aLightData->lightDir);
		shader->SetFloat("baseLight.cutOff", aLightData->cutOff);
		shader->SetFloat("baseLight.outerCutOff", aLightData->outerCutOff);
		shader->SetFloat("baseLight.constant", aLightData->constant);
		shader->SetFloat("baseLight.linear", aLightData->linear);
		shader->SetFloat("baseLight.quadratic", aLightData->quadtric);

		shader->SetVec3("baseLight.ambient", aLightData->ambient);
		shader->SetVec3("baseLight.diffuse", aLightData->diffuse);
		shader->SetVec3("baseLight.specular", aLightData->specular);
		// gotta take in and set materials from and into glsl and the meshes/objects.

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		

		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
	
		
		break;
	default:
		
		//std::cout << "Default" << std::endl;
		break;
	}

	




	//}
	return 0;
}



void LightingManager::Destroy(Lighting* light, LightData* lightData)
{
	Destroy(light, lightData);
}
