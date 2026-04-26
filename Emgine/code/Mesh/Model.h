
#include "Mesh.h"
//#include <../../Dependencies/assimp/postprocess.h>
#include <scene.h>
#include <postprocess.h>

//#include "Shader.h"
#include "Texture.h"
#pragma once



class Model
{
public:
	Model();

	void Draw(Shader& shader);

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

};

