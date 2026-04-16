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
	LightData* Destroy(Shader* aShader, Object* obj);
	LightData* RunLightData(Shader* shader, Camera* aCamera);

	Lighting* UseShadowDepth(Shader* shader, LightData* lightData);
	Lighting* RunMainFragmentShadows(Shader* shader, LightData* lightData);
	Lighting* LoadCubeMaps(Texture* shadowTexture);
	
	LightData* SetDirectional(LightData* aLightData);
	LightData* SetPoint(LightData* aLightData);
	LightData* SetSpot(LightData* aLightData);

	Lighting* InitDepthMapping();
	Lighting* InitShaderMaps(Shader* shader);

	Lighting* BindFrameBuffer();
	Lighting* ActiveTextureDepth();
	Lighting* BindTexture();
	Lighting* BindDepthTexture();
	Lighting* Viewport();	
	
	unsigned int SCR_WIDTH = 1024;
	unsigned int SCR_HEIGHT = 1024;
	const unsigned int SHADOW_WIDTH = SCR_WIDTH , SHADOW_HEIGHT = SCR_HEIGHT;
	GLuint depthMapFBO;
	GLuint depthMap;
	GLuint ShadowMap;
	unsigned int depthCubemap;
	bool LightHasInitalised;
};

