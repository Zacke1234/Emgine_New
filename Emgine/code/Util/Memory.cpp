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

bool Memory::HasMemoryAvailable(int megaBytesLimit, UI* thisUI)
{

	//GetProcessMemoryInfo(megaBytes, );
	
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	int memoryLoaded = status.dwMemoryLoad;
	int physicalLoaded = status.ullTotalPhys / (1024 * 1024);
	int virtualLoaded = status.ullTotalVirtual / (1024 * 1024);
	//std::cout << status.ullTotalPhys + " megabytes \n" << endl;
	//std::cout << "There are %*ld percent of memory in use.\n", status.dwMemoryLoad;
	_tprintf(TEXT("There is  %*ld MB of physical memory available.\n"), WIDTH, status.ullAvailPhys / (1024 * 1024));

	_tprintf(TEXT("There is  %*ld MB of memory loaded.\n"), WIDTH, physicalLoaded);
	if (physicalLoaded < memoryLoaded) // * 1048
	{
		
		//std::sprintf(thisUI->errorMessage, "%d", memoryLoaded);
		thisUI->errorMessage = "Loaded memory is too high, MB memory in use: " , static_cast<char>(physicalLoaded);
	
		thisUI->errorTriggered = true;
		//return false;
	}
	_tprintf(TEXT("There is  %*ld MB of virtual memory available.\n"), WIDTH, status.ullAvailVirtual / (1024 * 1024));
	_tprintf(TEXT("There is  %*ld MB of memory loaded.\n"), WIDTH, virtualLoaded);
	if (virtualLoaded < memoryLoaded) // * 1048
	{
		
		//std::sprintf(thisUI->errorMessage, "%d", memoryLoaded);
		thisUI->errorMessage = "Loaded memory is too high, MB memory in use: ", static_cast<char>(virtualLoaded);
		thisUI->errorTriggered = true;
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

