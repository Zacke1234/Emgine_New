#pragma once
#include "glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Object/Object.h"
#include <vector>



struct LightData {
public:
	
		enum LightType {
			Null = 0, Point, Directional, Spot
		};
		float ambientStrength = 0.1f;
		glm::vec3 lightPos = { 0,0,0 };
		glm::vec3 lightDir = { 0,0,0 };
		glm::vec2 TexCoord = { 0,0 };
		glm::vec3 ambient = { 1,1,1 };
		glm::vec3 diffuse = { 1,1,1 };
		glm::vec3 specular = {1,1,1};
		float near_plane = 1.0f, far_plane = 7.5f;
		glm::mat4 OrthographicProjection = glm::ortho(lightPos.x, lightPos.y, lightPos.z, 0.0f, near_plane, far_plane);
		glm::mat4 NormalPerspective = glm::perspective(glm::radians(1.0f), 1.0f, 0.1f, 0.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(lightDir.x, lightDir.y, lightDir.z),
			glm::vec3(lightDir.x, lightDir.y, lightDir.z),
			glm::vec3(lightDir.x, lightDir.y, lightDir.z));

		
		
		static std::vector<LightData*> dirLights;
		static std::vector<LightData*> spotLights;
		static std::vector<LightData*> pointLights;

		float linear = 1; 
		float quadtric = 1; 
		
		float cutOff = 1;
		float outerCutOff = 1;

		float constant = 1;

		enum LightType PointLight = Point;
		enum LightType DirLight = Directional;
		enum LightType SpotLight = Spot;
		enum LightType LightVar;
		
		std::string Name;

};


class Lighting
{
public:
	
	unsigned int depthmap = 0;
	unsigned int depthMapFBO = 0;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	Lighting();
	//std::vector<LightData> Lightdata;
	void Use(Camera* aCamera, Shader* aShader);
	//LightData* myLightData
	

	
};

