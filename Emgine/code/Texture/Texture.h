
//using namespace std;
#pragma once
#include <string>
#include <glad.h>
#include <vector>
#include "Shader.h"
#include <glm.hpp>

struct Material {
	
	std::string name;
	int diffuse;
	int specular;
	float shininess;
	glm::vec3 color;
};

class Texture
{
public:
	Material* myMaterial;
	Texture(const char* aPath, Material* mat);

	unsigned char* data;

	void SetMaterial(Material& mat);
	static std::vector<Texture*> textures;
	static std::vector<Material*> materials;
	//vector<Object*> Object::Entities;
	bool IsValid() const { return TextureObject == 0; };

	std::string texturePath = "";
	//Message* message = new Message(msg);
	std::string name;
	int Width = 0;
	int Height = 0;
	int Channels = 0;

	unsigned int TextureObject = 0;
	
	
	
};

