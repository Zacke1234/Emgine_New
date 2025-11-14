#include "MeshLoader.h"
#include "fstream"
#include <iostream>
#include <sstream>
#include <filesystem>
#include "Texture.h"
#include <Object.h>
#include "MeshManager.h"
#include <bitset>
using namespace std;

// do breakpoints

MeshLoader::MeshLoader()
{
	
}

// https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

bool runOnce = false;
bool MeshLoader::ObjParser(std::string fileName, Mesh* INmesh)
{
	BinaryFile bin((name + ".bin").c_str());

	

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
	bin.FileName = fileName;

	std::vector<Vertex> vertices;
	std::vector<Face> faces;
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
			if (newFace.length() >= 6 && runOnce == false) // This can't actually tell triangulated and non triangulated meshes apart.
			{
				runOnce = true;
				//std::cout << "This engine does not support mesh files with quads, please make sure the file is triangulated" << "\n";
				//std::exit(EXIT_FAILURE);
				//std::abort();
				
			}

			temp_faces.push_back(face);
			
		}
		if (prefix == "vt") 
		{
			glm::vec2 UV;
			iss >> UV.x >> UV.y;

			temp_uvs.push_back(UV);
		}

		if (prefix == "vn")
		{
			glm::vec3 NORMAL;
			iss >> NORMAL.x >> NORMAL.y >> NORMAL.z;

			temp_normals.push_back(NORMAL);
		}
		if (prefix == "mtllib") // load in the material from the file onto the mesh
		{
			
			/*char material[] = {255};
			iss >> material;
			std::cout << material , "\n";
			MeshTexture(material);*/

		}
		
	}

	//bin.ReadFile();
	//bin.WriteFile();

	

	file.close();
	

	for (int i = 0; i < temp_faces.size(); i++) 
	{
		Face face = temp_faces[i];
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
				glm::vec3 position = temp_position[index - 1]; 

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
				glm::vec3 normal = temp_normals[index - 1];
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
   				glm::vec2 uv = temp_uvs[index - 1];
				mesh.data.push_back(uv.x);
				mesh.data.push_back(uv.y);
			}
			mesh.elements.push_back(mesh.numberVertices);
			mesh.numberVertices++;
			
		}
		
	}
	
	temp_faces.clear();
	temp_normals.clear();
	temp_position.clear();
	temp_uvs.clear();
	temp_vertices.clear();
	/*WriteToBinary(fileName, &file);
	ReadFromBinary(fileName, *file);*/
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
	}
}

// $(SolutionDir)resoure

//ofstream filePath("out.bin", std::ios::binary);
//ofstream fileSize("out.bin", std::ios::binary);


//filesystem::path filePath = "C:\\Users\\zackarias.hager\\Emgine_New\\Emgine\\resource\\meshes\\cube.obj"; //
//

void MeshLoader::WriteToBinary(std::ostream& f, std::string filePath)
{
	size_t fileSize = filesystem::file_size(filePath);

	std::cerr << "Write to binary" << std::endl;
	
	
	//f.write((char*)&fileSize, sizeof(fileSize));
	//char* data;
	//data = new char[fileSize + 1];
	//name = data;
	f.write((char*)name.c_str(), fileSize);
	//fileSize = type.size();
	//f.write((char*)&fileSize, sizeof(fileSize));
	//f.write((char*)type.c_str(), fileSize);
	//BinaryFile->WriteFile(this);
	//std::cerr << name << std::endl;
	/*
	for (int i = 0; i < name.size(); ++i)
	{
		cout << bitset<8>(fileSize[&i]) << endl;
	}*/
	
}

void MeshLoader::ReadFromBinary(std::istream& f, std::string filePath)
{
	size_t fileSize = filesystem::file_size(filePath);
	char *data;
	
	std::cerr << "read from binary" << std::endl;

	//f.read((char*)&fileSize, sizeof(fileSize));// This would cause an unhandled exception.
	data = new char[fileSize + 1];
	f.read(data, fileSize);
	data[fileSize] = '\0';
	name = data;   
	delete data; 

	f.read((char*)&fileSize, sizeof(fileSize));
	data = new char[fileSize + 1];
	f.read(data, fileSize);
	data[fileSize] = '\0';
	//type = data;
	
	
	//std::cerr << data << std::endl;
	delete[] data; // memory clearing

	

	

}

void BinaryFile::hexdump(void* pointer, int buflen)
{
	File.open(FileName, std::ios::binary | std::ios::out);
	unsigned char* buf = (unsigned char*)pointer;
	int i, j;
	for (i = 0; i < buflen; i += 16) {
		printf("%06x: ", i);

		for (j = 0; j < 16; j++)
		{
			if (i + j < buflen)
				printf("%02x", buf[i + j]);
			else
				printf("  ");
		}
		printf(" ");
		for (j = 0; j < 16; j++) {
			if (i + j < buflen)
				printf("%c", isprint(buf[i + j]) ? buf[i + j] : '.');
		}

		printf("\n");
	/*	if (i >= buflen)
			return;*/
		
	}
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

void BinaryFile::WriteFile() {
	File.open(FileName, std::ios::binary | std::ios::out);
	if (!File)
	{
		std::cerr << "File error writing: " << FileName << ">\n";
		exit(1);
	}
	//obj.WriteToBinary(File, );
	File.close();
}

void BinaryFile::ReadFile() {
	File.open(FileName, std::ios::binary | std::ios::in);
	//file.open(fileName, ios::in | ios::binary);
	if (File.is_open())
	{	// get the starting position
		streampos start = File.tellg();

		// go to the end
		File.seekg(0, std::ios::end);

		// get the ending position
		streampos end = File.tellg();

		// go back to the start
		File.seekg(0, std::ios::beg);

		// create a vector to hold the data that
		// is resized to the total size of the file
		std::vector<char> contents;
		contents.resize(static_cast<size_t>(end - start));

		//read it in
		File.read(&contents[0], contents.size());

		//print it out 
		hexdump(contents.data(), contents.size());
		//return true;
	}
	if (!File)
	{
		std::cerr << "File error reading: " << FileName << ">\n";
		exit(1);
	}
	//obj.ReadFromBinary(File);
	File.close();
}
