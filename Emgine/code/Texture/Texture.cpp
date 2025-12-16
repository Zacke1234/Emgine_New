#include "Texture.h"
#include <glfw3.h>
#include <glad.h>
#include "stb_image.h"
#include <iostream>
#include "glm.hpp"
#define STB_IMAGE_IMPLEMENTATION
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
std::vector<Texture*> Texture::textures;
std::vector<Material*> Texture::materials;

Texture::Texture(const char* aPath, Material* mat = NULL)
{
	if (mat)
	{
		std::cout << "Set the material " << aPath << "\n";
		SetMaterial(*mat);
	}
	else
	{
		std::cout << "No material assigned to texture: " << aPath << "\n";
	}

	msg = "";
	//std::cout << "texture" << "\n";
	//aPath = "Default 1.png";
	int Channels = 0;
	Width = 0;
	Height = 0;
	
	unsigned char* data = stbi_load(aPath, &Width, &Height, &Channels, 0);
	
	//GL_CHECK(glEnable(GL_TEXTURE_2D));
	
	GL_CHECK(glGenTextures(1, &TextureObject));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, TextureObject));

	
	//GL_CHECK(glBindTexture(GL_TEXTURE_2D, mat->diffuse));

	// set the texture wrapping parameters


	
	/*glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

	if (data != NULL)
	{
		
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		//GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0));
		GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));

		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		// set texture filtering parameters
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		msg = "Texture loaded in";
		
	}
	else
	{
		std::cout
			<< "unable to load image: "
			<< stbi_failure_reason()
			<< "\n";
		//throw;
			
	}
	
	stbi_image_free(data);
	
}

void Texture::SetMaterial(Material& mat)
{
	this->myMaterial = &mat;
	this->myMaterial->color = { 1,1,1 };
	this->myMaterial->shininess = 1;
	this->myMaterial->specular = 1;
	this->myMaterial->diffuse = 0;

}




