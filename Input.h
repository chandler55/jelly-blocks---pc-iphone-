#pragma once
#include "SDL.h"
#include <iostream>
class CInput
{
public:
	Uint8 mousestate;
	int x, y;
	bool mouseToggle, mousePressed, mouseDown;
	bool lastFrameMouseWasPressed;
	bool pressAndReleased;
	bool buttonPressed;
public:
	CInput(void);
public:
	~CInput(void);
	void Update();
	bool MousePressed() { return mouseToggle; }
	bool ButtonIsDown() { return false; }
	bool ButtonPressed() { return false; }
};
