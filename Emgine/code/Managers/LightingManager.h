#pragma once
#include <Lighting.h>
class LightingManager
{
public: 
	
	LightingManager();
	LightData* DefaultLighting;
	glm::mat4 lightLookAt;
	glm::mat4 lightOrtho;
	glm::mat4 lightPerspective;
	glm::mat4 lightspaceMatrix;

	LightData* InitDefaultLighting();
	LightData* Create(std::string name = "newLight", Shader* shader = NULL, LightData* light = NULL);
	LightData* RunLightData(Shader* shader, Camera* aCamera, LightObject* lightObj);
	void Destroy(Lighting* light, LightData* lightData);
	Lighting* UseShadowDepth(Shader* shader, LightData* lightData);
	Lighting* LoadCubeMaps(Texture* shadowTexture);

	Lighting* ShadowMapStep1(Shader* shader, Camera* myCamera);
	Lighting* ShadowMapStep2(Shader* shader);
	Lighting* ShadowMapStep3(Shader* shader);
	Lighting* DebugShadow(Shader* shader);

	LightData* SetDirectional(LightData* aLightData);
	LightData* SetPoint(LightData* aLightData);
	LightData* SetSpot(LightData* aLightData);

	Lighting* InitDepthMapping(Texture* shadowTexture = NULL);
	Lighting* InitShaderMaps(Shader* shader);

	
	glm::vec3 zeros = { 0.0f,0.0f,0.0f };
	float near_plane = 1.0f, far_plane = 100.0f;
	const unsigned int SHADOW_WIDTH = 1920, SHADOW_HEIGHT = 1080;
	float aspect = (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT;
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;
	GLuint depthMapFBO;
	GLuint depthMap;
	GLuint ShadowMap;
	unsigned int depthCubemap;


	unsigned int* texture;

	glm::mat4 viewTEST;

};

