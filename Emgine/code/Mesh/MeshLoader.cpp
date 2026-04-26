#include "MeshLoader.h"
#include "fstream"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <Texture.h>
#include <Object.h>
#include "MeshManager.h"
#include <bitset>
#include <cassert>
using namespace std;

// do breakpoints
int n;
MeshLoader::MeshLoader()
{

}

MeshLoader::~MeshLoader()
{

}

// https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

bool runOnce = false;
bool MeshLoader::ObjParser(std::string fileName, Mesh* INmesh)
{

	if (INmesh == nullptr)
	{
		return false;
	}

	Mesh& mesh = *INmesh;

	std::ifstream file(fileName);
	
	std::string line;
	
	if (!file.is_open())
	{
		std::cerr <<  "Failed to open file: " << fileName << std::endl;
		return false;
	}
	
	while (std::getline(file, line)){
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;
		
		if (prefix == "v")
		{
			
			glm::vec3 position;
			iss >> position.x >> position.y >> position.z;
			
			temp_position.push_back(position);
			mesh.position.push_back(position);
			
			
		}
		if (prefix == "f")
		{
			
			Face face;
			int vertexIndex = 0;
			std::string newFace;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;
			
			iss >> newFace;
		
			temp_faces.push_back(face);
			mesh.faces.push_back(face);
			
		}
		if (prefix == "vt") 
		{
			
			glm::vec2 UV;
			iss >> UV.x >> UV.y;

			temp_uvs.push_back(UV);
			mesh.uvs.push_back(UV);
		}

		if (prefix == "vn")
		{
			
			glm::vec3 NORMAL;
			iss >> NORMAL.x >> NORMAL.y >> NORMAL.z;

			temp_normals.push_back(NORMAL);
			mesh.normals.push_back(NORMAL);
		}
		if (prefix == "mtllib") // load in the material from the file onto the mesh
		{
			
			
			std::cout << "Material", "\n";
			

		}
		
	}


	file.close();
	
	
	for (int i = 0; i < temp_faces.size(); i++) 
	{
		Vertex vertices[3];
		

		//Vertex vertex = temp_vertices[i];
		Face face = temp_faces[i];
		//vertices = temp_vertices(position, normal, uv);

		for (int e = 0; e < 3; e++)
		{
			int index = face.positionIndices[e];
			Vertex& v = vertices[e];

			if (index != -1)
			{
				v.position = temp_position[index - 1];

			}

			index = face.normalIndices[e];

			if (index != -1)
			{
				v.normal = temp_normals[index - 1];



			}

			index = face.uvIndices[e];

			if (index != -1)
			{

				v.uv = temp_uvs[index - 1];

			}



		}
		// calculate tangents

		CalculateTangent(vertices[0], vertices[1], vertices[2]);
		CalculateTangent(vertices[1], vertices[0], vertices[2]);
		CalculateTangent(vertices[2], vertices[1], vertices[0]);

		for (int e = 0; e < 3; e++)
		{
			
			Vertex& v = vertices[e];
			

			mesh.data.push_back(v.position.x);
			mesh.data.push_back(v.position.y);
			mesh.data.push_back(v.position.z);
				

			mesh.data.push_back(v.normal.x);
			mesh.data.push_back(v.normal.y);
			mesh.data.push_back(v.normal.z);

   			
			mesh.data.push_back(v.uv.x);
			mesh.data.push_back(v.uv.y);


			// push back tangents

			mesh.data.push_back(v.tangent.x);
			mesh.data.push_back(v.tangent.y);
			mesh.data.push_back(v.tangent.z);

			mesh.data.push_back(v.binormal.x);
			mesh.data.push_back(v.binormal.y);
			mesh.data.push_back(v.binormal.z);
			
			mesh.elements.push_back(mesh.numberVertices);
			temp_elements.push_back(mesh.numberVertices);
			
			//temp_vertices.push_back(vertices);

			mesh.numberVertices++;
			
		}
		
	}
	
	temp_faces.clear();
	temp_normals.clear();
	temp_position.clear();
	temp_uvs.clear();
	temp_vertices.clear();
	temp_elements.clear();

	return true;
}

bool MeshLoader::BinParser(std::string bineFileName, Mesh* mesh)
{
	std::ifstream binFile(bineFileName);
	std::string line;
	if (!binFile.is_open())
	{
		std::cout << "Filename empty" << std::endl;
		return false;
	}

	if (mesh == nullptr)
	{
		std::cout << "mesh is nullptr" << std::endl;
		return false;
	}

	// Parse the Binary file back into the human readable OBJ format and initialise the mesh with that exact data.

	int dataLength = mesh->data.size(); // redo this for the cache loading
	int elementsLength = mesh->elements.size();
	int positionLength = mesh->position.size();
	int normalsLength = mesh->normals.size();
	int uvLength = mesh->uvs.size();
	int facesLength = mesh->faces.size();

	
	for (int i = 0; i < positionLength; i++)
	{


		glm::vec3 positionBinary = mesh->position[i];


		binFile.read((char*)(&positionBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < facesLength; i++)
	{


		Face facesBinary = mesh->faces[i];


		binFile.read((char*)(&facesBinary),
			sizeof(Face));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < uvLength; i++)
	{


		glm::vec2 uvBinary = mesh->uvs[i];


		binFile.read((char*)(&uvBinary),
			sizeof(glm::vec2));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < normalsLength; i++)
	{


		glm::vec3 normalBinary = mesh->normals[i];


		binFile.read((char*)(&normalBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < dataLength; i++)
	{

		float dataBinary = mesh->data[i];

		binFile.read((char*)(&dataBinary),
			sizeof(float));

	}




	mesh->InitialiseMesh();
	return false;
}

static inline std::vector<std::string> SplitString(const std::string& str, char delimeter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimeter))
	{
		tokens.push_back(token);
	
	}
	return tokens;

}

void MeshLoader::ParseFaceIndices(const std::string& string, Face& face, int vertexIndex)
{
	
	/*auto foundIndex = string.find('/');
	face_result = string.substr  (0, foundIndex);*/

	char del = '/';

	std::string indexString = "";
	int indexCounter = 0;
	n = 0;
	std::vector<std::string> tokens = SplitString(string, del);
	
	for (std::string& token : tokens)
	{
		int index = std::atoi(token.c_str());
		if (indexCounter == 0)
		{
			face.positionIndices[vertexIndex] = index;
		}
		else if (indexCounter == 2)
		{
			face.normalIndices[vertexIndex] = index;
		}
		else if (indexCounter == 1)
		{
			face.uvIndices[vertexIndex] = index;
		}
		indexCounter++;
		n++;
	}
}


void MeshLoader::CalculateTangent(Vertex& A, const Vertex& B, const Vertex& C)
{

	glm::vec3 dpAB = B.position - A.position;

	glm::vec3 dpAC = C.position - A.position;

	glm::vec2 dtAB = B.uv - A.uv;

	glm::vec2 dtAC = C.uv - A.uv;

	float r = 1.0f / (dtAB.x * dtAC.y - dtAB.y * dtAC.x);

	glm::vec3 T = (dpAB * dtAC.y - dpAC * dtAB.y) * r;

	glm::vec3 Bn = (dpAC * dtAB.x - dpAB * dtAC.x) * r;

	glm::vec3 N = (A.normal);

	glm::vec3 X = glm::cross(N, T);

	T = glm::cross(X, N);
	T = glm::normalize(T);
	// get updated bi-tangent
	X = glm::cross(Bn, N);
	Bn = glm::cross(N, X);
	Bn = glm::normalize(Bn);

	A.tangent = T;
	A.binormal = Bn;


}

bool MeshLoader::ReadObjToBinary(std::string objPath, std::ifstream& objReadFile, Mesh* mesh) // read
{
	ObjParser(objPath, mesh);
	int dataLength = mesh->data.size();
	int elementsLength = mesh->elements.size();
	int positionLength = mesh->position.size();
	int normalsLength = mesh->normals.size();
	int uvLength = mesh->uvs.size();
	int facesLength = mesh->faces.size();
	
	

	if (!objReadFile.is_open())
	{
		cerr << "Error: Failed to open for parsing" << endl;
		return false;
	}
	for (int i = 0; i < positionLength; i++)
	{


		glm::vec3 positionBinary = mesh->position[i];


		objReadFile.read((char*)(&positionBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < facesLength; i++)
	{


		Face facesBinary = mesh->faces[i];


		objReadFile.read((char*)(&facesBinary),
			sizeof(Face));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < uvLength; i++)
	{


		glm::vec2 uvBinary = mesh->uvs[i];


		objReadFile.read((char*)(&uvBinary),
			sizeof(glm::vec2));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < normalsLength; i++)
	{


		glm::vec3 normalBinary = mesh->normals[i];


		objReadFile.read((char*)(&normalBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < dataLength; i++)
	{

		float dataBinary = mesh->data[i];

		objReadFile.read((char*)(&dataBinary),
			sizeof(float));

	}

	
	

	for (int i = 0; i < elementsLength; i++)
	{


		unsigned int elementsBinary = mesh->elements[i];

		
		objReadFile.read((char*)(&elementsBinary),
			sizeof(unsigned int));
		//std::cout << elementsBinary << endl;
	}

	
	
	
	//mesh->InitialiseMesh();

	
	

	objReadFile.close();
	
	return true;
}

bool MeshLoader::WriteObjToBinary(std::ofstream& binaryOutputFile, 
	std::string ObjFilePath, Mesh* mesh) // write
{
	
	

	int dataLength = mesh->data.size();
	int elementsLength = mesh->elements.size();

	int positionLength = mesh->position.size();
	int normalsLength = mesh->normals.size();
	int uvLength = mesh->uvs.size();

	int facesLength = mesh->faces.size();

	if (!binaryOutputFile.is_open())
	{
		cerr << "Error: Failed to open for parsing" << endl;
		return false;
	}
	for (int i = 0; i < positionLength; i++)
	{


		glm::vec3 positionBinary = mesh->position[i];


		binaryOutputFile.write((const char*)(&positionBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < facesLength; i++)
	{


		Face facesBinary = mesh->faces[i];


		binaryOutputFile.write((const char*)(&facesBinary),
			sizeof(Face));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < uvLength; i++)
	{


		glm::vec2 uvBinary = mesh->uvs[i];


		binaryOutputFile.write((const char*)(&uvBinary),
			sizeof(glm::vec2));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < normalsLength; i++)
	{


		glm::vec3 normalBinary = mesh->normals[i];


		binaryOutputFile.write((const char*)(&normalBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < dataLength; i++)
	{
		
		float dataBinary = mesh->data[i];
		

		binaryOutputFile.write((const char*)(&dataBinary),
			sizeof(float));
		


	}
	
	for (int i = 0; i < elementsLength; i++)
	{

		
		unsigned int elementsBinary = mesh->elements[i];

		binaryOutputFile.write((const char*)(&elementsBinary),
			sizeof(unsigned int));


	}

	
	//std::cout << reinterpret_cast<char*>(&TEST) << std::endl;
	
	binaryOutputFile.close();
	return true;
	
}













