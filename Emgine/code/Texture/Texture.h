
//using namespace std;
#pragma once
#include <string>
#include <stb_image.h>
#include <vector>
#include "Shader.h"
#include <glm.hpp>
#include <Material/Material.h>

//#define STB_IMAGE_IMPLEMENTATION
class Texture
{
public:
	Texture();
	Texture(const char* aPath, Material* mat);
	~Texture();	

	static std::vector<Texture*> textures;
	static std::vector<Material*> materials;
	Material* myMaterial; // This is wrong. a texture should be the child of a material, not the other way around
	std::string texturePath = "";
	std::string name;
	int Width = 0;
	int Height = 0;
	int Channels = 0;
	unsigned char* data;
	unsigned int TextureObject = 0;

	void SetMaterial(Material& mat);
	bool IsValid() const { return TextureObject == 0; };


	
	
	
};

