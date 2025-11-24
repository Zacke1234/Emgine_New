#include "MeshManager.h"
#include <cassert>



#pragma once

MeshManager::MeshManager()
{
	meshLoader = new MeshLoader();
	//std::cout << "Client triggers operation 1 (meshManager)" << "\n";
}

MeshManager::~MeshManager()
{ 
	for (auto& [key, value] : MeshCache)
	{
		delete value;
	}
	delete meshLoader;
}




Mesh* MeshManager::LoadMesh(std::string fromPath, std::string name)
{
	size_t fileSize = std::filesystem::file_size(fromPath);
	std::string Binary = "resource\\bins\\" + name + ".bin";

	//char* data = new char;
	//
	std::ofstream write("resource\\bins\\" + name + ".bin", std::ios::binary); // ./out.bin
	std::fstream read(fromPath);
	std::fstream readBin("resource\\bins\\" + name + ".bin");
	
	//meshLoader->DoMeshloadingStages(this, fromPath, "", read, write, readBin, Binary);
	meshLoader->WriteToBinary(read, write, fromPath);
	meshLoader->ParseBinary(Binary, readBin, write);
	//meshLoader->ReadFile(fromPath, Binary, write, read);
	
	/*BinaryFile bin((fromPath).c_str());
	bin.ReadFile(fromPath, Binary, write, read);*/
	//bin.WriteFile();
	
	
	

	Mesh* mesh = new Mesh;
	mesh->name = name;
	meshLoader->ObjParser(fromPath, mesh);
	//if (!meshLoader->ObjParser("C:\\Users\\zackarias.hager\\Emgine_New\\Emgine\\resource\\bins\\" + name + ".bin", mesh)) // herein lies the problem....
	//{
	//	std::cout << "Something is wrong with" << name << " from path: " << fromPath + name << "\n";
	//	//mesh = new Mesh();
	//	
	//	//return nullptr;
	//}

	msg = "Mesh loaded in";
	//message->SendMessage(msg, 0);
	mesh->InitialiseMesh();
	//MeshCache.emplace(fromPath, mesh);

	return mesh;
}	

Mesh* MeshManager::Create(std::string name, std::string path_end)
{
	std::string path = "resource\\meshes\\";
	Mesh* mesh = new Mesh();
	mesh->name = name;
	mesh = LoadMesh((path + path_end).c_str(), name);
	std::cout << "Mesh loaded in: " << name << " from path: " << path + path_end << "\n";
	MeshCache.emplace(name, mesh);
	std::cout << "Mesh created: " << name << " from path: " << path + path_end << "\n";
	
	
	return mesh;
}

