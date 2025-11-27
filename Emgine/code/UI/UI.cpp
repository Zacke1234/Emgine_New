#include "UI.h"
#include "Object.h"
#include "vector"
#include "imgui.h"
#include "Shader.h"
#include "Texture.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <iostream>

#pragma once

CubeCollider* cubeColl2;
//Lighting* light;
MeshManager* meshmang;
ShaderManager* shaderMang;
ColliderManager* colliderMang;
TextureManager* textureMang;
LightingManager* lightMang;
LightData* newLightData;
RigidbodyManager* myRigidbodyMang;


//Lighting* myLighting;
bool SelectedLight;
bool selectedMaterial;
bool selectedCamera;

int boolHandler()
{
	
	if (Object::Entities[Object::SelectedEntity]->myTexture != nullptr)
	{
		selectedMaterial = true;
	}
	else
	{
		selectedMaterial = false;
	}
	if (Object::Entities[Object::SelectedEntity]->ObjType == 1)
	{
		SelectedLight = true;
	}
	else
	{
		SelectedLight = false;
	}
	if (Object::Entities[Object::SelectedEntity]->ObjType == 4)
	{
		selectedCamera = true;
	}
	else
	{
		selectedCamera = false;
	}
	
	return 0;
}

int uiCameratList(UI* myUI, ObjectManager* objectmanager)
{
	
	if (Object::Entities.size() > 0) {
		
		if (selectedCamera)
		{
			Object::Entities[Object::SelectedEntity]->myCamera->myPosition = Object::Entities[Object::SelectedEntity]->Position;
			//Object::Entities[Object::SelectedEntity]->myCamera->myView = Object::Entities[Object::SelectedEntity]->Rotation;
		}
	}
	return 0;
}

int uiLightList(UI* myUI, ObjectManager* objectmanager)
{
	if (Object::Entities.size() > 0) {
		

		if (SelectedLight)
		{

			Object::Entities[Object::SelectedEntity]->myLightData->lightPos = Object::Entities[Object::SelectedEntity]->Position;
			Object::Entities[Object::SelectedEntity]->myLightData->lightDir = glm::vec3(
				glm::radians(myUI->xRot),
				glm::radians(myUI->yRot),
				glm::radians(myUI->zRot));
			Object::Entities[Object::SelectedEntity]->myLightData->constant = myUI->lightConstant;
			Object::Entities[Object::SelectedEntity]->myLightData->cutOff = myUI->cutoff;
			Object::Entities[Object::SelectedEntity]->myLightData->outerCutOff = myUI->outerCutOff;
			Object::Entities[Object::SelectedEntity]->myLightData->ambient = myUI->lightAmbient;
			Object::Entities[Object::SelectedEntity]->myLightData->diffuse = myUI->lightDiffuse;
			Object::Entities[Object::SelectedEntity]->myLightData->linear = myUI->lightLinear;
			Object::Entities[Object::SelectedEntity]->myLightData->quadtric = myUI->lightQuadratic;
			Object::Entities[Object::SelectedEntity]->myLightData->specular = myUI->lightspecular;
			
		}
	}
	
	
	return 0;
}

int uiMaterialList(UI* myUI)
{
	
	
	if (Object::Entities.size() > 0 && selectedMaterial) {
		
		Object::Entities[Object::SelectedEntity]->myTexture->myMaterial->diffuse = myUI->matDiffuse;
				Object::Entities[Object::SelectedEntity]->myTexture->myMaterial->specular = myUI->matSpecular;
				Object::Entities[Object::SelectedEntity]->myTexture->myMaterial->shininess = myUI->matShininess;
				Object::Entities[Object::SelectedEntity]->myTexture->myMaterial->color = myUI->matColor;
	}
	
	
	

	return 0;
}

int uiObjectList(UI* ui) 
{
	
	for (int i = 0; i < Object::Entities.size(); i++)
	{
		ImGui::PushID(i);
		if (ImGui::Button(Object::Entities[i]->namn.c_str()))
		{
			
			Object::SelectedEntity = i;
			
			ui->xPos = Object::Entities[i]->Position[0];
			ui->yPos = Object::Entities[i]->Position[1]; 
			ui->zPos = Object::Entities[i]->Position[2];

			ui->xRot = glm::degrees(Object::Entities[i]->Rotation[0]);
			ui->yRot = glm::degrees(Object::Entities[i]->Rotation[1]);
			ui->zRot = glm::degrees(Object::Entities[i]->Rotation[2]);

			ui->xScale = Object::Entities[i]->Scale[0];
			ui->yScale = Object::Entities[i]->Scale[1];
			ui->zScale = Object::Entities[i]->Scale[2];

			if (Object::Entities[Object::SelectedEntity]->myTexture != nullptr)
			{
				ui->matColor = Object::Entities[i]->myTexture->myMaterial->color;
				ui->matShininess = Object::Entities[i]->myTexture->myMaterial->shininess;
				ui->matSpecular = Object::Entities[i]->myTexture->myMaterial->specular;
				ui->matDiffuse = Object::Entities[i]->myTexture->myMaterial->diffuse;
				


				//myUI->matColor = Object::Entities[Object::SelectedEntity]->myTexture->myMaterial->color;
			}

			if (Object::Entities[Object::SelectedEntity]->ObjType == 1)
			{
				ui->lightAmbient = Object::Entities[i]->myLightData->ambient;
				ui->lightDiffuse = Object::Entities[i]->myLightData->diffuse;
				ui->lightspecular = Object::Entities[i]->myLightData->specular;

				ui->lightLinear = Object::Entities[i]->myLightData->linear;
				ui->lightQuadratic = Object::Entities[i]->myLightData->quadtric;
				ui->lightConstant = Object::Entities[i]->myLightData->constant;
				ui->cutoff = Object::Entities[i]->myLightData->cutOff;
				ui->outerCutOff = Object::Entities[i]->myLightData->outerCutOff;
				
			}

			if (Object::Entities[Object::SelectedEntity]->ObjType == 4)
			{
				
				ui->xPos = Object::Entities[i]->myCamera->myPosition.x;
				ui->yPos = Object::Entities[i]->myCamera->myPosition.y;
				ui->zPos = Object::Entities[i]->myCamera->myPosition.z;
			}
			
			
		}
		//Object::Entities[0] = o;
		ImGui::PopID();
	}
	return 0;
}


int classes() {
	glm::vec3 extents = { 1,1, 1 };
	glm::vec3 extentsPlane = { 7 / 2, 0.5f / 2, 7 / 2 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };
	
	cubeColl2 = new CubeCollider(center, extents, pos);
	//newLightData = new LightData();
	shaderMang = new ShaderManager();
	colliderMang = new ColliderManager();
	textureMang = new TextureManager();
	meshmang = new MeshManager();
	lightMang = new LightingManager();
	myRigidbodyMang = new RigidbodyManager();
	
	
	return 0;
}

UI::UI(GLFWwindow* window) // unitilized
{
	
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	/*io.ConfigFlags |= ImGuiViewportFlags_None;
	io.ConfigFlags |= ImGuiConfigFlags_None;
	
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}*/
	
	//camera = new Camera();
	ImGui::StyleColorsDark();
	//ImGui_ImplGlfw_InitForOpenGL(window, true); // changing this to false makes the hover over highlight effect work on the button, but I still
	// can't interact with it, nvm fixed all of this now
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	
	
	classes();
}

void UI::RenderUI(ShaderManager* shader, ObjectManager* objectmanager)
{

	
	
	
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::NewFrame();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::Begin("Emgine Properties");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	//ImGui::ShowDemoWindow();
	ImGui::Text("");
	
	boolHandler();

	if (ImGui::Button("echo"))
	{
		std::cout << "echo" << "\n";
		//std::cout << textureFile << "\n";
		/*for (int i = 0; i < Object::Entities.size(); i++)
		{
			std::cout << Object::Entities[i] << " ";
		}*/
	}
	ImGui::Text("Type in the exact file name");

	textureFile = ImGui::InputText("texture file", textureBuffer, sizeof(textureBuffer) - 1);  // does not work as intended
	name = ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer) - 1);
	charMesh = ImGui::InputText("Mesh", meshBuffer, sizeof(meshBuffer) - 1); 

	ImGui::InputFloat("Field of view", &fov, 1.0f, 1.0f, "%.2f");

	ImGui::InputFloat("Camera sensitivity", &sens, 0.1f, 1.0f, "%.2f");

	std::string tex = "_tex";
	//ImGui::Text("Change camera speed");
	//ImGui::InputFloat("Camera speed", &speed, 1.0f, 1.0f, "%.1f"); // supposed to change speed of camera cause
	
	if (errorTriggered) {

		ImGui::OpenPopup("errorMessage");
		if (ImGui::BeginPopup("errorMessage"))
		{
			ImGui::Text(errorMessage);
		}
		if (ImGui::Button("Ok"))
		{
			errorTriggered = false;	
		}
		ImGui::EndPopup();
	}
	

	if (ImGui::Button("Create new mesh"))
	{
		if (nameBuffer[0] == '\0' && nameBuffer != NULL && meshBuffer[0] != '\0')
		{
			objectmanager->Create(
				"Mesh", // Name
				meshmang->Create("Mesh", meshBuffer),
				textureMang->Create(std::string(nameBuffer + tex), "Default 1.png", material),
				shader->DefaultShader,
				colliderMang->Create("CubeColl", cubeColl2),
				myRigidbodyMang->Create(0.0f)
			);
		}
		if (meshBuffer[0] == '\0' && meshBuffer != NULL)
		{
			objectmanager->Create(
				"Mesh", // Name
				meshmang->Create("fish", "fish.obj"),
				textureMang->Create(std::string(nameBuffer + tex), "Default 1.png", material),
				shader->DefaultShader,
				colliderMang->Create("CubeColl", cubeColl2),
				myRigidbodyMang->Create(0.0f)
			);
		}
	}
	//std::string test = nameBuffer;
	if (ImGui::Button("Create new cube"))
	{
		if (nameBuffer[0] == '\0' && nameBuffer != NULL) // && textureBuffer[0] != '\0'
		{
			std::cout << "name field is empty" << std::endl;
			
			objectmanager->Create("Cube",
				meshmang->Create("Cube", "cube.obj"),
				textureMang->Create(std::string("Cube" + tex), "Default 1.png", material),
				shader->DefaultShader,
				colliderMang->Create("CubeColl", cubeColl2),
				myRigidbodyMang->Create(0.0f)
			);
		}
		else
		{
			objectmanager->Create(nameBuffer,
				meshmang->Create(nameBuffer, "cube.obj"),
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer, material),
				shader->DefaultShader,
				colliderMang->Create("CubeColl", cubeColl2),
				myRigidbodyMang->Create(0.0f)
			);
		}
		




		

	}
	uiCameratList(this, objectmanager);
	uiMaterialList(this);
	if(Object::Entities.size() > 0)
	{
		ImGui::Text("Material properties");
		
		ImGui::DragInt("Diffuse", &matDiffuse,step, 0, 1);
		ImGui::DragInt("Specular", &matSpecular, step, 0, 100);
		ImGui::DragInt("Shininess", &matShininess, step, 0, 100);
		ImGui::DragFloat3("Color", &matColor[0], step, step);
		
	}

	
	if (ImGui::Button("Create new light"))
	{

		if (nameBuffer[0] == '\0' && nameBuffer != NULL)
		{
			objectmanager->CreateLight("Light",
				NULL,
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer, material),
				shader->DefaultShader,
				NULL,
				lightMang->Create("Light", shader->DefaultShader, newLightData),
				myRigidbodyMang->Create(0.0f)

			);
			
			
		}
		if (nameBuffer[0] != '\0' && nameBuffer != NULL)
		{
			objectmanager->CreateLight(nameBuffer,
				NULL,
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer, material),
				shader->DefaultShader,
				NULL,
				lightMang->Create(nameBuffer, shader->DefaultShader, newLightData),
				myRigidbodyMang->Create(0.0f)
			);
			
		}
		//std::cout << "didnt work" << std::endl;
	}
	uiLightList(this, objectmanager);
	if (LightObject::LightEntities.size() > 0)
	{
		ImGui::Text("Light properties");
		
		ImGui::DragFloat3("Ambient", &lightAmbient[0], step, step);
		ImGui::DragFloat3("Specular", &lightspecular[0], step, step);
		ImGui::DragFloat3("Diffuse", &lightDiffuse[0], step, step);		//ImGui::DragScalar("Light direction", ImGuiDataType_Float, &lightVector, step, NULL, NULL, "%.4f");
		ImGui::DragFloat("Light constant", &lightConstant, step, step_fast);
		ImGui::DragFloat("Light cut off", &cutoff, step, step_fast);
		ImGui::DragFloat("Light outer cut off", &outerCutOff, step, step_fast);
		ImGui::DragFloat("Light linear", &lightLinear, step, step_fast);
		ImGui::DragFloat("Light quadratic", &lightQuadratic, step, step_fast);
		
	}

	if (ImGui::Button("Delete Object"))
	{
		if (Object::Entities.size() > 0) {
			objectmanager->Destroy(Object::Entities[Object::SelectedEntity]);
		}
		

	}
	/*if (Object::Entities[Object::SelectedEntity] != NULL) {
		 
	}*/
	
	
	if (ImGui::Combo("Light type", &SelectedItem, Items, IM_ARRAYSIZE(Items)))
	{
		if (SelectedLight)
		{
			
			//std::cout << "Selected entity is light" << std::endl; // Yes finally!!
			if (SelectedItem == 0)
			{	 
				
				lightMang->SetDirectional(newLightData, Object::Entities[Object::SelectedEntity]);
				//lightMang->InitialiseLightData(shader->DefaultShader, newLightData);
				//LightObject::LightEntities[LightObject::SelectedLightEntity]->SetDirectional(newLightData);
			}
			if (SelectedItem == 1)
			{
				lightMang->SetPoint(newLightData, Object::Entities[Object::SelectedEntity]);
				//lightMang->InitialiseLightData(shader->DefaultShader, newLightData);
				//LightObject::LightEntities[LightObject::SelectedLightEntity]->SetPoint(newLightData);
			}
			if (SelectedItem == 2)
			{
				lightMang->SetSpot(newLightData, Object::Entities[Object::SelectedEntity]);
				//lightMang->InitialiseLightData(shader->DefaultShader, newLightData);
				//LightObject::LightEntities[LightObject::SelectedLightEntity]->SetSpot(newLightData);
			}
		};
			

	}
		// How do I check if the selected entity is the same as the selected light entity, Cause I want to know when the user is selecting the Light object:: SOLVED
		
	
	ImGui::Text("");
	

   //ImGui::Text("IsKinematic", &check);
	if (ImGui::Checkbox("Is kinematic", &check)) // a bit jank
	{
		//Object::Entities[Object::SelectedEntity]->myCollider->isKinematic = check;
		//virtobj->Entities[Object::SelectedEntity]->myCollider->isKinematic;
	}

	if(ImGui::Button("Change Mesh"))
	{
		mesh = meshmang->Create("mesh", meshBuffer);
		Object::Entities[Object::SelectedEntity]->SetMesh(*mesh);
	}

	if (ImGui::Button("Change Texture"))
	{
		std::string test = "C:\\Users\\zackarias.hager\\Emgine_New\\Emgine\\resource\\textures\\";
		test.append(textureBuffer);
		
		texture = new Texture(test.c_str(), material);
		Object::Entities[Object::SelectedEntity]->SetTexture(*texture);
	}

	if (ImGui::Button("Change name"))
	{
		Object::Entities[Object::SelectedEntity]->SetName(nameBuffer);
	}


	if (ImGui::Button("Play"))
	{

	}

	ImGui::Text("Mesh Manager");
	//int n = sizeof(virtobj->Entities

	//if (this == NULL){}
		uiObjectList(this);

	//ImGui::InputText("texture file", buf, sizeof(buf) - 1);

	ImGui::Text("");

	ImGui::DragFloat("X pos", &xPos, step, step_fast);
	ImGui::DragFloat("Y pos", &yPos, step, step_fast);
	ImGui::DragFloat("Z pos", &zPos, step, step_fast);
	ImGui::Text("");
	ImGui::DragFloat("X rotate", &xRot, step, step_fast);
	ImGui::DragFloat("Y rotate", &yRot, step, step_fast);
	ImGui::DragFloat("Z rotate", &zRot, step, step_fast);
	ImGui::Text("");
	ImGui::DragFloat("X scale", &xScale, step, step_fast);
	ImGui::DragFloat("Y scale", &yScale, step, step_fast);
	ImGui::DragFloat("Z scale", &zScale, step, step_fast);

	//ImGui_ImplGlfw_Shutdown();
	ImGui::End();
	ImGui::EndFrame();;
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//glfwSwapBuffers(window);
	glfwPollEvents();

}


		