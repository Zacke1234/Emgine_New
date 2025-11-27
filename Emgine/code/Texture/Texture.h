
//using namespace std;
#pragma once
#include <string>
#include <glad.h>
#include <vector>
#include "Shader.h"
#include <glm.hpp>

struct Material {
	
	int diffuse = 0;
	int specular;
	float shininess;
	glm::vec3 color;
};

class Texture
{
public:
	Material* myMaterial = new Material();
	Texture(const char* aPath, Material* mat);

	static std::vector<Texture*> textures;

	//vector<Object*> Object::Entities;
	bool IsValid() const { return TextureObject == 0; };

	std::string msg;
	//Message* message = new Message(msg);
	std::string name;
	int Width = 0;
	int Height = 0;

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int TextureObject = 0;
	unsigned int depthMapFBO = 0;

	
	
};

