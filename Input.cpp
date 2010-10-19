#include "StdAfx.h"
#include "Input.h"

CInput::CInput(void)
{
	mousestate = 0;
	x = y = 0;
	mouseToggle = mousePressed = mouseDown = false;
	lastFrameMouseWasPressed = false;
	pressAndReleased= false;
}

CInput::~CInput(void)
{
}

void CInput::Update() {
	mousestate = SDL_GetMouseState(&x, &y);    // Get the mouse coords
	pressAndReleased = false;

	mouseToggle = false;
	if (mousestate&SDL_BUTTON(1)) {
		if (!mousePressed)
			lastFrameMouseWasPressed = mouseToggle = mousePressed = true;
	} else {
		mousePressed = false;
		if (lastFrameMouseWasPressed) {
			lastFrameMouseWasPressed = false;
			pressAndReleased = true;
		}
	}
	if (mousePressed) {
		//g_game->TouchDown(x,y);
		//g_game->TouchDrag(x,y);
	} else {
		//g_game->TouchUp(x,y);
	}

	//if (mouseToggle)
	//	printf("mouse pressed %d %d\n", x, y);
}