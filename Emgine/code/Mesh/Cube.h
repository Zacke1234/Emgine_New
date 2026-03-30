#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include <Object.h>
#include <glfw3.h>
#include <glm.hpp>

class Object;

class Cube
{
private:
	int IndicesSize = 0;

public:
	Cube();
	~Cube();

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	size_t indexCount, vertexCount;

	void Draw(Shader* myShader, Object* Object, Camera* myCamera);
	void ApplyTexture(Texture* aTexture);
	void InitializeCube();


};

