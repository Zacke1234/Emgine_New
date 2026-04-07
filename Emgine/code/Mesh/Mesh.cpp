#include "Mesh.h"
#include <Object.h>

void Mesh::InitialiseMesh()
{
	GL_CHECK(glGenVertexArrays(1, &VAO));
	GL_CHECK(glGenBuffers(1, &VBO));
	GL_CHECK(glGenBuffers(1, &EBO));

	GL_CHECK(glBindVertexArray(VAO));

	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));

	this->vertexbuffer = VBO;

	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(float), &this->data[0], GL_STATIC_DRAW)); // Data here is zero, for some reason

	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(unsigned int), &this->elements[0], GL_STATIC_DRAW));


	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0));
	GL_CHECK(glEnableVertexAttribArray(0)); // pos

	GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(1)); // normal

	GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(2)); // uv

	GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(3)); // tangent

	GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(4)); // binormal
}
