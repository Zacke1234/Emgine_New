#pragma once
#include "glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Object/Object.h"
#include <vector>



struct LightData {
public:
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		enum LightType {
			Null = 0, Point, Directional, Spot
		};
		float ambientStrength = 0.1f;
		glm::vec3 lightPos = { 0,0,0 };
		glm::vec3 lightDir = { 0,0,-1.0f };
		
		glm::vec3 ambient = { 1,1,1 };
		glm::vec3 diffuse = { 1,1,1 };
		glm::vec3 specular = {1,1,1};

		glm::vec3 lightRight;
		glm::vec3 lightUp;

		float near_plane = 1.0f, far_plane = 7.5f;
		glm::mat4 LightOrthographicProjection;
		glm::mat4 LightNormalPerspective;

		glm::mat4 view;

		
		
		
		

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
	//std::vector<LightData> Lightdata;
	
	//LightData* myLightData
	

	static std::vector<glm::vec3*> pointLightPositions;
	static std::vector<glm::vec3*> spotLightPositions;

	static std::vector<glm::vec3*> speculars;
	static std::vector<glm::vec3*> diffuses;
	static std::vector<glm::vec3*> ambients;
	static std::vector<glm::vec3*> DirLightDirections;
	static std::vector<glm::vec3*> spotLightDirections;

	static std::vector<float*> cutOffs;
	static std::vector<float*> outerCutOffs;

	static std::vector<float*> constants;
	static std::vector<float*> linears;
	static std::vector<float*> quadtrics;

	
	
	static std::vector<LightData*> dirLights;
	static std::vector<LightData*> spotLights;
	static std::vector<LightData*> pointLights;
};

class SpotLight{
	glm::vec3 lightDir = { 0,0,0 };
	glm::vec3 lightPos = { 0,0,0 };
};

class DirectionalLight{
	glm::vec3 lightDir = { 0,0,0 };
};

class PointLight{
	glm::vec3 lightPos = { 0,0,0 };
};