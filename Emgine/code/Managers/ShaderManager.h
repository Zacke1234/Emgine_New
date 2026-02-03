#pragma once
#include <string>
#include "Shader.h"
class ShaderManager
{
public:

	Shader* DefaultShader;
	Shader* InitDefaultShader();

	Shader* Create(std::string name, const char* VertexPath, const char* FragmantPath);

	Shader* Find(std::string name);

};

