#pragma once
#include <Lighting.h>
class LightingManager
{
public: 
	
	LightingManager();
	LightData* DefaultLighting;
	glm::mat4 view;
	glm::mat4 lightProjection;
	glm::mat4 lightspaceMatrix;

	LightData* InitDefaultLighting();
	LightData* Create(std::string name = "newLight", Shader* shader = NULL, LightData* light = NULL);
	LightData* RunLightData(Shader* shader, Camera* aCamera, LightObject* lightObj);
	void Destroy(Lighting* light, LightData* lightData);
	Lighting* UseShadowDepth(Shader* shader, LightData* lightData);

	Lighting* ShadowMapStep1(Shader* shader);
	Lighting* ShadowMapStep2(Shader* shader);
	Lighting* ShadowMapStep3(Shader* shader);
	Lighting* DebugShadow(Shader* shader);

	LightData* SetDirectional(LightData* aLightData);
	LightData* SetPoint(LightData* aLightData);
	LightData* SetSpot(LightData* aLightData);

	Lighting* InitDepthMapping(Texture* shadowTexture = NULL);
	Lighting* InitShaderMaps(Shader* shader);

	
	glm::vec3 zeros = { 0.0f,0.0f,0.0f };
	float near_plane = 1.0f, far_plane = 10.0f;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;
	GLuint depthMapFBO;
	GLuint depthMap;

	unsigned int* texture;

	glm::mat4 viewTEST;

};

enum class BoundingTypes {
	AABB = 0x00,
	SPHERE = 0x01
};

class BoundingRegions {
public:
	BoundingTypes type;

	glm::vec3 center;
	float radius;
	glm::vec3 min, max;

	BoundingRegions(BoundingTypes type);

	BoundingRegions(glm::vec3 Center, float radius);

	BoundingRegions(glm::vec3 min, glm::vec3 max);

	glm::vec3 CalcTheCenter();

	glm::vec3 CalcTheDimensions();

	bool containsPoints(glm::vec3 pts);

	bool containsRegion(BoundingRegions br);

	bool intersectsWith(BoundingRegions br);
};