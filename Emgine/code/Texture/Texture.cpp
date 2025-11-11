#include "Texture.h"
#include <glfw3.h>
#include <glad.h>
#include "stb_image.h"
#include <iostream>
#include "glm.hpp"

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		__debugbreak();
	}
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif

#pragma once
float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };


Texture::Texture(const char* aPath)
{
	msg = "";
	//std::cout << "texture" << "\n";
	//aPath = "Default 1.png";
	int Channels = 0;
	Width = 1920;
	Height = 1080;
	
	unsigned char* data = stbi_load(aPath, &Width, &Height, &Channels, 0);
	
	glGenTextures(1, &TextureObject);
	glBindTexture(GL_TEXTURE_2D, TextureObject);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data != NULL)
	{
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		msg = "Texture loaded in";
		
	}
	
	stbi_image_free(data);
	
}


