#pragma once
class Time
{
public:
	Time();
	
	void Run();
	void Pause();
	void UnPause();


	float Deltatime = 0;
	float LastTime = 0;
	float PausedTime = 0;
	double CurrentTime = 0;
	bool IsPaused = true;

	

};

