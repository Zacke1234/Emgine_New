#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <iostream>

#include <glm/glm.hpp>
#include <CustomGame/Levels.h>
#pragma once

class BasicMenus
{
public:
	void ShowMenu(GLFWwindow* window);

	void RenderMenu();
};

