#pragma once
#include <Lighting.h>
class LightingManager
{
public: 
	
	LightingManager();
	LightData* DefaultLighting;
	
	LightData* InitDefaultLighting();
	LightData* Create(std::string name = "newLight", Shader* shader = NULL, LightData* light = NULL);
	LightData* RunLightData(Shader* shader, LightData* aLightData, Camera* aCamera);
	void Destroy(Lighting* light, LightData* lightData);
	Lighting* UseShadowDepth(Shader* shader, LightData* lightData);

	Lighting* ShadowMapStep1(Shader* shader, Camera* myCamera, Texture* texture);
	Lighting* ShadowMapStep2(Shader* shader, Texture* texture);
	Lighting* ShadowMapStep3(Shader* shader);

	LightData* SetDirectional(LightData* aLightData, Object* test);
	LightData* SetPoint(LightData* aLightData, Object* test = NULL);
	LightData* SetSpot(LightData* aLightData, Object* test);

	Lighting* InitDepthMapping(Texture* shadowTexture = NULL);
	Lighting* InitShaderMaps(Shader* shader);

	glm::mat4 lightProjection;
	glm::vec3 zeros = { 0.0f,0.0f,0.0f };
	float near_plane = 1.0f, far_plane = 7.5f;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;
	unsigned int depthMapFBO;
	unsigned int depthMap;

	unsigned int* texture;

	

};