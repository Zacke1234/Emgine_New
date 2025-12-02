#pragma once
#include <string>
#include "Texture.h"
#include <vector>
class TextureManager
{
public:
	
	Texture* Create(std::string name = "newtexture", std::string path_end = NULL);
	Texture* Find(std::string name);
	Material InitializeMaterial(Shader* shader = NULL, Material* mat = NULL);
};

