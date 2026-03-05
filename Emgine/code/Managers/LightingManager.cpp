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

		shader->SetFloat("pointLight[" + number + "].constant", *Lighting::constants[lObjs]); 
		shader->SetFloat("pointLight[" + number + "].linear", *Lighting::linears[lObjs]);
		shader->SetFloat("pointLight[" + number + "].quadratic", *Lighting::quadtrics[lObjs]);
		shader->SetFloat("pointLight[" + number + "].far_plane", 7.0f); // far plane

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


	SetPoint(aLightData);
	//SetDirectional(aLightData, NULL);
	//SetSpot(aLightData, NULL);
	//InitialiseLightData(shader, light);
	
	return aLightData;
}

LightData* LightingManager::SetDirectional(LightData* aLightData)
{
	
	
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
	aLightData->quadtric = 1;
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
	/*if (!obj == NULL) {

		aLightData = obj->Entities[obj->SelectedEntity]->myLightData;
	}*/
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
	aLightData->quadtric = 0;

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
	
	if (aLightData->LightVar != 3)
	{
		Lighting::spotLights.push_back(aLightData);
	}
	else
	{
		Lighting::spotLights.pop_back();
	}
	aLightData->lightDir = { 0,0,0 };
	aLightData->ambient = { 0.3,0.3,0.3 };
	aLightData->diffuse = { 0.3,0.3,0.3 };
	aLightData->specular = { 0.3,0.3,0.3 };
	aLightData->constant = 1;
	aLightData->linear = 1;
	aLightData->quadtric = 1;
	aLightData->cutOff = 1;
	aLightData->outerCutOff = 1;
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

Lighting* LightingManager::InitDepthMapping(Texture* shadowTexture)
{
	
	//data = stbi_load(shadowTexture->texturePath.c_str(), &shadowTexture->Width, &shadowTexture->Height, &shadowTexture->Channels, 0);

	GL_CHECK(glGenFramebuffers(1, &depthMapFBO) );
	// create depth texture
	
	GL_CHECK(glGenTextures(1, &depthMap));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMap));

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
	// attach depth texture as FBO's depth buffer
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
	GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0));
	GL_CHECK(glDrawBuffer(GL_NONE));
	GL_CHECK(glReadBuffer(GL_NONE));
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << ("ShadowBuffer [Framebuffer] could not be initialized.");
	//std::cout << "init depth mapping" << std::endl;

	return 0;
}

Lighting* LightingManager::InitShaderMaps(Shader* shader)
{
	//shader->SetInt("shadowMap", 1);

	return nullptr;
}



LightData* LightingManager::RunLightData(Shader* shader, Camera* aCamera, LightObject* lightObj)
{

	if (lightObj->myLightData == NULL)
	{
		return 0;
		lightObj->myLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}

	lightObj->myLightData->lightPos = lightObj->Position;
	
	
	//shader->SetInt("shadowMap", 1);
	
	PointLightShaderSetting(shader, lightObj->myLightData);
	DirectionalLightSetting(shader, lightObj->myLightData);
	SpotLightShaderSetting(shader, lightObj->myLightData);

	return 0;
}



void LightingManager::Destroy(Lighting* light, LightData* lightData)
{
	//Destroy(light, lightData);
}


Lighting* LightingManager::UseShadowDepth(Shader* shader, LightData* aLightData)
{
	if (shader == NULL)
	{
		return 0;
	}
	//glm::vec3 aPos = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 fragPos = glm::vec3(objects->trans * glm::vec4(aPos, 1.0f));

	//glm::vec3 pointLightPos = glm::normalize(aLightData->lightPos + fragPos); // (whole scene within range of course)
	//glm::vec3 pointLightDir = glm::normalize(aLightData->lightDir + fragPos);
	if (aLightData == NULL)
	{
		return 0;
		aLightData = Object::Entities[Object::SelectedEntity]->myLightData;
	}
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	
	
	// return glm::lookAt(myPosition, myPosition + myDirection, myUp);

	
	if (aLightData->LightVar == 2) // directional
	{
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		view = glm::lookAt(aLightData->lightDir, glm::vec3(0), glm::vec3(0, 1, 0));
		
	}
	if (aLightData->LightVar == 1) // point
	{

		lightProjection = glm::perspective(glm::radians(70.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);

		view = glm::lookAt(aLightData->lightPos, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0)); // this light position is not enough to reflect the whole scene sadly
	}															// NOTE: this one in the middle is super important for this!!!!!!!
	if (aLightData->LightVar == 3) // spot
	{

		lightProjection = glm::perspective(glm::acos(aLightData->outerCutOff) * 2.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);

		view = glm::lookAt(aLightData->lightPos, aLightData->lightPos + aLightData->lightDir, glm::vec3(0.0, 1.0, 0.0));
	}
	lightspaceMatrix = lightProjection * view;

	
	/*myUp = glm::cross(myDirection, myRight);



	projection = glm::perspective(glm::radians(fieldOfView), myWidth / myHeight, 0.1f, cameraViewRange);

	myRight = glm::normalize(glm::cross(WorldUp, myDirection));
	myUp = glm::cross(myDirection, myRight);
	myView = glm::lookAt(myPosition, myPosition + myDirection, myUp);*/

	
	/*glm::vec4 FragPosLightSpace = glm::vec4(1, 2, 440, 1);



	shader->SetVec4("FragPosLightSpace", FragPosLightSpace);*/
	shader->SetMatrix("lightSpaceMatrix", lightspaceMatrix);
	shader->SetMatrix("dirLight.lightSpaceMatrix", lightspaceMatrix);
	//FragPosLightSpace
	
	
	
	
	return 0;
}

Lighting* LightingManager::ShadowMapStep1(Shader* shader)
{
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	for (auto& t : Texture::textures)
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, t->TextureObject));
	}
	GL_CHECK(glActiveTexture(GL_TEXTURE1));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMap));
	//viewTEST = glm::lookAt(aLightData->lightPos, aLightData->lightPos, glm::vec3(0.0f, 1.0f, 0.0f));
	/*glm::mat4 lightspaceMatrix = lightProjection * aLightData->view;
	if (aLightData->lightPos.length > objects->Position.length)
	{
		shader->SetInt("shadowMap", 0);
	}
	else
	{
		shader->SetInt("shadowMap", 1);
	}
	shader->SetMatrix("lightSpaceMatrix", lightspaceMatrix);
*/
	
	

	return 0;
}

Lighting* LightingManager::ShadowMapStep2(Shader* shader)
{
	
	/*GL_CHECK(glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT));
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
	GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	for (auto& t : Texture::textures)
	{
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, t->TextureObject));
	}*/
	
	//glCullFace(GL_FRONT);
	for (auto& o : Object::Entities)
	{
		o->Draw(shader);
	}
	//glCullFace(GL_BACK);
	////renderScene(simpleDepthShader);
	//GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	// // reset viewport
	//GL_CHECK(glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT));
	//GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	return 0;
}

Lighting* LightingManager::ShadowMapStep3(Shader* shader)
{
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMap));
	return 0;
}

Lighting* LightingManager::DebugShadow(Shader* shader)
{
	shader->SetFloat("near_plane", near_plane);
	shader->SetFloat("far_plane", far_plane);
	return 0;
}

BoundingRegions::BoundingRegions(BoundingTypes type) : type(type)
{
	

}

BoundingRegions::BoundingRegions(glm::vec3 Center, float radius) : type(BoundingTypes::SPHERE), center(center), radius(radius)
{
}

BoundingRegions::BoundingRegions(glm::vec3 min, glm::vec3 max) : type(BoundingTypes::AABB), min(min), max(max) {

}


glm::vec3 BoundingRegions::CalcTheCenter()
{
	return (type == BoundingTypes::AABB) ? (min + max) / 2.0f : center;
}

glm::vec3 BoundingRegions::CalcTheDimensions()
{
	return (type == BoundingTypes::AABB) ? (min - max) : glm::vec3(2.0f * radius);
}

bool BoundingRegions::containsPoints(glm::vec3 pts)
{
	if (type == BoundingTypes::AABB)
	{
		return (pts.x >= min.x) && (pts.x <= max.x) &&
			(pts.y >= min.y) && (pts.y <= max.y) &&
			(pts.z >= min.z) && (pts.z <= max.z);
	}
	else
	{
		float dist = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			dist += (center[i] - pts[i]) * (center[i] - pts[i]);
		}
		return dist <= (radius * radius);
	}
}

bool BoundingRegions::containsRegion(BoundingRegions br)
{
	if (br.type == BoundingTypes::AABB)
	{
		return containsPoints(br.min) && containsPoints(br.max);
	}
	else if (type == BoundingTypes::SPHERE && br.type == BoundingTypes::SPHERE){
		return glm::length(center - br.center) + br.radius < radius;
	}
	else
	{
		if (!containsPoints(br.center))
		{
			return false;
		}
		for (int i = 0; i < 3; i++)
		{
			if (abs(max[i] - br.center[i] < br.radius ||
				abs(br.center[i] - min[i] < br.radius)))
			{
				return false;
			}
			
		}
		return true;
	}
}

bool BoundingRegions::intersectsWith(BoundingRegions br)
{
	if (type == BoundingTypes::AABB && br.type == BoundingTypes::AABB)
	{
		glm::vec3 rad = CalcTheDimensions() / 2.0f;
		glm::vec3 radBr = br.CalcTheDimensions() / 2.0f;

		glm::vec3 center = CalcTheCenter();
		glm::vec3 centerBr = br.CalcTheCenter();

		glm::vec3 dist = abs(center - centerBr);

		for (int i = 0; i < 3; i++)
		{
			if (dist[i] > rad[i] + radBr[i])
			{
				return false;
			}
		}
		return true;
	}
	else if (type == BoundingTypes::SPHERE) {
		// this is a sphere, br is a box
		float distSquared = 0.0f;
		for (int i = 0; i < 3; i++) {
			// determine closest side
			float closestPt = std::max(br.min[i], std::min(center[i], br.max[i]));
			// add distance
			distSquared += (closestPt - center[i]) * (closestPt - center[i]);
		}

		return distSquared < (radius * radius);
	}

	else
	{
		return br.intersectsWith(*this);
	}
}
