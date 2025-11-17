#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#pragma once



Lighting::Lighting()
{
	
}

void Lighting::Use(Camera* aCamera, Shader* shader)
{
	//shader->SetVec3("NoLight.direction", aCamera->projection);
	shader->SetVec3("viewPos", aCamera->myPosition);
	shader->SetVec3("specularStrength", glm::vec3(1.5f, 1.5, 1.5));
	//shader->SetInt("shadowMap", 0);
	//shader->SetInt("depthMap", 1);
	glm::mat4 view = aCamera->GetViewMatrix();
	shader->SetMatrix("view", view);
	//shader->SetVec4("FragPosLightSpace", aCamera->lightsp);
	//glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	
}

