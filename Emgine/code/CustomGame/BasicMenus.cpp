#include "BasicMenus.h"


void BasicMenus::ShowMenu(GLFWwindow* window)
{
	
}

void BasicMenus::RenderMenu()
{
	
	ImGui::Begin("Level Select");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Select a level to play.");
	
	//ImGui::Text("Currently playing level: %.1f " , 1);
	
	for (int l = 0; l < Levels::levelList.size(); l++)
	{
		
		if (ImGui::Button(Levels::levelList[l]->name.c_str()))
		{
			Levels::SelectedLevel = l;

			Levels::levelList[l]->Clear();
			
			Levels::levelList[l]->Load();
			
			//


			//

			// 
		}
		ImGui::Text("Record Time %.2f", Levels::levelList[l]->recordTime);
	}
	
	ImGui::Text("Time %.2f", Levels::levelList[Levels::SelectedLevel]->levelTime);

	

	if (ImGui::Button("Restart"))
	{
		Teleported = true;
		Levels::levelList[Levels::SelectedLevel]->tempTime->CurrentTime = 0.0f;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
