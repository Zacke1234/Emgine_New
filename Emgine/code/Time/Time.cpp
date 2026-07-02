#include "Time.h"
#include <glfw3.h>

#pragma once
Time::Time()
{
	LastTime = 0;
	Deltatime = 0;
	CurrentTime = 0;

}

void Time::Run()
{
	if (!IsPaused)
	{
		LastTime = CurrentTime;
		//CurrentTime = glfwGetTime();
		CurrentTime += 0.01f;
		Deltatime = CurrentTime - LastTime;
	}
}

void Time::Pause()
{
	IsPaused = true;
}

void Time::UnPause()
{
	IsPaused = false;
	Deltatime = 0;
}
