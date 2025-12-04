#pragma once
class Time
{
public:
	Time();
	
	

	float Deltatime = 0;
	float Lastframe = 0;
	float PausedTime = 0;
	double CurrentFrame = 0;
	bool IsPaused = true;

	void Run();
	void Pause();
	void UnPause();

};

