#include "LightingManager.h"
std::vector<LightData*> lightsList;
//LightObject::LightEntities.size();
//Camera* Cameron = new Camera();
// 
// shadow mapping  
float near_plane = 1.0f, far_plane = 7.5f;
glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 lightSpaceMatrix = lightProjection * lightView;
int lightSpaceMatrixLocation;

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
		shader->SetFloat("PLight[" + number + "].constant", 1.0f);
		shader->SetFloat("PLight[" + number + "].linear", 0.09f);
		shader->SetFloat("PLight[" + number + "].quadratic", 0.032f);

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


		shader->SetVec3(ambient.c_str(), glm::vec3(0.05f, 0.05f, 0.05f)); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), glm::vec3(0.8f, 0.8f, 0.8f));

		shader->SetVec3(specular.c_str(), glm::vec3(1.0f, 1.0f, 1.0f));

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
		shader->SetMatrix("SLight[NR_SPOT_LIGHTS]", lObjs);
		shader->SetFloat("SLight[" + number + "].constant", 1.0f);
		shader->SetFloat("SLight[" + number + "].linear", 0.09f);
		shader->SetFloat("SLight[" + number + "].quadratic", 0.032f);
		shader->SetFloat("SLight[" + number + "].cutOff", glm::cos(glm::radians(12.5f)));
		shader->SetFloat("SLight[" + number + "].outerCutOff", 0.04f);

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


		shader->SetVec3(ambient.c_str(), glm::vec3(0.05f, 0.05f, 0.05f)); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), glm::vec3(0.8f, 0.8f, 0.8f));

		shader->SetVec3(specular.c_str(), glm::vec3(1.0f, 1.0f, 1.0f));

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
		
		shader->SetFloat("DLight[" + number + "].constant", 1.0f);
		shader->SetFloat("DLight[" + number + "].linear", 0.09f);
		shader->SetFloat("DLight[" + number + "].quadratic", 0.032f);
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

		shader->SetVec3(ambient.c_str(), glm::vec3(0.05f, 0.05f, 0.05f)); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), glm::vec3(0.8f, 0.8f, 0.8f));

		shader->SetVec3(specular.c_str(), glm::vec3(1.0f, 1.0f, 1.0f));

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
	
	SetPoint(light, NULL);
	InitialiseLightData(shader, light);
	
	return light;
}

LightData* LightingManager::SetDirectional(LightData* aLightData, Object* test)
{
	if (!test == NULL) {

		aLightData = test->Entities[test->SelectedEntity]->myLightData;
	}
	
	std::cout << "Directional light" << std::endl;
	aLightData->LightVar = aLightData->DirLight;
	return aLightData;
}

LightData* LightingManager::SetPoint(LightData* aLightData, Object* test)
{
	if (!test == NULL) {
		
		aLightData = test->Entities[test->SelectedEntity]->myLightData;
	}
	
	
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
	if (aLightData == NULL)
	{
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}
	switch (aLightData->LightVar)
	{
	case 0:

		//std::cout << "Null light" << std::endl;
		break;
	case 1:
		//std::cout << "Point light" << std::endl;

		//PointLightShaderSetting(shader, aLightData);

		shader->SetVec3("PLight[0].position", pointLightPositions[0]);
		shader->SetVec3("PLight[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		shader->SetVec3("PLight[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		shader->SetVec3("PLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetFloat("PLight[0].constant", 1.0f);
		shader->SetFloat("PLight[0].linear", 0.09f);
		shader->SetFloat("PLight[0].quadratic", 0.032f);
		// point light 2
		shader->SetVec3("PLight[1].position", pointLightPositions[1]);
		shader->SetVec3("PLight[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		shader->SetVec3("PLight[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		shader->SetVec3("PLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetFloat("PLight[1].constant", 1.0f);
		shader->SetFloat("PLight[1].linear", 0.09f);
		shader->SetFloat("PLight[1].quadratic", 0.032f);
		// point light 3
		shader->SetVec3("PLight[2].position", pointLightPositions[2]);
		shader->SetVec3("PLight[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		shader->SetVec3("PLight[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		shader->SetVec3("PLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetFloat("PLight[2].constant", 1.0f);
		shader->SetFloat("PLight[2].linear", 0.09f);
		shader->SetFloat("PLight[2].quadratic", 0.032f);
		// point light 4
		shader->SetVec3("PLight[3].position", pointLightPositions[3]);
		shader->SetVec3("PLight[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		shader->SetVec3("PLight[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		shader->SetVec3("PLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetFloat("PLight[3].constant", 1.0f);
		shader->SetFloat("PLight[3].linear", 0.09f);
		shader->SetFloat("PLight[3].quadratic", 0.032f);


		shader->SetVec3("lightColor", glm::vec3(0.0f, 0.01, 0.0f));

		shader->SetVec3("material.objectColor", glm::vec3(1.0f, 1.0,1.0));


		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);

		shader->SetVec3("material.ambient", glm::vec3(1.0f, 1.0, 1.0));
		shader->SetInt("material.diffuse", 0);
		shader->SetInt("material.specular", 1.01);
		shader->SetFloat("material.shininess", 1.01f);

		break;
	case 2:
		DirectionalLightSetting(shader, aLightData);
		//std::cout << "Directional light" << std::endl;

		shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		//shader->SetVec3("DLight.position", aLightData->lightPos);
		shader->SetVec3("material.objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

		//shader->SetVec3("viewPos", aCamera->myPosition);
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		shader->SetVec3("material.ambient", glm::vec3(0.5f, 0.5, 0.5));
		shader->SetInt("material.diffuse", 2);
		shader->SetInt("material.specular", 3);
		shader->SetFloat("material.shininess", 0.0f);
		break;
	case 3:
		//std::cout << "Spot light" << std::endl;
		SpotLightShaderSetting(shader, aLightData);
		shader->SetVec3("material.lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("material.objectColor", glm::vec3(0.5f, 0.6f, 0.2f));

		shader->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));

		//shader->SetVec3("viewPos", aCamera->myPosition);
		shader->SetMatrix("lightSpaceMatrix", lightSpaceMatrix);
		shader->SetVec3("material.ambient", glm::vec3(0.2f, 0.2, 0.2));
		shader->SetInt("material.diffuse", 1);
		shader->SetInt("material.specular", 1);
		shader->SetFloat("material.shininess", 32.0f);
		break;
	default:
		std::cout << "Default" << std::endl;
		break;
	}

	//for (int l = 0; l < LightObject::LightEntities.size(); l++)
	//{	
	//	//LightObject::SelectedEntity = l;
	//	//std::string number = sizeof(lObjs);

	//	// I want to find each light entity and be able to tell if each one is a certain type of light, directional, spot, pointlight.
	//	//LightObject::LightEntities[l]->myLightData-
	//	




	//}
	return 0;
}



void LightingManager::Destroy(Lighting* light, LightData* lightData)
{
	Destroy(light, lightData);
}
