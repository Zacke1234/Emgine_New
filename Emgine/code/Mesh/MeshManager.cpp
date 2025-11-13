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
	

	
	
	std::ofstream write("C:\\Users\\zackarias.hager\\Emgine_New\\Emgine\\resource\\bins\\" + name + ".bin", std::ios::binary); // ./out.bin
	std::ifstream read(fromPath);
	
	meshLoader->ReadFromBinary(read, fromPath);
	meshLoader->WriteToBinary(write, fromPath);
	
	
	
	
	write.close();
	read.close();

	Mesh* mesh = new Mesh;
	mesh->name = name;
	meshLoader->ObjParser("C:\\Users\\zackarias.hager\\Emgine_New\\Emgine\\resource\\bins\\" + name + ".bin", mesh);
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
	std::string path = "C:\\Users\\zackarias.hager\\Emgine_New\\Emgine\\resource\\meshes\\";
	Mesh* mesh = new Mesh();
	mesh->name = name;
	mesh = LoadMesh((path + path_end).c_str(), name);
	std::cout << "Mesh loaded in: " << name << " from path: " << path + path_end << "\n";
	MeshCache.emplace(name, mesh);
	std::cout << "Mesh created: " << name << " from path: " << path + path_end << "\n";
	
	
	return mesh;
}

