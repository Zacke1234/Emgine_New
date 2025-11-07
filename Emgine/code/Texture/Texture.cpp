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
	GL_CHECK(glGenTextures(1, &TextureObject));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, TextureObject));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	//Shadows
	

	if (data != NULL)
	{
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
		GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, TextureObject, 0));
		GL_CHECK(glDrawBuffer(GL_NONE));
		GL_CHECK(glReadBuffer(GL_NONE));
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		//std::cout << "data = true" << "\n";
		GL_CHECK(glGenFramebuffers(1, &depthMapFBO));
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		// 2
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, TextureObject));

		/*glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);*/
		
		GL_CHECK(glCullFace(GL_FRONT));
		GL_CHECK(glCullFace(GL_BACK));
		GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
		GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));

		

		//glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		
		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		// configure shader and matrices
		// render scene
		
		//
		//glViewport(0, 0, Width, Height);
		

		


		msg = "Texture loaded in";
		//message->SendMessage(msg, 0);
	}
	
	stbi_image_free(data);
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}


