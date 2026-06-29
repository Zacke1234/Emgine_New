#include "BasicMenus.h"

void BasicMenus::ShowMenu(GLFWwindow* window)
{
	
}

void BasicMenus::RenderMenu()
{
	
	ImGui::Begin("Level Select");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Select a level to play.");

	
	for (int l = 0; l < Levels::levelList.size(); l++)
	{
		if (ImGui::Button(Levels::levelList[l]->name.c_str()))
		{
			Levels::SelectedLevel = l;

			//

			//

			// 
		}
	}
	
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
