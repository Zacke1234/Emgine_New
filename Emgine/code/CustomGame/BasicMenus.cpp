#include "BasicMenus.h"

void BasicMenus::ShowMenu(GLFWwindow* window)
{
	
}

void BasicMenus::RenderMenu()
{
	
	ImGui::Begin("Level Select");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Select a level to play.");

	for (auto& l : Levels::levelList)
	{
		if (ImGui::Button(l->name.c_str()))
		{

		}
	}
	

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//glfwSwapBuffers(window);
	//glfwPollEvents();
}
