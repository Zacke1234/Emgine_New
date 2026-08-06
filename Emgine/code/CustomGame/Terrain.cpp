#include "Terrain.h"
#include <gl.h>
#include <string>
#include <stb_image.h>
#include <iostream>
#include <GLChecking.h>



GLuint terrainVAO, terrainVBO, terrainEBO;

Terrain::Terrain()
{
	
	unsigned char* data = stbi_load("resource\\textures\\iceland_heightmap.png",
		&width, &height, &channels,
		0);

    if (data)
    {
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
        fileSize = height * width;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    terrainSize = (int)sqrtf((float)fileSize / (float)sizeof(float));
    heightMap[256] += terrainSize, data;
    // vertex generation
    
    float yScale = 64.0f / 256.0f, yShift = 16.0f;
    int rez = 1;
    unsigned bytePerPixel = channels;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char* pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];
            //TERRAIN_HEIGHT = vertices[i];
            // vertex
            vertices.push_back(-height / 2.0f + height * i / (float)height);   // vx
            vertices.push_back((int)y * yScale - yShift);   // vy
            vertices.push_back(-width / 2.0f + width * j / (float)width);   // vz
            /*points.push_back(glm::vec3(-height / 2.0f + height * i / (float)height, 
                (int)y * yScale - yShift,
                -width / 2.0f + width * j / (float)width));*/
            
            
           
        }
    }

   
    stbi_image_free(data);

    // index generation
   
    
    for (unsigned i = 0; i < height - 1; i += rez)
    {
        for (unsigned j = 0; j < width; j += rez)
        {
            for (unsigned k = 0; k < 2; k++)
            {
                indices.push_back(j + width * (i + k * rez));
                //points.push_back(glm::vec3(j + width * (i + k * rez))); 
            }
        }
    }

    NUM_STRIPS = (height - 1) / rez;
    NUM_VERTS_PER_STRIP = (width / rez) * 2 - 2;

    // register VAO
   
    GL_CHECK(glGenVertexArrays(1, &terrainVAO));
    GL_CHECK(glBindVertexArray(terrainVAO));

    GL_CHECK(glGenBuffers(1, &terrainVBO));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, terrainVBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),       // size of vertices buffer
        &vertices[0],                          // pointer to first element
        GL_STATIC_DRAW));

    // position attribute
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glGenBuffers(1, &terrainEBO));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int), // size of indices buffer
        &indices[0],                           // pointer to first element
        GL_STATIC_DRAW));
        
   // Render();

    terrainMesh = new Mesh();
    terrainMesh->name = "Terrain";
    terrainMesh->data = vertices;
    terrainMesh->elements = indices;
    terrainMesh->VAO = terrainVAO;
    terrainMesh->EBO = terrainEBO;
    terrainMesh->VBO = terrainVBO;

}

Terrain::~Terrain()
{
    /*glDeleteVertexArrays(1, &terrainVAO);
    glDeleteBuffers(1, &terrainVBO);
    glDeleteBuffers(1, &terrainIBO);*/
}





void Terrain::Render()
{
    
    // draw mesh
    GL_CHECK(glBindVertexArray(terrainVAO));
    // render the mesh triangle strip by triangle strip - each row at a time
    for (unsigned strip = 0; strip < NUM_STRIPS; strip++)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
            NUM_VERTS_PER_STRIP + 2,   // number of indices to render
            GL_UNSIGNED_INT,     // index data type
            (void*)(sizeof(unsigned) * (NUM_VERTS_PER_STRIP + 2) * strip)); // offset to starting index
        int b = 0;
    }

 

}

float Terrain::GetHeightInterporlated(float x, float z)
{
    float X0Z0Height = (x, z);

    if (((int)x + 1 >= width) || ((int)z + 1 >= width)) {
        return X0Z0Height;
    }

    float X1Z0Height = (x + 1, z);
    float X0Z1Height = (x, z + 1);
    float X1Z1Height = (x + 1, z + 1); 

    float FactorX = x - floorf(x);

    float InterpolatedBottom = (X1Z0Height - X0Z0Height) * FactorX + X0Z0Height;
    float InterpolatedTop = (X1Z1Height - X0Z1Height) * FactorX + X0Z1Height;

    float FactorZ = z - floorf(z);

    float FinalHeight = (InterpolatedTop - InterpolatedBottom) * FactorZ + InterpolatedBottom;

    return FinalHeight;
}

