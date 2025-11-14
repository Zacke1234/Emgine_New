#pragma once
#include <string>
#include "Texture.h"
#include <vector>
class TextureManager
{
public:
	std::vector<Texture*> textures;
	Texture* Create(std::string name = "newtexture", std::string path_end = NULL, Material* mat = NULL);
	Texture* Find(std::string name);
	Material InitializeTexture(Shader* shader = NULL, Material* mat = NULL);
};

