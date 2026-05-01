#include "MainGameplay.h"



void MainGameplay::Start(GLFWwindow* window)
{
	
	player = new Player(window);
	
}

void MainGameplay::Run()
{
	player->InputMovement();

}
