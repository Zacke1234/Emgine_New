
#include "main.h"

using namespace std;

#pragma once




unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;


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
	myShaderManager->InitDefaultShader();
	myShaderManager->Create("depthShader", "../Shader/DepthQuadVS.glsl", "../Shader/DepthQuadFS.glsl");
	myShaderManager->Create("DirectionalShader", "../Shader/DirectionalVS.glsl", "../Shader/DirectionalFS.glsl");
	//myShaderManager->Create("PointShader", "../Shader/PointVS.glsl", "../Shader/PointFS.glsl", "../Shader/PointGS.glsl");
	
	
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
	glm::vec3 extentsPlane = { 100, 0.5f,100 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };

	cubeColl = new CubeCollider(scale, pos);
	planeColl = new CubeCollider(extentsPlane, pos);
	planeColl->isKinematic = true;
	PlaneCollider = MyColliderManager->Create("PlaneColl", PlaneCollider, true);
	sphereColl = new SphereCollider(radius, pos);
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
	cam->ProcessInput(myTime->Deltatime);
	//cam->CameraUpdate();
	
	cam->fieldOfView = myUI->fov;
	cam->sensitivity = myUI->sens;

	return 0;
}

bool UIRunOnce = false;

int static update_ui(UI* myUI, ShaderManager* myShader, ObjectManager* objManager)
{
	myUI->RenderUI(myShader, objManager, myTime);
	
	if (!UIRunOnce)
	{
		if (Object::Entities.size() > 0)
		{
			myUI->xPos = Object::Entities[Object::SelectedEntity]->Position.x;
			myUI->yPos = Object::Entities[Object::SelectedEntity]->Position.y;
			myUI->zPos = Object::Entities[Object::SelectedEntity]->Position.z;

			myUI->xRot = Object::Entities[Object::SelectedEntity]->Rotation.x;
			myUI->yRot = Object::Entities[Object::SelectedEntity]->Rotation.y;
			myUI->zRot = Object::Entities[Object::SelectedEntity]->Rotation.z;

			myUI->xScale = Object::Entities[Object::SelectedEntity]->Scale.x;
			myUI->yScale = Object::Entities[Object::SelectedEntity]->Scale.y;
			myUI->zScale = Object::Entities[Object::SelectedEntity]->Scale.z;

		}
		UIRunOnce = true;
	}

	if (Object::Entities.size() > 0) { // rework this
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
	
	myCamera = myCameraManager->Create("SceneCamera", window);
	
	message_calling();

	init_colliders();

	init_lightning();

	init_physics();

	myUI = new UI(window);
	init_memory_tracker();

	// Object Creation
	Mesh* fish = myMeshManager->Create("Fish", "fish.obj");
	//Mesh* quadplane = myMeshManager->Create("quadplane", "quadplane.obj");
	Mesh* cube = myMeshManager->Create("Cube", "cube.obj");

	/*Mesh* vikinghouse = myMeshManager->Create("Viking_House", "Viking_House.obj");

	Mesh* backpack = myMeshManager->Create("backpack", "backpack.obj");*/

	
	

	// whatever is first in the list (being selected) can't be changed by the find and set properties function when initialising
	myObjectManager->Create("Plane",
		cube,
		defaultTex,
		planeColl,
		NULL()
	);


	myObjectManager->FindAndSetProperties("Plane", glm::vec3(0.0f), glm::vec3( 100.0f ,0.5f,100.0f ), glm::vec3(0.0f));

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

	myShaderManager->DefaultShader->UseShader();
	myShaderManager->DefaultShader->SetInt("shadowMap", 1);
	
	directionalShader->UseShader();

	directionalShader->SetInt("depthMap", 1);
	directionalShader->SetInt("depthCubeMap", 1);

	myShaderManager->DefaultShader->SetInt("depthMap", 1);
	myShaderManager->DefaultShader->SetInt("depthCubeMap", 1);

	LightObject* lightobject = LightObject::LightEntities[0];

	bool OnceCheck = false;
	
	myGameplay->Initialise(window, myObjectManager, myMeshManager, myTextureManager, MyColliderManager, myRigidbodyManager, myCameraManager, myTime, myShaderManager, Phys);

	// loops until user closes window
	while (!glfwWindowShouldClose(window))
	{
		
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		
		if (!OnceCheck)
		{
			myGameplay->Start();
			OnceCheck = true;
		}
		

		myTime->Run();

		//update camera
		for (auto& gameCameraEntity : Camera::cameras)
		{
			gameCameraEntity->CameraUpdate();
		}

		if (myTime->IsPaused == true)
		{
			update_camera(myCamera, myUI, window);
		}
		
		
		

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

		if (myTime->IsPaused == true)
		{
			myCamera->CameraSendToShader(myShaderManager->DefaultShader);
		}
		else 
		{
			for (auto& gameCameraEntity : Camera::cameras)
			{
				if (gameCameraEntity->name != "SceneCamera")
				{
					gameCameraEntity->CameraSendToShader(myShaderManager->DefaultShader);
				}
				
			}
		}
		

		
		myLightingManager->RunLightData(myShaderManager->DefaultShader);
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


		if (myTime->IsPaused == false)
		{
			myGameplay->Run();
			//Object::SelectedEntity = -1;
		}
		
		

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







