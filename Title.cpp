#include "StdAfx.h"
#include "Title.h"

CTitle::CTitle(void)
{
	CModule::CModule();
}

CTitle::~CTitle(void)
{
}

void CTitle::Update() {
	
	if (shared->input->mouseToggle) {
		shared->nextstate = 0;
	}
	Render();
}
void CTitle::Render(int alpha) {
	shared->images->backgrounds[0]->Render();
	shared->images->titlebackground->Render();
	if (shared->TRANSITION != shared->gamestate) {
		//shared->images->megaman->Render(350+(-1*5*50),50,int(255*(50/50)));
	} else {
		animatingFrom= true;
	}
}
void CTitle::AnimateFrom() {

}
void CTitle::AnimateTo() {

}