#pragma once
#include "vector"
#include "Message.h"
#include <gtc/matrix_transform.hpp>
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <list>
#include "fstream"
#include <vec3.hpp>
#include <string>




#pragma once
struct Face {
	
	int positionIndices[3] = {-1, -1, -1};
	int uvIndices[3] = { -1, -1, -1 };
	int normalIndices[3] = { -1, -1, -1 };
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal = glm::vec3(0, 0, 1);
	glm::vec2 uv;
	
};

struct Mesh{
	
public:
	
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	std::vector<float> data;
	std::vector<unsigned int> elements;
	int vertexbuffer = 0;
	unsigned int numberVertices = 0;
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	size_t indexCount = 0, vertexCount = 0;


	
	
	

	void InitialiseMesh();
};

enum MeshLoadStage {
	ParsingObj = 0,
	ReadingVertices,
	ReadingFaces,
	ReadingUVs,
	ReadingNormals,
	InitialisingMesh,
	BinaryWriting,
	BinaryParsing,
	MeshLoaded
};


class MeshLoader
{
public:
	
	MeshLoadStage stage;
	MeshLoader();
	bool ObjParser(std::string fileName, Mesh* mesh);
	void ParseFaceIndices(const std::string& string, Face& face, int vertexIndex);

	
	void Faces(Face& face);
	void Vertices(Vertex& vertex);
	void UVs(Vertex& vertex);
	void Normals(Vertex& vertex);
	virtual bool ParseObjToBinary(std::ifstream& filePath, std::ofstream& filepathOut, std::string fileString, Mesh* mesh);
	virtual bool ParseBinaryToMesh(std::string fileString, std::ifstream& fstreamPath, std::ofstream& filepathOut, Mesh* mesh);

	std::string name;
	std::string type;

	std::vector <Vertex> tmp;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	//std::vector <glm::vec3> temp_vertices; // glm::vec3 
	std::vector<Vertex> temp_vertices; // glm::vec3
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<Face> temp_faces;
	std::vector<glm::vec3> temp_position;
	std::string face_result;
	
};



