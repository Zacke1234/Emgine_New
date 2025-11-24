#include "Memory.h"
//#include <Psapi.h>
#include <Windows.h>
#include <crtdbg.h>
#include <iostream>
#include <tchar.h>

#define _CRTDBG_MAP_ALLOC
#define WIDTH 7

Memory::Memory()
{

}

bool Memory::HasMemoryAvailable(int megaBytes, GLFWwindow* window)
{

	//GetProcessMemoryInfo(megaBytes, );
	
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	//std::cout << status.ullTotalPhys + " megabytes \n" << endl;
	//std::cout << "There are %*ld percent of memory in use.\n", status.dwMemoryLoad;
	_tprintf(TEXT("There is  %*ld percent of memory in use.\n"), WIDTH, status.dwMemoryLoad);

	if (status.dwMemoryLoad > megaBytes) // * 1048
	{
		std::cout << "Loaded memory is too high" << std::endl;
		myUI->ErrorDialog("Too much memory in use", window);
		//return false;
	}

	return status.ullTotalPhys;
}

std::thread Memory::T1()
{
	return std::thread();
}

void Memory::ClearMemory(Shader* CmyShader, Camera* CmyCamera, Lighting* CmyLighting, ObjectManager* ObjManager, UI* CmyUI, MeshManager* CmyMeshManager, Mesh* CObjLoader, Collider* CmyCollider)
{
	myShader = CmyShader;
	delete CmyShader;
	/*myCube = CmyCube;
	delete CmyCube;*/
	myCamera = CmyCamera;
	delete CmyCamera;
	myLighting = CmyLighting;
	delete CmyLighting;
	OBJManager = ObjManager;
	delete ObjManager;
	myUI = CmyUI;
	delete CmyUI;
	myMeshManager = CmyMeshManager;
	delete CmyMeshManager;
	myMesh = CObjLoader;
	delete CObjLoader;
	//myPhysics = CmyPhysics;
	//delete CmyPhysics;
	myCollider = CmyCollider;
	delete CmyCollider;
	
}

void Memory::LoadInMemory(Shader* myShader, Camera* myCamera, Lighting* myLighting, ObjectManager* virtObj, UI* myUI, MeshManager* myMeshManager, Mesh* ObjLoader, Collider* myCollider)
{
	
}

