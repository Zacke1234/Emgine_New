#include "ShaderManager.h"

Shader* ShaderManager::InitDefaultShader()
{
	DefaultShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	DefaultShader->shaderName = "defaultShader";
	Shader::shaderList.push_back(DefaultShader);
	return DefaultShader;
}

Shader* ShaderManager::Create(std::string name, const char* VertexPath, const char* FragmantPath)
{
	
	Shader* myShader = new Shader(VertexPath, FragmantPath);
	myShader->shaderName = name;
	Shader::shaderList.push_back(myShader);
	//DefaultShader =+ myShader;
	return myShader;
}

Shader* ShaderManager::Find(std::string name)
{
	for (Shader* shader : Shader::shaderList)
	{
		if (shader->shaderName == name)
		{
			return shader;
		}
	}
	return nullptr;
}

// C:\Users\zackarias.hager\source\repos\Emgine\Shader