
#include "imgui.h"
#include <iostream>
#include "gl.h"
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
#include <thread>
#include <mutex>
#include <ColliderManager.h>
#include <ShaderManager.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <ObjectManager.h>
#include <TextureManager.h>
#include <LightingManager.h>
#include <RigidbodyManager.h>
#include <CameraManager.h>
#include <CustomGame/MainGameplay.h>
#include <Time/Time.h>
#include <glfw3.h>




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
SphereCollider* sphereColl;
LightingManager* myLightingManager;
RigidbodyManager* myRigidbodyManager;
Physics* Phys;
CameraManager* myCameraManager;
Time* myTime;
MainGameplay* myGameplay;

unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;

int do_time()
{
	return 0;
}

int message_calling() { // message passing between meshmanager and objectmanager
	myMessage = new Message;
	myMessageQueue = new MessageQueue;
	
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
		
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Emgine", NULL, NULL);


	//std::cout << "" + a << std::endl;

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
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
	GL_CHECK(glEnable(GL_DEPTH_TEST));
	myShaderManager = new ShaderManager();
	myLightingManager = new LightingManager();
	myMeshManager = new MeshManager;
	//myCubeMap = new Cubemap;
	
	myTextureManager = new TextureManager();
	MyColliderManager = new ColliderManager();
	
	
	//myModel = new Model();
	myLightingManager->InitDefaultLighting();
	myShaderManager->Create("depthShader", "../Shader/DepthQuadVS.glsl", "../Shader/DepthQuadFS.glsl");
	myShaderManager->Create("DirectionalShader", "../Shader/DirectionalVS.glsl", "../Shader/DirectionalFS.glsl");
	//myShaderManager->Create("PointShader", "../Shader/PointVS.glsl", "../Shader/PointFS.glsl", "../Shader/PointGS.glsl");
	myShaderManager->InitDefaultShader();
	
	myObjectManager = new ObjectManager;
	myRigidbodyManager = new RigidbodyManager();
	myCameraManager = new CameraManager();
	myGameplay = new MainGameplay();
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
	glm::vec3 extentsPlane = { 100, 0.5f,100 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };

	cubeColl = new CubeCollider(center, extents, pos);
	planeColl = new CubeCollider(center, extentsPlane, pos);
	sphereColl = new SphereCollider(center, radius, pos);
	return 0;
}

int init_lightning() {
	//init shader/lighting
	
	myLighting = new Lighting();
	
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


int static update_ui(UI* myUI, ShaderManager* myShader, ObjectManager* objManager)
{
	myUI->RenderUI(myShader, objManager, myTime);
	
	if (Object::Entities.size() > 0) {
		Object::Entities[Object::SelectedEntity]->Position = glm::vec3(myUI->xPos, myUI->yPos, myUI->zPos); // vector subscript out of range. Meaning something is wrong with how the selected entity is done. (FIXED)
		Object::Entities[Object::SelectedEntity]->Rotation = glm::vec3(
			glm::radians(myUI->xRot),
			glm::radians(myUI->yRot),
			glm::radians(myUI->zRot));
		Object::Entities[Object::SelectedEntity]->Scale = glm::vec3(myUI->xScale, myUI->yScale, myUI->zScale);
	}
	
	return 0;
}





int main()
{
	
	myTime = new Time();
	init_window();

	init_managers();

	init_camera();

	Texture* wall = myTextureManager->Create("wall", "wall.jpg");
	Texture* defaultTex = myTextureManager->Create("default", "Default 1.png");
	
	myCamera = myCameraManager->Create("Camera");
	
	message_calling();

	init_colliders();

	init_lightning();

	init_physics();

	glm::vec3 size = {100,0.5f,100};
	glm::vec3 pos = { 0, -3, 0 };
	glm::vec3 pos2 = { 0,1,1 };
	glm::vec3 rotation = { 0,0,0 };
	myUI = new UI(window);
	init_memory_tracker();

	// Object Creation
	Mesh* fish = myMeshManager->Create("Fish", "fish.obj");
	Mesh* quadplane = myMeshManager->Create("quadplane", "quadplane.obj");
	Mesh* cube = myMeshManager->Create("Cube", "cube.obj");

	/*Mesh* vikinghouse = myMeshManager->Create("Viking_House", "Viking_House.obj");

	Mesh* backpack = myMeshManager->Create("backpack", "backpack.obj");*/

	myShaderManager->DefaultShader->UseShader();
	
	myObjectManager->Create( // these also push entities to Object::Entities and etc
		"Fish",
		fish,
		defaultTex,
		MyColliderManager->Create("SphereColl", sphereColl),
		myRigidbodyManager->Create(0.96f, false)
	);


	//myObjectManager->Create( // these also push entities to Object::Entities and etc
	//	"backpack",
	//	backpack,
	//	defaultTex,
	//	myShaderManager->DefaultShader,
	//	MyColliderManager->Create("SphereColl", sphereColl),
	//	myRigidbodyManager->Create(0.96f, false)
	//);

	myObjectManager->Create("Cube",
		cube,
		wall,
		MyColliderManager->Create("CubeColl", cubeColl),
		myRigidbodyManager->Create(0.96f, false)
	);

	myObjectManager->FindAndSetProperties("Cube", glm::vec3(2,1,3), glm::vec3(1,1,1), rotation);

	

	//planeColl->isKinematic = true;

	myObjectManager->Create("Plane",
		cube,
		defaultTex,
		MyColliderManager->Create("PlaneColl", planeColl),
		NULL()
	);

	myObjectManager->FindAndSetProperties("Plane", pos, size, rotation);

	myObjectManager->CreateLight("SceneLight", 
		NULL,
		NULL,
		NULL,
		myLightingManager->Create("SceneLight", myShaderManager->DefaultShader, myLightingManager->DefaultLighting),
		NULL);

	myObjectManager->FindAndSetProperties("SceneLight", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f));

	myObjectManager->CreateCamera("SceneCamera",
		NULL,
		NULL,
		NULL,
		myCamera,
		NULL);

	Shader* depthShader = myShaderManager->Find("depthShader");
	Shader* directionalShader = myShaderManager->Find("DirectionalShader");
	//Shader* pointShader = myShaderManager->Find("PointShader");

	myLightingManager->InitDepthMapping();
	
	myShaderManager->DefaultShader->SetInt("shadowMap", 1);
	
	directionalShader->UseShader();

	directionalShader->SetInt("depthMap", 1);
	directionalShader->SetInt("depthCubeMap", 1);

	myShaderManager->DefaultShader->SetInt("depthMap", 1);
	myShaderManager->DefaultShader->SetInt("depthCubeMap", 1);

	LightObject* lightobject = LightObject::LightEntities[0];

	myGameplay->Start(window);

	// loops until user closes window
	while (!glfwWindowShouldClose(window))
	{
		
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		
		myTime->Run();

		//update camera
		update_camera(myCamera, myUI, window);
		

		

		// shadow pass 
		directionalShader->UseShader();
		

		// View port 
		myLightingManager->Viewport();
		// Bind shadow frameBuffer 
		myLightingManager->BindFrameBuffer();		
		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		// bind frame buffer texture to the depth cube map
		//myLightingManager->FrameBufferTexture();
		myLightingManager->ActiveTextureDepth();

		// Clear depth
		
		// Configure shader and lightspacematrix
		myLightingManager->UseShadowDepth(directionalShader, lightobject->myLightData);
		// Render scene

		glCullFace(GL_FRONT);
		for (auto& o : Object::Entities)
		{
			o->Draw(directionalShader); // Draws and binds the texture and sends the transform to the shader
		}
		//myModel->Draw(*directionalShader);
		glCullFace(GL_BACK);
		// Bind default frameBuffer
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		// View port
		GL_CHECK(glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT));
		// Clear Depth
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		//myLightingManager->BindCubeMapTexture();

		myShaderManager->DefaultShader->UseShader();

		myLightingManager->RunMainFragmentShadows(myShaderManager->DefaultShader, lightobject->myLightData);
		myShaderManager->DefaultShader->SetInt("shadowMap", 1);
		myCamera->CameraSendToShader(myShaderManager->DefaultShader);

		
		myLightingManager->RunLightData(myShaderManager->DefaultShader, myCamera);
		myLightingManager->ActiveTextureDepth();

		//Drawcall objects
		for (auto& o : Object::Entities)
		{
			o->Draw(myShaderManager->DefaultShader);

		}

		//myModel->Draw(*myShaderManager->DefaultShader);

		depthShader->UseShader();
		depthShader->SetInt("depthMap", 0);
		myLightingManager->UseShadowDepth(depthShader, lightobject->myLightData);

		Phys->Simulate(myTime->Deltatime, myTime);
		
		// render UI (after/ON TOP OF drawcall)
		update_ui(myUI, myShaderManager, myObjectManager);

		myGameplay->Run();
		

		// swaps front and back buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		//glClearColor(0.7, 0.31, 0.9, 1);
	}
	  
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	glfwTerminate();
	
	return 0;
}







