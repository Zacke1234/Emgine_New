#include "Time.h"
#include <glfw3.h>

#pragma once
Time::Time()
{
	
}

void Time::Run()
{


	if (IsPaused == false)
	{
		CurrentFrame = glfwGetTime();
		Deltatime = CurrentFrame - Lastframe;
		Lastframe = CurrentFrame;
		
	}
	else
	{
		CurrentFrame = 0;
	}
	
}

void Time::Pause()
{
	IsPaused = true;
}

void Time::UnPause()
{
	IsPaused = false;
}
