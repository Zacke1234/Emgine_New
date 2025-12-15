#pragma once
#include <Lighting.h>
class LightingManager
{
public: 

	LightData* DefaultLighting;

	LightData* InitDefaultLighting();
	LightData* Create(std::string name = "newLight", Shader* shader = NULL, LightData* light = NULL);
	LightData* InitialiseLightData(Shader* shader, LightData* aLightData);
	void Destroy(Lighting* light, LightData* lightData);
	
	LightData* SetDirectional(LightData* aLightData, Object* test);
	LightData* SetPoint(LightData* aLightData, Object* test = NULL);
	LightData* SetSpot(LightData* aLightData, Object* test);

private:
	void SetFragSpot(Shader* shader, LightData* aLightData);
	void SetFragPoint(Shader* shader, LightData* aLightData);
	void SetFragDir(Shader* shader, LightData* aLightData);
	
};

