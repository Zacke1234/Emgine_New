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
		glfwSetTime(CurrentFrame);
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
