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

bool Memory::HasMemoryAvailable(int megaBytes, UI* thisUI)
{

	//GetProcessMemoryInfo(megaBytes, );
	
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	
	//std::cout << status.ullTotalPhys + " megabytes \n" << endl;
	//std::cout << "There are %*ld percent of memory in use.\n", status.dwMemoryLoad;
	
	if (status.dwMemoryLoad > megaBytes) // * 1048
	{
		_tprintf(TEXT("There is  %*ld MB of physical memory available.\n"), WIDTH, status.ullAvailPhys / (1024 * 1024));
		_tprintf(TEXT("There is  %*ld MB of virtual memory available.\n"), WIDTH, status.ullAvailVirtual / (1024 * 1024));
		thisUI->errorMessage = "Loaded memory is too high, There is MB memory in use.\n ";
		thisUI->errorTriggered = true;
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

