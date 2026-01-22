#include "Lighting.h"
#include <glad.h>
#include <vector>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#pragma once

std::vector<LightData*> Lighting::dirLights;
std::vector<LightData*> Lighting::spotLights;
std::vector<LightData*> Lighting::pointLights;
std::vector<glm::vec3*> Lighting::pointLightPositions;
std::vector<glm::vec3*> Lighting::speculars;
std::vector<glm::vec3*> Lighting::diffuses;
std::vector<glm::vec3*> Lighting::ambients;
std::vector<float*> Lighting::constants;
std::vector<float*> Lighting::linears;
std::vector<float*> Lighting::quadtrics;
std::vector<float*> Lighting::cutOffs;
std::vector<float*> Lighting::outerCutOffs;
std::vector<glm::vec3*> Lighting::DirLightDirections;
std::vector<glm::vec3*> Lighting::spotLightPositions;
std::vector<glm::vec3*> Lighting::spotLightDirections;


