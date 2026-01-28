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

		shader->SetFloat("pointLight[" + number + "].constant", *Lighting::constants[lObjs]); // Something wrong with these sets
		shader->SetFloat("pointLight[" + number + "].linear", *Lighting::linears[lObjs]);
		shader->SetFloat("pointLight[" + number + "].quadratic", *Lighting::quadtrics[lObjs]);

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
	
	
	for (int lObjs = 0; lObjs < Lighting::spotLights.size(); lObjs++)
	{

		//std::string PlightPos = "Plight["+lObjs + "].position";
		//
		//std::cout << lObjs <<< "\n";
		std::string number = std::to_string(lObjs);
		//shader->SetInt("NR_SPOTLIGHTS", lObjs);
		
		shader->SetInt("NumSpotLights", Lighting::spotLights.size());
		shader->SetFloat("spotLight[" + number + "].constant", *Lighting::constants[lObjs]);
		shader->SetFloat("spotLight[" + number + "].linear", *Lighting::linears[lObjs]);
		shader->SetFloat("spotLight[" + number + "].quadratic", *Lighting::quadtrics[lObjs]);
		shader->SetFloat("spotLight[" + number + "].cutOff", glm::cos(glm::radians(*Lighting::cutOffs[lObjs])));
		shader->SetFloat("spotLight[" + number + "].outerCutOff", *Lighting::outerCutOffs[lObjs]);

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


		shader->SetVec3(ambient.c_str(), *Lighting::ambients[lObjs]); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), *Lighting::diffuses[lObjs]);

		shader->SetVec3(specular.c_str(), *Lighting::speculars[lObjs]);

		shader->SetVec3(position.c_str(), *Lighting::spotLightPositions[lObjs]);

		shader->SetVec3(direction.c_str(), *Lighting::spotLightDirections[lObjs]);



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
LightingManager::LightingManager()
{
	

	
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
	//SetDirectional(aLightData, NULL);
	//SetSpot(aLightData, NULL);
	//InitialiseLightData(shader, light);
	
	return aLightData;
}

LightData* LightingManager::SetDirectional(LightData* aLightData, Object* obj)
{
	if (!obj == NULL) {

		aLightData = obj->Entities[obj->SelectedEntity]->myLightData;
	}
	
	if (aLightData->LightVar != 2)
	{ 
		Lighting::dirLights.push_back(aLightData);
		std::cout << "dir light!" << std::endl;

	}
	else
	{
		Lighting::dirLights.pop_back();
	}
	aLightData->lightDir = { -0.2f, -1.0f, -0.3f };
	aLightData->ambient = { 0.3, 0.3, 0.3 };
	aLightData->diffuse = { 0.3, 0.3, 0.3 };
	aLightData->specular = { 0.3, 0.3, 0.3 };
	aLightData->constant = 0.3;
	aLightData->linear = 0.3;
	aLightData->quadtric = 0.3;
	Lighting::DirLightDirections.push_back(&aLightData->lightDir);
	Lighting::speculars.push_back(&aLightData->specular);
	Lighting::diffuses.push_back(&aLightData->diffuse);
	Lighting::ambients.push_back(&aLightData->ambient);
	Lighting::constants.push_back(&aLightData->constant);
	Lighting::quadtrics.push_back(&aLightData->quadtric);
	Lighting::linears.push_back(&aLightData->linear);
	
	
	
	std::cout << "Directional light" << std::endl;
	aLightData->LightVar = aLightData->DirLight;
	return aLightData;
}

LightData* LightingManager::SetPoint(LightData* aLightData, Object* obj)
{
	if (!obj == NULL) {

		aLightData = obj->Entities[obj->SelectedEntity]->myLightData;
	}
	if (aLightData->LightVar != 1)
	{
		Lighting::pointLights.push_back(aLightData);
	}
	else
	{
		Lighting::pointLights.pop_back();
	}
	Lighting::pointLightPositions.push_back(&aLightData->lightPos);
	aLightData->ambient = { 0.3, 0.3, 0.3 };
	aLightData->diffuse = { 0.3, 0.3, 0.3 };
	aLightData->specular = { 0.3, 0.3, 0.3 };
	aLightData->constant = 0.3;
	aLightData->linear = 0.3;
	aLightData->quadtric = 0.3;
	Lighting::speculars.push_back(&aLightData->specular);
	Lighting::diffuses.push_back(&aLightData->diffuse);
	Lighting::ambients.push_back(&aLightData->ambient);
	Lighting::constants.push_back(&aLightData->constant);
	Lighting::quadtrics.push_back(&aLightData->quadtric);
	Lighting::linears.push_back(&aLightData->linear);

	//Lighting::pointLightPositions->length();
	
	
	
	
	obj->Entities[obj->SelectedEntity]->Position = aLightData->lightPos;
	

	
	std::cout << "Pointlight" << std::endl;
	aLightData->LightVar = aLightData->PointLight;
	return aLightData;
}

LightData* LightingManager::SetSpot(LightData* aLightData, Object* obj)
{
	if (!obj == NULL) {

		aLightData = obj->Entities[obj->SelectedEntity]->myLightData;
	}
	if (aLightData->LightVar != 3)
	{
		Lighting::spotLights.push_back(aLightData);
	}
	else
	{
		Lighting::spotLights.pop_back();
	}
	aLightData->lightDir = { -0.2f, -1.0f, -0.3f };
	aLightData->ambient = { 0.3, 0.3, 0.3 };
	aLightData->diffuse = { 0.3, 0.3, 0.3 };
	aLightData->specular = { 0.3, 0.3, 0.3 };
	aLightData->constant = 0.3;
	aLightData->linear = 0.3;
	aLightData->quadtric = 0.3;
	aLightData->cutOff = 0.3;
	aLightData->outerCutOff = 0.3;
	Lighting::spotLightDirections.push_back(&aLightData->lightDir);
	Lighting::spotLightPositions.push_back(&aLightData->lightPos);
	Lighting::speculars.push_back(&aLightData->specular);
	Lighting::diffuses.push_back(&aLightData->diffuse);
	Lighting::ambients.push_back(&aLightData->ambient);
	Lighting::constants.push_back(&aLightData->constant);
	Lighting::quadtrics.push_back(&aLightData->quadtric);
	Lighting::linears.push_back(&aLightData->linear);
	Lighting::cutOffs.push_back(&aLightData->cutOff);
	Lighting::outerCutOffs.push_back(&aLightData->outerCutOff);
	
	
	std::cout << "Spotlight" << std::endl;
	aLightData->LightVar = aLightData->SpotLight;
	return aLightData;
}

Lighting* LightingManager::InitDepthMapping()
{
	
	
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return 0;
}

Lighting* LightingManager::InitShaderMaps(Shader* shader)
{
	//shader->SetInt("shadowMap", 1);

	return nullptr;
}



LightData* LightingManager::RunLightData(Shader* shader, LightData* aLightData, Camera* aCamera)
{
	
	
	


	glm::vec3 normalisedDirectionOfLight = glm::normalize(aLightData->lightDir);
	glm::vec3 lightEyePos = glm::vec3(0.0f, 0.0f, 0.0f) - normalisedDirectionOfLight; // *sceneboundsDiagonalLength;
	//glm::vec3 upVector = (abs(dot(normalisedDirectionOfLight, (0, 1, 0))) > 0.99) ? (0, 0, 1) : (0, 1, 0);
	if (aLightData == NULL)
	{
		return 0;
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}

	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	aLightData->view = glm::lookAt(aLightData->lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	// 
	//if (aLightData->LightVar == 2)
	//{
	//	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane); // X, Y, Z, W ?
	//	aLightData->view = glm::lookAt(aLightData->lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	//}
	//if(aLightData->LightVar == 1)
	//{
	//	
	//	lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
	//	
	//	aLightData->view = glm::lookAt(aLightData->lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	//}
	//if (aLightData->LightVar == 3)
	//{
	//	
	//	lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
	//	
	//	aLightData->view = glm::lookAt(lightEyePos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	//}
	
	
	
	glm::mat4 lightspaceMatrix = lightProjection * aLightData->view;

	
	shader->SetVec3("viewPos", aCamera->myPosition);
	shader->SetMatrix("lightSpaceMatrix", lightspaceMatrix);
	
	//shader->SetInt("shadowMap", 1);
	
	PointLightShaderSetting(shader, aLightData);
	DirectionalLightSetting(shader, aLightData);
	SpotLightShaderSetting(shader, aLightData);

	return 0;
}



void LightingManager::Destroy(Lighting* light, LightData* lightData)
{
	Destroy(light, lightData);
}

Lighting* LightingManager::UseShadowDepth(Shader* shader, LightData* aLightData)
{



	//glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//glClear(GL_DEPTH_BUFFER_BIT);
	////ConfigureShaderAndMatrices();
	////RenderScene();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//// 2. then render scene as normal with shadow mapping (using depth map)
	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////ConfigureShaderAndMatrices();
	//glBindTexture(GL_TEXTURE_2D, depthMap);
	//RenderScene();

	aLightData->view = glm::lookAt(aLightData->lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane); // X, Y, Z, W ?
	//glm::mat4 lightProjection = glm::perspective(glm::radians(0.0f), near_plane / far_plane, 0.1f, 100.0f);
	glm::mat4 lightspaceMatrix = lightProjection * aLightData->view;
	shader->SetMatrix("lightSpaceMatrix", lightspaceMatrix);

	shader->SetInt("depthMap", 0);
	shader->SetFloat("near_plane", near_plane);
	shader->SetFloat("far_plane", far_plane);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);


	//shader->SetMatrix("transform", trans);
	return 0;
}

Lighting* LightingManager::ShadowMapStep1(Shader* shader)
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, woodTexture);
	//renderScene(simpleDepthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// reset viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return 0;
}

Lighting* LightingManager::ShadowMapStep2(Shader* shader)
{
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, woodTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	//renderScene(shader);

	// render Depth map to quad for visual debugging
	// ---------------------------------------------
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	return 0;
}
