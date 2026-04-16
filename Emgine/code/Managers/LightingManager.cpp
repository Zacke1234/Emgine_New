#include "LightingManager.h"


#pragma once
std::vector<LightData*> lightsList;

int DeleteLightVariables(std::string lightType)
{
	// crashes the second time something is deleted

	if (lightType == "Directional")
	{
		Lighting::DirLightDirections.erase(Lighting::DirLightDirections.begin() + LightObject::SelectedLightEntity);
	}
	else if (lightType == "Point")
	{
		Lighting::pointLightPositions.erase(Lighting::pointLightPositions.begin() + LightObject::SelectedLightEntity);

	}
	else if (lightType == "Spot")
	{
		
		Lighting::spotLightDirections.erase(Lighting::spotLightDirections.begin() + LightObject::SelectedLightEntity);
		Lighting::spotLightPositions.erase(Lighting::spotLightPositions.begin() + LightObject::SelectedLightEntity);

		Lighting::cutOffs.erase(Lighting::cutOffs.begin() + LightObject::SelectedLightEntity);
		Lighting::outerCutOffs.erase(Lighting::outerCutOffs.begin() + LightObject::SelectedLightEntity);

	}

	
	
	Lighting::constants.erase(Lighting::constants.begin() + LightObject::SelectedLightEntity);
	Lighting::linears.erase(Lighting::linears.begin() + LightObject::SelectedLightEntity);
	Lighting::quadtrics.erase(Lighting::quadtrics.begin() + LightObject::SelectedLightEntity);

	
	return 0;
}

int LightShaderSetting(Shader* shader, std::string lightType)
{
	std::vector<LightData*> fragmentLightTypeSize;
	std::vector<glm::vec3*> fragmentLightTypePositions;
	std::vector<glm::vec3*> fragmentLightTypeDirections;
	std::string fragmentLightTypeName;
	std::string fragmentLightAmount;
	if (lightType == "Directional")
	{
		fragmentLightAmount = "NumDirectionalLights";
		fragmentLightTypeSize = Lighting::dirLights;
		fragmentLightTypeDirections = Lighting::DirLightDirections;
		fragmentLightTypeName = "dirLight";
	}
	else if (lightType == "Point")
	{
		fragmentLightAmount = "NumPointLights";
		fragmentLightTypeSize = Lighting::pointLights;
		fragmentLightTypePositions = Lighting::pointLightPositions;
		fragmentLightTypeName = "pointLight";
	}
	else if (lightType == "Spot")
	{
		fragmentLightAmount = "NumSpotLights";
		fragmentLightTypeSize = Lighting::spotLights;
		fragmentLightTypePositions = Lighting::spotLightPositions;
		fragmentLightTypeDirections = Lighting::spotLightDirections;
		fragmentLightTypeName = "spotLight";
	}
	
	shader->SetInt(fragmentLightAmount, fragmentLightTypeSize.size());

	for (int lObjs = 0; lObjs < fragmentLightTypeSize.size(); lObjs++)
	{
		std::string number = std::to_string(lObjs);
		//shader->SetInt(fragmentLightAmount, fragmentLightTypeSize.size());

		shader->SetFloat(fragmentLightTypeName + "[" + number + "].constant", *Lighting::constants[lObjs]);
		shader->SetFloat(fragmentLightTypeName + "[" + number + "].linear", *Lighting::linears[lObjs]);
		shader->SetFloat(fragmentLightTypeName + "[" + number + "].quadratic", *Lighting::quadtrics[lObjs]);
		if (lightType == "Spot")
		{
			shader->SetFloat(fragmentLightTypeName + "[" + number + "].cutOff", glm::cos(glm::radians(*Lighting::cutOffs[lObjs])));
			shader->SetFloat(fragmentLightTypeName + "[" + number + "].outerCutOff", *Lighting::outerCutOffs[lObjs]);
		}
		
		std::string temp1 = fragmentLightTypeName + "[";  temp1.append(number);
		
		std::string tempAmb = "].ambient";
		std::string tempDiff = "].diffuse";
		std::string tempSpec = "].specular";
		std::string tempDir = "].direction";
		std::string tempPos = "].position";
		std::string ambient = temp1.append(tempAmb);
		temp1 = fragmentLightTypeName + "["; temp1.append(number);
		std::string diffuse = temp1.append(tempDiff);
		temp1 = fragmentLightTypeName + "["; temp1.append(number);
		std::string specular = temp1.append(tempSpec);
		temp1 = fragmentLightTypeName + "["; temp1.append(number);
		std::string position = temp1.append(tempPos);
		temp1 = fragmentLightTypeName + "["; temp1.append(number);
		std::string direction = temp1.append(tempDir);

		if (lightType == "Directional")
		{
			shader->SetVec3(direction.c_str(), *fragmentLightTypeDirections[lObjs]); // need to erase these variables as well
		}
		else if (lightType == "Spot")
		{
			shader->SetVec3(position.c_str(), *fragmentLightTypePositions[lObjs]);
			shader->SetVec3(direction.c_str(), *fragmentLightTypeDirections[lObjs]);
		}
		else if (lightType == "Point")
		{
			shader->SetVec3(position.c_str(), *fragmentLightTypePositions[lObjs]);
		}
		
		shader->SetVec3(ambient.c_str(), *Lighting::ambients[lObjs]); // it appends the number at the start as well as in the middle field. SOLVED!

		shader->SetVec3(diffuse.c_str(), *Lighting::diffuses[lObjs]);

		shader->SetVec3(specular.c_str(), *Lighting::speculars[lObjs]);

	}
	
	return 0;
}

int ClearLightSetting(LightData* aLightData)
{
	aLightData->lightDir = { 0,0,0 };
	aLightData->ambient = { 0.0,0.0,0.0 };
	aLightData->diffuse = { 0.0,0.0,0.0 };
	aLightData->specular = { 0.0,0.0,0.0 };
	aLightData->constant = 0;
	aLightData->linear = 0;
	aLightData->quadtric = 0;
	aLightData->Range = 0;
	aLightData->near_plane = -aLightData->Range;
	aLightData->far_plane = aLightData->Range;
	aLightData->cutOff = 0;
	aLightData->outerCutOff = 0;
	Lighting::DirLightDirections.push_back(&aLightData->lightDir);
	Lighting::speculars.push_back(&aLightData->specular);
	Lighting::diffuses.push_back(&aLightData->diffuse);
	Lighting::ambients.push_back(&aLightData->ambient);
	Lighting::constants.push_back(&aLightData->constant);
	Lighting::quadtrics.push_back(&aLightData->quadtric);
	Lighting::linears.push_back(&aLightData->linear);
	return 0;
}


LightingManager::LightingManager()
{
	

	
}
LightData* LightingManager::InitDefaultLighting()
{
	DefaultLighting = new LightData();
	
	SetPoint(DefaultLighting);
	//SetDirectional(DefaultLighting);
	//SetSpot(DefaultLighting);

	LightHasInitalised = true;
	return DefaultLighting;
}
LightData* LightingManager::Create(std::string name, Shader* aShader, LightData* aLightData)
{
	
	if (LightHasInitalised)
	{
		aLightData = DefaultLighting;
		DefaultLighting->Name = name;

	}
	else
	{
		aLightData = new LightData();
		aLightData->Name = name;
	}
	
	
	
	
	return aLightData;
}

LightData* LightingManager::Destroy(Shader* aShader, Object* obj)
{
	switch (obj->myLightData->LightVar)
	{
	case 1: // point
		Lighting::pointLights.erase(Lighting::pointLights.begin() + LightObject::SelectedLightEntity); 
		DeleteLightVariables("Point");
		aShader->SetInt("NumPointLights", Lighting::pointLights.size());
		break;
	case 2: // dir
		Lighting::dirLights.erase(Lighting::dirLights.begin() + LightObject::SelectedLightEntity);
		DeleteLightVariables("Directional");
		aShader->SetInt("NumDirectionalLights", Lighting::dirLights.size());
		break;
	case 3: // spot
		//if (!Lighting::pointLights.empty())
		Lighting::spotLights.erase(Lighting::spotLights.begin() + LightObject::SelectedLightEntity); 
		DeleteLightVariables("Spot");
		aShader->SetInt("NumSpotLights", Lighting::spotLights.size());
		break;
	}
	
	//ClearLightSetting(obj->myLightData);
	LightObject::LightEntities.erase(LightObject::LightEntities.begin() + LightObject::SelectedLightEntity);

	return nullptr;
}

LightData* LightingManager::SetDirectional(LightData* aLightData)
{
	if (aLightData == NULL)
	{
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
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
	aLightData->lightDir = { 0,0,0 };
	aLightData->ambient = { 0.3,0.3,0.3 };
	aLightData->diffuse = { 0.3,0.3,0.3 };
	aLightData->specular = { 0.3,0.3,0.3 };
	aLightData->constant = 1;
	aLightData->linear = 1;
	aLightData->quadtric = 0.5;
	aLightData->near_plane = -aLightData->Range;
	aLightData->far_plane = aLightData->Range;
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

LightData* LightingManager::SetPoint(LightData* aLightData)
{
	if (aLightData == NULL)
	{
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
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
	aLightData->ambient = { 0.3,0.3,0.3 };
	aLightData->diffuse = { 0.3,0.3,0.3 };
	aLightData->specular = { 0.3,0.3,0.3 };
	aLightData->constant = 1;
	aLightData->linear = 0;
	aLightData->quadtric = 0.5;
	aLightData->near_plane = 0.1f;
	aLightData->far_plane = aLightData->Range;

	Lighting::speculars.push_back(&aLightData->specular);
	Lighting::diffuses.push_back(&aLightData->diffuse);
	Lighting::ambients.push_back(&aLightData->ambient);
	Lighting::constants.push_back(&aLightData->constant);
	Lighting::quadtrics.push_back(&aLightData->quadtric);
	Lighting::linears.push_back(&aLightData->linear);

	//Lighting::pointLightPositions->length();
	
	
	//obj->Entities[obj->SelectedEntity]->Position = aLightData->lightPos;
	// gotta change this
	//obj->Position = aLightData->lightPos;
	

	
	std::cout << "Pointlight" << std::endl;
	aLightData->LightVar = aLightData->PointLight;
	return aLightData;
}

LightData* LightingManager::SetSpot(LightData* aLightData)
{
	if (aLightData == NULL)
	{
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}
	if (aLightData->LightVar != 3)
	{
		Lighting::spotLights.push_back(aLightData);
	}
	else
	{
		Lighting::spotLights.pop_back();
	}
	aLightData->lightDir = { 0,0,0 };
	aLightData->ambient = { 0.0f, 0.0f, 0.0f };
	aLightData->diffuse = { 0.3,0.3,0.3 };
	aLightData->specular = { 0.3,0.3,0.3 };
	aLightData->constant = 1;
	aLightData->linear = 0.09f;
	aLightData->quadtric = 0.032f;
	aLightData->cutOff = glm::cos(glm::radians(1.5f));
	aLightData->outerCutOff = glm::cos(glm::radians(45.f));
	aLightData->near_plane = 0.1f;
	aLightData->far_plane = aLightData->Range;

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

Lighting* LightingManager::LoadCubeMaps(Texture* shadowTexture)
{
	std::vector<std::string> faces;
	int width, height, nrComponents;
	GL_CHECK(glGenTextures(1, &depthCubemap));
	GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap));
	for (unsigned int i = 0; i < 6; ++i)
	{
		/*unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{

		}*/
		GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, shadowTexture->data));
	}

	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

	//GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthCubemap, 0));

	return 0;
}

Lighting* LightingManager::InitDepthMapping()
{
	GL_CHECK(glGenFramebuffers(1, &depthMapFBO));

	GL_CHECK(glGenTextures(1, &depthMap));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMap));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
	GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0));
	GL_CHECK(glDrawBuffer(GL_NONE));
	GL_CHECK(glReadBuffer(GL_NONE));
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	
	return 0;
}

Lighting* LightingManager::InitShaderMaps(Shader* shader)
{
	//shader->SetInt("shadowMap", 1);

	return nullptr;
}

Lighting* LightingManager::BindFrameBuffer()
{
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
	return nullptr;
}


Lighting* LightingManager::ActiveTextureDepth()
{
	GL_CHECK(glActiveTexture(GL_TEXTURE1));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMap));
	return nullptr;
}

Lighting* LightingManager::BindTexture()
{
	
	for (auto& t : Texture::textures)
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, t->TextureObject));
	}
	
	
	return nullptr;
}

Lighting* LightingManager::BindDepthTexture()
{
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMap));
	return nullptr;
}

Lighting* LightingManager::Viewport()
{
	GL_CHECK(glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT));
	return nullptr;
}

LightData* LightingManager::RunLightData(Shader* shader, Camera* aCamera)
{
	
	for (auto& lightObj : LightObject::LightEntities)
	{
		if (lightObj->myLightData == NULL)
		{
			return 0;
			lightObj->myLightData = Object::Entities[Object::SelectedEntity]->myLightData;
		}

		lightObj->myLightData->lightPos = lightObj->Position;
		lightObj->myLightData->lightDir = lightObj->Rotation;

		switch (lightObj->myLightData->LightVar)
		{
		case 1: // point
			LightShaderSetting(shader, "Point");
			break;
		case 2: // dir
			LightShaderSetting(shader, "Directional");
			break;
		case 3: // spot
			LightShaderSetting(shader, "Spot");
			break;
		}

	}
	if (Lighting::dirLights.size() == 0)
	{ 
		LightShaderSetting(shader, "Directional");
		//std::cout << "No light entities exist" << std::endl;
	}
	if (Lighting::pointLights.size() == 0)
	{
		LightShaderSetting(shader, "Point");
		//std::cout << "No light entities exist" << std::endl;
	}
	if (Lighting::spotLights.size() == 0)
	{
		LightShaderSetting(shader, "Spot");
		//std::cout << "No light entities exist" << std::endl;
	}
	
	return 0;
}

Lighting* LightingManager::UseShadowDepth(Shader* shader, LightData* aLightData)
{
	
	if (aLightData->LightVar == 2) // directional
	{

		lightOrtho = glm::ortho(-aLightData->Range, aLightData->Range, -aLightData->Range, aLightData->Range, aLightData->near_plane, aLightData->far_plane);

		lightLookAt = glm::translate(glm::lookAt(aLightData->lightDir, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)), aLightData->lightPos); 
		
		lightspaceMatrix = lightOrtho * lightLookAt;
		
	}
	else if (aLightData->LightVar == 1) // point
	{

		lightPerspective = glm::perspective(glm::radians(70.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, aLightData->near_plane, aLightData->far_plane);

		lightLookAt = glm::lookAt(aLightData->lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

		lightspaceMatrix = lightPerspective * lightLookAt;
	}															
	else if (aLightData->LightVar == 3) // spot
	{

		lightPerspective = glm::perspective(glm::radians(70.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, aLightData->near_plane, aLightData->far_plane);

		lightLookAt = glm::lookAt(aLightData->lightPos, aLightData->lightDir, glm::vec3(0.0, 1.0, 0.0));

		lightspaceMatrix = lightPerspective * lightLookAt;
	}

	

	
	shader->SetFloat("far_plane", aLightData->far_plane);
	shader->SetFloat("near_plane", aLightData->near_plane);

	shader->SetMatrix("lightSpaceMatrix", lightspaceMatrix);

	


	return 0;
}

Lighting* LightingManager::RunMainFragmentShadows(Shader* shader, LightData* lightData)
{

	shader->SetMatrix("lightSpaceMatrix", lightspaceMatrix);

	return nullptr;
}
