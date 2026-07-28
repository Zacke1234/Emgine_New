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
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // vertex generation
    std::vector<float> vertices;
    int rez = 1;
    float yScale = 64.0f / 256.0f, yShift = 16.0f;  // apply a scale+shift to the height data
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            // retrieve texel for (i,j) tex coord
            unsigned char* texel = data + (j + width * i) * channels;
            // raw height at coordinate
            unsigned char y = texel[0];

            // vertex
            vertices.push_back(-height / 2.0f + height*i/(float)height);        // v.x
            vertices.push_back((int)y * yScale - yShift); // v.y
            vertices.push_back(-width / 2.0f + width*j/(float)width);        // v.z
        }
    }

    stbi_image_free(data);

    // index generation
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < height - 1; i++)       // for each row a.k.a. each strip
    {
        for (unsigned int j = 0; j < width; j++)      // for each column
        {
            for (unsigned int k = 0; k < 2; k++)      // for each side of the strip
            {
                indices.push_back(j + width * (i + k*rez));
            }
        }
    }

    NUM_STRIPS = (height - 1) / rez;
    NUM_VERTS_PER_STRIP = (width * 2) * 2-2;

   
     

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
    for (unsigned int strip = 0; strip < NUM_STRIPS; ++strip)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
            NUM_VERTS_PER_STRIP, // number of indices to render
            GL_UNSIGNED_INT,     // index data type
            (void*)(sizeof(unsigned int)
                * NUM_VERTS_PER_STRIP
                * strip)); // offset to starting index
    }
    
}
