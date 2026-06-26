#pragma once

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
#include <Time/Time.h>
#include <glfw3.h>
#include <CustomGame/MainGameplay.h>

//namespace {};


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

LightingManager* myLightingManager;
RigidbodyManager* myRigidbodyManager;
Physics* Phys;
CameraManager* myCameraManager;
Time* myTime;
MainGameplay* myGameplay;