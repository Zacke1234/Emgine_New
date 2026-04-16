#pragma once
#include "vector"
#include "Message.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <list>
#include "fstream"
#include <vec3.hpp>
#include <string>
#include "Mesh/Mesh.h"
#include "Structs/Face.h"
#include "Structs/Vertex.h"
#include "Enums/E_MeshLoadStage.h"





class MeshLoader
{
public:
	std::string name;
	std::string type;

	std::vector <Vertex> tmp;
	std::vector<unsigned int> temp_elements;
	std::vector<Vertex> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<Face> temp_faces;
	std::vector<glm::vec3> temp_position;
	std::string face_result;

	MeshLoadStage stage;

	MeshLoader();
	~MeshLoader();

	virtual bool WriteObjToBinary(std::ofstream& filepathOut, std::string fileString, Mesh* mesh);
	virtual bool ReadObjToBinary(std::string fileString, std::ifstream& fstreamPath, Mesh* mesh);
	bool ObjParser(std::string fileName, Mesh* mesh);
	bool BinParser(std::string fileName, Mesh* mesh);
	void ParseFaceIndices(const std::string& string, Face& face, int vertexIndex);
	void CalculateTangent(Vertex& A, const Vertex&  B, const Vertex& C);
	

	
	
	
};



