#include "StdAfx.h"
#include "Transition.h"

CTransition::CTransition(void)
{
	CModule::CModule();
	imageFrom = new CImg("blank.bmp");
	imageTo = new CImg("blank.bmp");

	transitionTimer= 0;
	alpha = 255;
}

CTransition::~CTransition(void)
{
}
void CTransition::Update() {
	// initialize images
	if (transitionTimer == 0) {
	//	shared->modules[shared->nextstate]->Render();
	//	int success = SDL_RenderReadPixels(rect,pixels,pitch);
		//printf("%d success reading screen", success);
	}
	transitionTimer++;
	Render();
	if (transitionTimer > 59) {
		alpha = 255;
		shared->gamestate = shared->nextstate;
		transitionTimer = 0;
	}
	
}
void CTransition::Render() {
	//imageTo->Init("blank.bmp");
	if (shared->transitionType == shared->FADE) {
		alpha-=4;
	//	shared->modules[shared->prevstate]->Render(imageFrom->getSurface());
		//shared->modules[shared->nextstate]->Render(imageTo->getSurface());

		imageFrom->Render(0,0,alpha);
		imageTo->Render(0,0,255-alpha);	
	}
	else if (shared->transitionType == shared->FADETOBLACK) {
		alpha -= 4;
		
		if (transitionTimer <= 30) {
			shared->modules[shared->prevstate]->Render();

			int alpha = int((transitionTimer/30.0)*255.0);
			//imageFrom->Render(0,0,255-alpha);
		} else {
			int alpha = int(((transitionTimer-30)/30.0)*255.0);
			shared->modules[shared->nextstate]->Render();
			//imageTo->Render(0,0,alpha);
		}
	} else if (shared->transitionType == shared->EXPAND) {
		shared->modules[shared->prevstate]->Render();
		shared->modules[shared->nextstate]->Render();
	}

}
void CTransition::AnimateFrom() {
}
void CTransition::AnimateTo() {
}