#include "TextureManager.h"
#include <filesystem>
#include <iostream>

Texture* TextureManager::Create(std::string name, std::string path_end)
{
	std::string path = "resource\\textures\\";
	Material* mat = new Material();
	mat->name = name;
	
	Texture* new_texture = new Texture((path + path_end).c_str(), mat);
	new_texture->name = name; 
	//new_texture->texturePath = (path.c_str() + *path_end.c_str());
	
	Texture::textures.push_back(new_texture);
	Texture::materials.push_back(mat);
	std::cout << "Texture created: " << name << " from path: " << path + path_end << "\n";
	return new_texture;
}


Texture* TextureManager::Find(std::string name) {
	for (Texture* texture : Texture::textures)
		{
		if (texture->name == name)
			{
			return texture;
			std::cout << "Texture found: " << name << "\n";
			}
		}
	std::cout << "Texture not found: " << name << "\n";
	return nullptr;
}

Material TextureManager::InitializeMaterial(Shader* shader, Material* mat)
{

	shader->SetInt("material.diffuse", mat->diffuse);
	shader->SetInt("material.specular", mat->specular);
	shader->SetFloat("material.shininess", mat->shininess);
	shader->SetVec3("material.objectColor", mat->color);
	return *mat;

}