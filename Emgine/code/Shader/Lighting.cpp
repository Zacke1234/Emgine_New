#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#pragma once

std::vector<LightData*> Lighting::dirLights;
std::vector<LightData*> Lighting::spotLights;
std::vector<LightData*> Lighting::pointLights;
std::vector<glm::vec3*> Lighting::pointLightPositions;
std::vector<glm::vec3*> Lighting::speculars;
std::vector<glm::vec3*> Lighting::diffuses;
std::vector<glm::vec3*> Lighting::ambients;
std::vector<float*> Lighting::constants;
std::vector<float*> Lighting::linears;
std::vector<float*> Lighting::quadtrics;

Lighting::Lighting()
{
	
}

void Lighting::Use(Camera* aCamera, Shader* shader)
{
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;
	//shader->SetVec3("NoLight.direction", aCamera->projection);
	//shader->SetVec3("viewPos", aCamera->myPosition);
	shader->SetVec3("specularStrength", glm::vec3(1.5f, 1.5, 1.5));
	//shader->SetInt("shadowMap", 0);
	//shader->SetInt("depthMap", 1);
	//shader->SetMatrix("viewPos", aCamera->myView);
	//shader->SetMatrix("lightSpaceMatrix", aCamera->GetViewMatrix());
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*GL_CHECK(glGenTextures(1, &depthmap));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthmap));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));*/

	//GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
	//GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthmap, 0));
	//GL_CHECK(glDrawBuffer(GL_NONE));
	//GL_CHECK(glReadBuffer(GL_NONE));
	//GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	//GL_CHECK(glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT));
	//GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
	//GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
	//GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	//GL_CHECK(glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT));
	//GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthmap));

	
	

}

