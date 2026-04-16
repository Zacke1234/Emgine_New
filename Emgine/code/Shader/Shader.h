#pragma once
#include <string>
#include <glm.hpp>
#include <vector>

class Shader
{
public:
	Shader(const char* VertexPath, const char* FragmantPath, const char* GSPath = NULL);

	void UseShader();

	void SetMatrix(const char* transform, glm::mat4 aMatrix);

	void SetVec2(const char* texture, glm::vec2 aVec2);

	void SetVec3(const char* texture, glm::vec3 aVec3);

	void SetVec4(const char* texture, glm::vec4 aVec4);

	void SetFloat(const std::string, float aTexCord);

	void SetInt(const std::string depth, int OutInt);

	std::string LoadShader(const char* aPath);

	unsigned int ShaderProgram;

	std::string shaderName;

	static std::vector<Shader*> shaderList;
 private:
	
};