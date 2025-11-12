#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>




Lighting::Lighting()
{
	
}

void Lighting::Use(Camera* aCamera, Shader* shader)
{
	
	shader->SetVec3("viewPos", aCamera->myPosition);
	shader->SetVec3("specularStrength", glm::vec3(1.5f, 1.5, 1.5));
	shader->SetInt("shadowMap", 1);
	shader->SetInt("depthMap", 1);
	glm::mat4 view = aCamera->GetViewMatrix();
	shader->SetMatrix("view", view);
	//glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	
}

