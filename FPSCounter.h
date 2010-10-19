#pragma once

class CFPSCounter
{
	float numFrames;
	float startTick;

public:
	CFPSCounter(void);
public:
	~CFPSCounter(void);
	void countFPS();
	void Init();
};
