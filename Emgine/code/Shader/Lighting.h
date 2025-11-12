#pragma once
#include "glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Object/Object.h"
#include <vector>



struct LightData {

	
		enum LightType {
			Null, Point, Directional, Spot
		};
		float ambientStrength = 0.1f;
		glm::vec3 lightPos = { 0,0,0 };
		glm::vec3 lightDir = { 0,0,0 };
		glm::vec2 TexCoord = { 0,0 };
		glm::vec3 ambient = { 0,0,0 };
		glm::vec3 diffuse = { 0,0,0 };
		glm::vec3 specular = {0,0,0};
		float linear = 0; 
		float quadtric = 0; 

		float cutOff;
		float outerCutOff;

		float constant;

		enum LightType PointLight = Point;
		enum LightType DirLight = Directional;
		enum LightType SpotLight = Spot;
		enum LightType LightVar;
		
		std::string Name;

};


class Lighting
{
public:
	
	 
	
	Lighting();
	//std::vector<LightData> Lightdata;
	void Use(Camera* aCamera, Shader* aShader);
	//LightData* myLightData
	

	
};

