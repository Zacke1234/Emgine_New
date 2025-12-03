#include "MeshLoader.h"
#include "fstream"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <Texture.h>
#include <Object.h>
#include "MeshManager.h"
#include <bitset>
#include<cassert>
using namespace std;

// do breakpoints
int n;
MeshLoader::MeshLoader()
{
	
}

// https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

bool runOnce = false;
bool MeshLoader::ObjParser(std::string fileName, Mesh* INmesh)
{
	

	

	string message = "ObjLoaderStart";
	//Message* mess = new Message(message);
	 // if bin file, return?
	
	
	if (INmesh == nullptr)
	{
		return false;
	}

	Vertex vertex;
	Vertex vertexNor;
	Vertex vertexUV;
	Mesh& mesh = *INmesh;

	std::ifstream file(fileName);
	//bin.FileName = fileName;


	
	//printf("%s", file.binary);

	
	
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
		
		if (prefix == "o")
		{
			/*iss >> name;
			name.push_back();*/
		}
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
			//if (mesh.numberVertices == 4 && runOnce == false) // This can't actually tell triangulated and non triangulated meshes apart.
			//{
			//	runOnce = true;
			//	//std::cout << "This engine does not support mesh files with quads, please make sure the file is triangulated" << "\n";
			//	//std::exit(EXIT_FAILURE);
			//	//std::abort();
			//	
			//}

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

	//bin.ReadFile();
	//bin.WriteFile();

	

	file.close();
	
	
	for (int i = 0; i < temp_faces.size(); i++) 
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;

		//Vertex vertex = temp_vertices[i];
		Face face = temp_faces[i];
		//vertices = temp_vertices(position, normal, uv);

		for (int e = 0; e < 3; e++)
		{
			
			int index = face.positionIndices[e]; 
			
			
			if (index == -1)
			{
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
			}
			else
			{
				position = temp_position[index - 1]; 

				mesh.data.push_back(position.x);
				mesh.data.push_back(position.y);
				mesh.data.push_back(position.z);
				
			}

			index = face.normalIndices[e];

			if (index == -1)
			{
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
			}
			else
			{
				normal = temp_normals[index - 1];
				mesh.data.push_back(normal.x);
				mesh.data.push_back(normal.y);
				mesh.data.push_back(normal.z);
				

			}
			
			index = face.uvIndices[e];

			if (index == -1)
			{
				mesh.data.push_back(0.0f);
				mesh.data.push_back(0.0f);
			}
			else
			{
   				uv = temp_uvs[index - 1];
				mesh.data.push_back(uv.x);
				mesh.data.push_back(uv.y);
			}
			
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
	/*ParseObjToBinary(fileName, &file);
	ParseObjToBinary(fileName, *file);*/
	return true;
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


void MeshLoader::Faces(Face& face)
{
}

void MeshLoader::Vertices(Vertex& vertex)
{
}

void MeshLoader::UVs(Vertex& vertex)
{
}

void MeshLoader::Normals(Vertex& vertex)
{
}

bool MeshLoader::ParseBinaryToMesh(std::string binaryPath, std::ifstream& binaryInputFile, std::ofstream& binaryOutputFile, Mesh* mesh) // read
{
	
	int dataLength = mesh->data.size();
	int elementsLength = mesh->elements.size();
	int positionLength = mesh->position.size();
	int normalsLength = mesh->normals.size();
	int uvLength = mesh->uvs.size();
	int facesLength = mesh->faces.size();

	if (!binaryInputFile.is_open())
	{
		cerr << "Error: Failed to open for parsing" << endl;
		return false;
	}
	for (int i = 0; i < positionLength; i++)
	{


		glm::vec3 positionBinary = mesh->position[i];


		binaryInputFile.read((char*)(&positionBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < facesLength; i++)
	{


		Face facesBinary = mesh->faces[i];


		binaryInputFile.read((char*)(&facesBinary),
			sizeof(Face));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < uvLength; i++)
	{


		glm::vec2 uvBinary = mesh->uvs[i];


		binaryInputFile.read((char*)(&uvBinary),
			sizeof(glm::vec2));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < normalsLength; i++)
	{


		glm::vec3 normalBinary = mesh->normals[i];


		binaryInputFile.read((char*)(&normalBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < dataLength; i++)
	{

		float dataBinary = mesh->data[i];
		
		

		binaryInputFile.read((char*)(&dataBinary),
			sizeof(float));
	


	}

	
	

	for (int i = 0; i < elementsLength; i++)
	{


		unsigned int elementsBinary = mesh->elements[i];

		
		binaryInputFile.read((char*)(&elementsBinary),
			sizeof(unsigned int));
		//std::cout << elementsBinary << endl;
	}

	
	
	mesh->InitialiseMesh();

	binaryInputFile.close();
	
	return true;
}

bool MeshLoader::ParseObjToBinary(std::ifstream& ObjInputFile, std::ofstream& binaryOutputFile, std::string ObjFilePath, Mesh* mesh) // write
{
	
	
	ObjParser(ObjFilePath, mesh);
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

	
}








void Mesh::InitialiseMesh()
{
	
	//std::cout << "initialise object file" << "\n";
	
	/*if (data.size() != NULL)
	{
		data.clear();
		elements.clear();
	}*/
	
	GL_CHECK(glGenVertexArrays(1, &VAO));
	GL_CHECK(glGenBuffers(1, &VBO));
	GL_CHECK(glGenBuffers(1, &EBO));

	GL_CHECK(glBindVertexArray(VAO));

	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));

	this->vertexbuffer = VBO;

	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(float), &this->data[0], GL_STATIC_DRAW)); // Data here is zero, for some reason

	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(unsigned int), &this->elements[0], GL_STATIC_DRAW));

	
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
	GL_CHECK(glEnableVertexAttribArray(0));



	GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(1));


	GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
	
	GL_CHECK(glEnableVertexAttribArray(2));

	//GL_CHECK(glBindVertexArray(0));
	//data.clear();
	//elements.clear();
	//numberVertices = 0;
	//VAO = 0;
	//VBO = 0;
	//EBO = 0;
	//vertexbuffer = 0;
	//faces.clear();
	//vertices.clear();
	
}




