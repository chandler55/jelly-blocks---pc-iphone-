#include "StdAfx.h"
#include "Button.h"
extern CShared *shared;
Button::Button(char *fileimageup, char *fileimagedown, int fx, int fy)
{
	shared= CShared::getInstance();
	image = new CImg(fileimageup);
	imagedown = new CImg(fileimagedown);
	x = fx; y = fy;

	rect.x = fx;
	rect.y = fy;
	rect.w = image->getWidth();
	rect.h = image->getHeight();

	isPressed = false;
}

Button::~Button(void)
{
}

void Button::Update() {
	if (shared->input->buttonPressed)
		return;
	pressed = false;
	
	if (shared->input->mouseToggle && 
		(shared->input->x >= rect.x && shared->input->x < (rect.x+rect.w) &&
		shared->input->y >= rect.y && shared->input->y <= (rect.y+rect.h))) {
		isPressed= true;
		pressed = true;
		shared->input->buttonPressed = true;
	}
	if (!shared->input->mousePressed) {
		isPressed= false;
	}
	
}
bool Button::PressAndReleased() {
	if (shared->input->x >= rect.x && shared->input->x < (rect.x+rect.w) &&
		shared->input->y >= rect.y && shared->input->y <= (rect.y+rect.h))
		return shared->input->pressAndReleased;
	else 
		return false;
}
bool Button::IsPressed() {
	if ((shared->input->x >= rect.x && shared->input->x < (rect.x+rect.w) &&
		shared->input->y >= rect.y && shared->input->y <= (rect.y+rect.h))) {
			return isPressed;
	}
	else
		return false;
}
void Button::Render() {
	if (isPressed && 
		(shared->input->x >= rect.x && shared->input->x < (rect.x+rect.w) &&
		shared->input->y >= rect.y && shared->input->y <= (rect.y+rect.h)))
		imagedown->Render(x,y,255);
	else
		image->Render(x,y,255);
}