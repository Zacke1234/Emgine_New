#include <stdio.h>
#include "imgui.h"
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Camera.h"
#include "Lighting.h"
#include "string"
#include <cstdlib>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "Object.h"
#include "UI.h"
#include "MeshManager.h"
#include "MeshLoader.h"
#include "Physics.h"
#include "Memory.h"
#include "Collider.h"
#include "Message.h"
#include "Threading.h"
#include "Observer.h"
#include <float.h>
#include <thread>
#include <mutex>
#include <Managers/ColliderManager.h>
#include <Managers/ObjectManager.h>
#include <Managers/ShaderManager.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <Managers/ObjectManager.h>
#include <Managers/TextureManager.h>
#include "../DisplayMessage.h"
#include <Managers/LightingManager.h>
#include <Managers/RigidbodyManager.h>
#include <CameraManager.h>
#include <Time/Time.h>



using namespace std;
#pragma once


GLFWwindow* window;

Lighting* myLighting;
Camera* myCamera;
MeshManager* myMeshManager;
ObjectManager* myObjectManager;
ShaderManager* myShaderManager;
ColliderManager* MyColliderManager;
TextureManager* myTextureManager;
Memory* myMemory;
MeshLoader* myMeshLoader = nullptr;
UI* myUI;
Message* myMessage;
MessageQueue* myMessageQueue;
CubeCollider* cubeColl;
CubeCollider* planeColl;
//CubeCollider* cubeColl2;
SphereCollider* sphereColl;
LightingManager* myLightingManager;
RigidbodyManager* myRigidbodyManager;
Physics* Phys;
//Threading* myThreading;
Thread* myThread; 
LightData* newLightdata;
CameraManager* myCameraManager;
Time* myTime;

int do_time()
{
	return 0;
}

int message_stuff() { // message passing between meshmanager and objectmanager
	myMessage = new Message;
	myMessageQueue = new MessageQueue;

	myThread = new Thread();
	//myThread->DoWork(myMeshManager, myMessage);
	//myMessage->setMessage("Thread started for MeshManager");
	

	myMessage->Attach(myMeshManager);
	myMessage->setMessage(myObjectManager->message = "MeshManager attached to ObjectManager (Subject)"); // Subject attaches to Observer, because the observer observes the subject

	myMessage->setMessage("Queue the message");
	myMessageQueue->Enqueue(myMessage);
	
	

	myMessage->setMessage("Detach MeshManager from Message");
	myMessage->setMessage("Dequeue the message");
	myMessage->Detach(myMeshManager);
	myMessageQueue->Dequeue(myMessage);
	
	return 0;
}



//Init Functions

int static init_window()
{
	if (!glfwInit())
	{

		std::cout << "Failed to initialize glfw" << endl;
		//myMessage->SendMessage(message, 0);
		return -1;
	}
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Emgine", NULL, NULL);


	//std::cout << "" + a << std::endl;

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//message = "Failed to initialize GLAD";
		std::cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	return 0;
}

int init_memory_tracker() {
	int megaBytes = 30;
	myMemory = new Memory();
	myMemory->HasMemoryAvailable(megaBytes, myUI);
	return 0;
}


int init_managers() {
	
	myShaderManager = new ShaderManager();
	myLightingManager = new LightingManager();
	myMeshManager = new MeshManager;
	
	myTextureManager = new TextureManager();
	MyColliderManager = new ColliderManager();
	newLightdata = new LightData();
	myLightingManager->InitDefaultLighting();
	myShaderManager->InitDefaultShader();
	//TODO: init shader, collider, and rigidbodymanager
	myObjectManager = new ObjectManager;
	myRigidbodyManager = new RigidbodyManager();
	myCameraManager = new CameraManager();
	
	return 0;
} 

int init_camera() {
	//init camera
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CENTER_CURSOR);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwSetCursorPosCallback(window, myCamera->Mouse_Callback);
	return 0;
}

int init_colliders() {
	glm::vec3 extents = { 1,1, 1 };
	glm::vec3 extentsPlane = { 1, 0.5f, 1 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };

	cubeColl = new CubeCollider(center, extents, pos);
	//cubeColl2 = new CubeCollider(center, extents, pos);
	planeColl = new CubeCollider(center, extents, pos);
	sphereColl = new SphereCollider(center, radius, pos);
	return 0;
}

int init_lightning() {
	//init shader/lighting
	glm::vec3 PointLight1;
	glm::vec3 DirectionalLight1;
	glm::vec3 SpotLight;
	//myShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	myLighting = new Lighting();
	//myLightData = new LightData();
	return 0;
}

int init_physics() {
	//init physics
	Phys = new Physics();
	

	return 0;
}


// Update Functions

int static update_camera(Camera* cam, UI* myUI, GLFWwindow* window)
{
	cam->ProcessInput(window, myTime->Deltatime);
	cam->CameraUpdate(window);
	
	cam->fieldOfView = myUI->fov;
	cam->sensitivity = myUI->sens;
	return 0;
}

//Object* selectedobj = Object::Entities[Object::SelectedEntity];
int static update_ui(UI* myUI, ShaderManager* myShader, ObjectManager* objManager)
{
	
	
	//glm::vec3 v(selectedobj->Rotation);
	

	myUI->RenderUI(myShader, objManager, myTime);
	//test = glm::scale(test, Object::Entities[Object::SelectedEntity]->Scale);
	
	if (Object::Entities.size() > 0) {
		Object::Entities[Object::SelectedEntity]->Position = glm::vec3(myUI->xPos, myUI->yPos, myUI->zPos);
		Object::Entities[Object::SelectedEntity]->Rotation = glm::vec3(
			glm::radians(myUI->xRot),
			glm::radians(myUI->yRot),
			glm::radians(myUI->zRot));
		Object::Entities[Object::SelectedEntity]->Scale = glm::vec3(myUI->xScale, myUI->yScale, myUI->zScale);
	}
	/*Object::Entities[Object::SelectedEntity]->Rotation = glm::mat4(
		glm::rotate(transform, glm::radians(myUI->yRot), glm::vec3(0, 0, 0)));*/

	//
	
	//newLightData->lightPos = SelectedLight->Position;
	return 0;
}





int main()
{
	
	myTime = new Time();
	init_window();



	init_managers();

	init_camera();


	Shader* depthShader = new Shader("../Shader/ShadowMappingVS.glsl", "../Shader/ShadowMappingFS.glsl");
	//Create Textures
	Texture* wall = myTextureManager->Create("wall", "wall.jpg");
	Texture* defaultTex = myTextureManager->Create("default", "Default 1.png");
	//myTextureManager->Create("Default", "Default 1.png");
	myCamera = myCameraManager->create("Camera");
	//Message calling
	message_stuff();




	init_colliders();

	init_lightning();

	init_physics();

	glm::vec3 size = {10,0.5f,10};
	glm::vec3 pos = { 0,-1,0 };
	glm::vec3 rotation = { 0,0,0 };
	myUI = new UI(window);
	init_memory_tracker();

	// Object Creation
	Mesh* fish = myMeshManager->Create("Fish", "fish.obj");
	Mesh* quadplane = myMeshManager->Create("quadplane", "quadplane.obj");
	Mesh* cube = myMeshManager->Create("Cube", "cube.obj");

	myObjectManager->Create( // these also push entities to Object::Entities and etc
		"Fish",
		fish,
		defaultTex,
		myShaderManager->DefaultShader,
		MyColliderManager->Create("SphereColl", sphereColl),
		myRigidbodyManager->Create(0.96f, false)
	);

	myObjectManager->Create("Cube",
		cube,
		defaultTex,
		myShaderManager->DefaultShader,
		MyColliderManager->Create("CubeColl", cubeColl),
		myRigidbodyManager->Create(0.96f, false)
	);

	myObjectManager->Create("Plane",
		cube,
		defaultTex,
		myShaderManager->DefaultShader,
		MyColliderManager->Create("PlaneColl", planeColl),
		NULL()
	);

	myObjectManager->FindAndSetProperties("Plane", pos, size, rotation);

	myObjectManager->CreateLight("SceneLight",
		NULL,
		NULL,
		myShaderManager->DefaultShader,
		NULL,
		myLightingManager->Create("SceneLight", myShaderManager->DefaultShader, myLightingManager->DefaultLighting),
		NULL);


	myObjectManager->CreateCamera("SceneCamera",
		NULL,
		NULL,
		myShaderManager->DefaultShader,
		NULL,
		myCamera,
		NULL);
	
	//myShaderManager->Create(depthShader, "../Shader/ShadowMappingVS.glsl", "../Shader/ShadowMappingFS.glsl");
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;
	unsigned int depthMapFBO;
	unsigned int depthMap;
	glGenFramebuffers(1, &depthMapFBO);
	GL_CHECK(glGenTextures(1, &depthMap));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthMap));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
	// attach depth texture as FBO's depth buffer
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
	GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0));
	GL_CHECK(glDrawBuffer(GL_NONE));
	GL_CHECK(glReadBuffer(GL_NONE));
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	
	GL_CHECK(glEnable(GL_DEPTH_TEST));
	// loops until user closes window
	while (!glfwWindowShouldClose(window))
	{
		
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		
	
		//myThread->DoWork(deltatime);
		
		// poll for and process events ?
		glfwPollEvents();

		//myMemory->LoadInMemory(myShaderManager->DefaultShader, myCamera, myLighting, myObjectManager, myUI, myMeshManager, fish, cubeColl);

		myTime->Run();

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, woodTexture);
		myShaderManager->DefaultShader->UseShader();
		
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& lightObj : LightObject::LightEntities)
		{
			myLightingManager->RunLightData(myShaderManager->DefaultShader, lightObj->myLightData, myCamera);
			
		}
		
		

		//Drawcall objects
		for (auto& o : Object::Entities)
		{
			o->Draw(myCamera, myShaderManager->DefaultShader);

		}
		depthShader->UseShader();
		for (auto& lightObj : LightObject::LightEntities)
		{
			myLightingManager->UseShadowDepth(depthShader, lightObj->myLightData);
		}
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);*/

		Phys->Simulate(myTime->Deltatime, myTime);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		// render UI (after/ON TOP OF drawcall)
		update_ui(myUI, myShaderManager, myObjectManager);

		//update camera
		update_camera(myCamera, myUI, window);
		

		// swaps front and back buffers
		glfwSwapBuffers(window);

		
		//glClearColor(0.7, 0.31, 0.9, 1);
	}
	  
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//myMemory->ClearMemory(myShaderManager->DefaultShader, myCamera, myLighting, myObjectManager, myUI, myMeshManager, MeshMesh, cubeColl);
	//delete myMemory;
	glfwTerminate();
	//std::cout << "hello engime" << std::endl;
	
	/*delete myShader;*/
	return 0;
}







