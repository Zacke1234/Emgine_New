#include <iostream>
#include <glm.hpp>
#include "../../../Dependencies/gl.h"
 
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <gtc/type_ptr.hpp>
#include <Object.h>




std::vector<Shader*> Shader::shaderList;

std::string Shader::LoadShader(const char* aPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(aPath);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();
		shaderCode = shaderStream.str();

		return shaderCode;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Could not load shader file from path - " << aPath << "\n";
		return "";
	}
}

Shader::Shader(const char* VertexPath, const char* FragmantPath, const char* GeometryPath)
{
	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmantShader;
	unsigned int geometryShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexCodeString = LoadShader(VertexPath);
	const char* vertexCode = vertexCodeString.c_str();
	GL_CHECK(glShaderSource(vertexShader, 1, &vertexCode, NULL));

	GL_CHECK(glCompileShader(vertexShader));

	fragmantShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmantCodeString = LoadShader(FragmantPath);
	const char* fragmantCode = fragmantCodeString.c_str();
	GL_CHECK(glShaderSource(fragmantShader, 1, &fragmantCode, NULL));

	GL_CHECK(glCompileShader(fragmantShader));

	if (GeometryPath != nullptr)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		std::string geometryCodeString = LoadShader(GeometryPath);
		const char* geometryCode = geometryCodeString.c_str();
		GL_CHECK(glShaderSource(geometryShader, 1, &geometryCode, NULL));

		GL_CHECK(glCompileShader(geometryShader));

	}
	

	ShaderProgram = glCreateProgram();
	
	GL_CHECK(glAttachShader(ShaderProgram, vertexShader));
	GL_CHECK(glAttachShader(ShaderProgram, fragmantShader));

	if (GeometryPath != nullptr)
	{
		GL_CHECK(glAttachShader(ShaderProgram, geometryShader));
	}
	
	GL_CHECK(glLinkProgram(ShaderProgram));
	
	
	char Log[512];
	

	int fragmentResult;
	int vertexResult;
	int geometryResult;
	
	GL_CHECK(glGetShaderiv(fragmantShader, GL_COMPILE_STATUS, &fragmentResult));
	GL_CHECK(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexResult));
	if (GeometryPath != nullptr)
	{
		GL_CHECK(glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &geometryResult));
	}


	if (!fragmentResult)
	{
		GL_CHECK(glGetShaderInfoLog(fragmantShader, 512, NULL, Log));
		std::cout << "Failed to compile fragment shader \n" << Log << std::endl;
	}
	if (!vertexResult)
	{
		GL_CHECK(glGetShaderInfoLog(vertexShader, 512, NULL, Log));
		std::cout << "Failed to compile vertex shader \n" << Log << std::endl;
	}
	if (GeometryPath != nullptr)
	{
		if (!geometryResult)
		{
			GL_CHECK(glGetShaderInfoLog(geometryShader, 512, NULL, Log));
			std::cout << "Failed to compile geometry shader \n" << Log << std::endl;
		}
	
	}
	
	glDetachShader(ShaderProgram, fragmantShader);
	glDeleteShader(fragmantShader);
	glDetachShader(ShaderProgram, vertexShader);
	glDeleteShader(vertexShader);

	if (GeometryPath != nullptr)
	{
		glDetachShader(ShaderProgram, geometryShader);
		glDeleteShader(geometryShader);
	}

}

void Shader::UseShader()
{
	GL_CHECK(glUseProgram(ShaderProgram));
}

void Shader::SetMatrix(const char* name, glm::mat4 aMatrix)
{
	GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name), 1, GL_FALSE, glm::value_ptr(aMatrix)));
}
void Shader::SetVec2(const char* name, glm::vec2 aVec2)
{
	GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name), 1, GL_FALSE, glm::value_ptr(aVec2)));
}
void Shader::SetVec3(const char* name, glm::vec3 aVec3)
{
	GL_CHECK(glUniform3fv(glGetUniformLocation(ShaderProgram, name), 1, glm::value_ptr(aVec3)));
}
void Shader::SetVec4(const char* name, glm::vec4 aVec4)
{
	GL_CHECK(glUniform4fv(glGetUniformLocation(ShaderProgram, name), 1, glm::value_ptr(aVec4)));

}
void Shader::SetFloat(const std::string name, float aFloat)
{
	GL_CHECK(glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), aFloat));
}
void Shader::SetInt(const std::string name, int aInt)
{
	GL_CHECK(glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), aInt));
}
