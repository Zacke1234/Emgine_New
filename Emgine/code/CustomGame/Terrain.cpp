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

    // vertex generation
    
    float yScale = 64.0f / 256.0f, yShift = 16.0f;
    int rez = 1;
    unsigned bytePerPixel = channels;
    for (int i = 0; i < height; i++)
    {
        int c = 0;
      //  c += 1;
        for (int j = 0; j < width; j++)
        {
            
            unsigned char* pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];
            //TERRAIN_HEIGHT = vertices[i];
            // vertex
            vertices.push_back(-height / 2.0f + height * i / (float)height);   // vx
            vertices.push_back((int)y * yScale - yShift);   // vy
            vertices.push_back(-width / 2.0f + width * j / (float)width);   // vz
            //heightMap +=  {-height / 2.0f + height * i / (float)height} ;
            /*points.push_back(glm::vec3(-height / 2.0f + height * i / (float)height, 
                (int)y * yScale - yShift,
                -width / 2.0f + width * j / (float)width));*/
            c = 0;
            heightMap[i][c] = -height / 2.0f + height * i / (float)height;
            c++;
            heightMap[i][c] = -width / 2.0f + width * i / (float)width;
           
        }
    }

    //terrainTransform;
    //heightMap2;
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

float Terrain::GetHeightInterporlated(float x, float z, float heights[256][2])
{
   
    float gridSquareLength = height / ((float)width - 1);
    int gridX = (int)std::floor(x - 1 / gridSquareLength);
    int gridZ = (int)std::floor(z - 1 / gridSquareLength);

    if (gridX >= width - 1 || gridZ >= height - 1 || gridX < 0 || gridZ < 0)
    {
        return 0;
    }
    float xCoord = std::fmod(x - 1, gridSquareLength) / gridSquareLength;
    float zCoord = std::fmod(z - 1, gridSquareLength) / gridSquareLength;
    float answer = 0.0;

    if (xCoord <= (1 - zCoord))
    {
        answer = barryCentric(glm::vec3(0, heights[gridX][gridZ], 0),
            glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(0, heights[gridX][gridZ + 1], 1),
            glm::vec2(xCoord, zCoord));
    }

    else
    {
        answer = barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0),
            glm::vec3(1, heights[gridX + 1][gridZ + 1], 1), glm::vec3(0, heights[gridX][gridZ + 1], 1),
            glm::vec2(xCoord, zCoord));
    }

    return answer;
}

float Terrain::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

