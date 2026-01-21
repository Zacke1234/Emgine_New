#include "MeshManager.h"
#include <cassert>



#pragma once

std::vector<Mesh> MeshManager::MeshCache;
std::vector<std::string> MeshManager::MeshList;
MeshManager::MeshManager()
{
	meshLoader = new MeshLoader();
	//std::cout << "Client triggers operation 1 (meshManager)" << "\n";
}

MeshManager::~MeshManager()
{ 
	//for (auto& [key, value] : MeshCache)
	//{
	//	delete value;
	//}
	//delete meshLoader;
}




Mesh* MeshManager::LoadMesh(std::string objPath, std::string name, Mesh* mesh)
{
	size_t fileSize = std::filesystem::file_size(objPath);
	std::string BinaryPath = "resource\\bins\\" + name + ".bin";
	//Mesh* mesh = new Mesh;
	mesh->name = name;
	
	std::ofstream writeBin(BinaryPath, std::ios_base::binary); 
	std::ifstream readObj(objPath);
	std::ifstream readBin(BinaryPath, std::ios::binary);
	//



	meshLoader->ReadObjToBinary(objPath, readObj, mesh);
	if (meshLoader->WriteObjToBinary(writeBin, objPath, mesh))
	{
		
		meshLoader->BinParser(BinaryPath, mesh);
	}
	else
	{

		meshLoader->ObjParser(objPath, mesh);
		mesh->InitialiseMesh();

	}

	
	
	//check if binary path has file:
		//if file exists
			// parse binary->mesh
		//else
			// parse obj to binary
			// then binary ->mesh
		// then load mesh(instantiate) into meshmanager n stuff 
	std::cout << "Mesh loaded in: " << name << " from path: " << objPath + name << "\n";
	return mesh;
}
Mesh* MeshManager::LoadFromMeshCache(std::string fromPath, std::string name, Mesh* mesh)
{
	std::ifstream readObj(fromPath);
	std::string BinaryPath = "resource\\bins\\" + name + ".bin";
	for (auto& meshes : MeshCache)
	{
		if (meshes.name == name)
		{
			mesh->data = meshes.data;
			mesh->elements = meshes.elements;
			mesh->normals = meshes.normals;
			mesh->uvs = meshes.uvs;
			mesh->faces = meshes.faces;
			mesh->position = meshes.position;
			break;
			
		}
		
	}
	meshLoader->BinParser(BinaryPath, mesh);
	
	return mesh;
}


Mesh* MeshManager::Create(std::string name, std::string path_end)
{
	std::string path = "resource\\meshes\\";
	Mesh* mesh = new Mesh();
	std::string BinaryPath = "resource\\bins\\" + name + ".bin";
	mesh->name = name;
	std::cout << "Mesh created: " << name << " from path: " << path + path_end << "\n";
	
	
	// copy over the mesh from the mesh cache over to this mesh without any of the obj parsing

	if (std::find(MeshList.begin(), MeshList.end(), name) != MeshList.end())
	{
		
		LoadFromMeshCache((path + path_end).c_str(), name, mesh);
		std::cout << "has mesh: " + name << std::endl;
	}
	else
	{
		MeshList.push_back(name);
		
		mesh = LoadMesh((path + path_end).c_str(), name, mesh);
		MeshCache.push_back(*mesh);
		std::cout << "does not have mesh: " + name << std::endl;

		
	}
	return mesh;
}

