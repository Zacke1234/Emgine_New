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

		glm::vec3 lightPos = { 0,0,0 };
		glm::vec3 lightDir = { 0,0,0 };
		
		glm::vec3 ambient = { 1,1,1 };
		glm::vec3 diffuse = { 1,1,1 };
		glm::vec3 specular = {1,1,1};
		
		float near_plane = 1.0f, far_plane = 7.5f;

		float Range = 100.0f;

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

	static std::vector<glm::vec3*> pointLightPositions;
	static std::vector<glm::vec3*> spotLightPositions;

	static std::vector<glm::vec3*> speculars;
	static std::vector<glm::vec3*> diffuses;
	static std::vector<glm::vec3*> ambients;
	static std::vector<glm::vec3*> DirLightDirections;
	static std::vector<glm::vec3*> spotLightDirections;

	static std::vector<glm::mat4*> DirlightspaceMatrixes;
	static std::vector<glm::mat4*> pointlightspaceMatrixes;
	static std::vector<glm::mat4*> spotlightspaceMatrixes;

	static std::vector<float*> cutOffs;
	static std::vector<float*> outerCutOffs;

	static std::vector<float*> constants;
	static std::vector<float*> linears;
	static std::vector<float*> quadtrics;

	
	
	static std::vector<LightData*> dirLights;
	static std::vector<LightData*> spotLights;
	static std::vector<LightData*> pointLights;
};

