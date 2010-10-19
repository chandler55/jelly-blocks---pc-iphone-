#pragma once
#include "SDL.h"
#include "Img.h"
#include "Shared.h"
class CShared;
class Button
{
	CShared *shared;
	CImg *image, *imagedown;
	int x,y;
	SDL_Rect rect;
	bool pressed;
	bool isPressed;
	bool pressAndReleased;
public:
	Button(char *fileimageup, char *fileimagedown, int fx, int fy);
	~Button(void);
	void Update();
	void Render();
	bool Pressed() { return pressed; }
	void LinkShared(CShared *fshared) { shared = fshared; }
	bool IsPressed();
	bool PressAndReleased();
};
