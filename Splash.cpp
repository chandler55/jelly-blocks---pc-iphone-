#include "StdAfx.h"
#include "Splash.h"

CSplash::CSplash(void)
{
	CModule::CModule();
	animatingButtons= 200;
	animatingFrom= true;
	animatingTo = true;
}

CSplash::~CSplash(void)
{
}
void CSplash::Update() {
	if (animatingTo) {
		AnimateTo();
		return;
	}
	if (shared->input->mouseToggle) {
		animatingTo = true;
	}
	Render();
}
void CSplash::Render(int alpha) {
	shared->images->splash->Render();
	shared->images->crescent->Render(210,93,255);
	if (shared->TRANSITION != shared->gamestate) {
	
	} else {
		animatingFrom= true;
	}
}
void CSplash::AnimateFrom() {
}
void CSplash::AnimateTo() {
	shared->images->splash->Render();
	float alpha = 255*((150-(animatingButtons-50))/150.0);
	if (animatingButtons > 50)
		shared->images->crescent->Render(210,93,int(alpha));
	else
		shared->images->crescent->Render(210,93,255);

	if (animatingButtons > 0) {
		animatingButtons--;
		
	} else {
		animatingButtons = 200;
		shared->nextstate = 1;
		animatingTo = false;
	}
}