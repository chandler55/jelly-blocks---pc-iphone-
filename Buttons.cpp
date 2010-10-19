#include "StdAfx.h"
#include "Buttons.h"

Buttons::Buttons(void)
{

	 startbutton = startbutton2=
	 rulesbutton=
	 leftarrow= uparrow= downarrow= rightarrow=
	 undobutton= menubutton= backbutton=
	 resetbutton= turnonsound= turnoffsound=
	 levelselect= backbutton2= titlescreen=
	 leftarrowlevel= rightarrowlevel=
	 previous= next=
	 nextlevel= colorblindon= colorblindoff= NULL;
	
}

void Buttons::InitButtons() {

	//risestackbutton = new Button("raisestackbutton.png","raisestackbuttondown.png",8,385);
	if (startbutton == NULL) {
		startbutton = new Button("startbutton.png", "startbuttondown.png", 128,267);
		return;
	}
	if (rulesbutton == NULL) {
		rulesbutton = new Button("rulesbutton.png", "rulesbuttondown.png", 77-66, 433);
		return;
	}
	if (startbutton2 == NULL) {
		startbutton2 = new Button("startbutton.png", "startbuttondown.png", 127,383);
		return;
	}
	if (leftarrow == NULL) {
		leftarrow = new Button("leftarrowbutton.png", "leftarrowbuttondown.png", 133,344);
		return;
	}
	if (uparrow == NULL) {
		uparrow = new Button("uparrowbutton.png", "uparrowbuttondown.png", 182,292);
		return;
	}
	if (rightarrow == NULL) {
		rightarrow = new Button("rightarrowbutton.png", "rightarrowbuttondown.png", 230,344);
		return;
	}
	if (downarrow == NULL) {
		downarrow = new Button("downarrowbutton.png", "downarrowbuttondown.png", 182,396);
		return;
	}
	if (undobutton == NULL) {
		undobutton = new Button("undobutton.png", "undobuttondown.png", 22,301);
		return;
	}
	if (menubutton == NULL) {
		menubutton = new Button("menubutton.png", "menubuttondown.png", 77-66,433);
		return;
	}
	if (backbutton == NULL) {
		backbutton = new Button("backbutton.png", "backbuttondown.png", 77-66, 433);
		return;
	}
	if (resetbutton == NULL) {
		resetbutton = new Button("resetbutton.png", "resetbuttondown.png", 56,74);
		return;
	}
	if (turnonsound == NULL) {
		turnonsound = new Button("turnonsoundbutton.png", "turnonsoundbuttondown.png", 56,114);
		return;
	}
	if (turnoffsound == NULL) {
		turnoffsound = new Button("turnoffsoundbutton.png", "turnoffsoundbuttondown.png", 56,114);
		return;
	}
	if (levelselect == NULL) {
		levelselect = new Button("levelselectbutton.png", "levelselectbuttondown.png", 56,196);
		return;
	}
	if (backbutton2 == NULL) {
		backbutton2 = new Button("backbutton.png", "backbuttondown.png", 56,240);
		return;
	}
	if (titlescreen == NULL) {
		titlescreen = new Button("titlescreenbutton.png", "titlescreenbuttondown.png", 77-66,433);
		return;
	}
	if (leftarrowlevel == NULL) {
		leftarrowlevel = new Button("leftarrowlevelbutton.png", "leftarrowlevelbuttondown.png", 17,279);
		return;
	}
	if (rightarrowlevel == NULL) {
		rightarrowlevel = new Button("rightarrowlevelbutton.png", "rightarrowlevelbuttondown.png", 255,279);
		return;
	}
	if (next == NULL) {
		next = new Button("nextbutton.png", "nextbuttondown.png", 243,400);
		return;
	}
	if (previous == NULL) {
		previous = new Button("prevbutton.png", "prevbuttondown.png", 77-66,400);
		return;
	}
	if (nextlevel == NULL) {
		nextlevel= new Button("nextlevelbutton.png", "nextlevelbuttondown.png", 127,210);
		return;
	}
	if (colorblindon == NULL) {
		colorblindon= new Button("colorblindbuttonon.png", "colorblindbuttonondown.png", 56,156);
		return;
	}
	if (colorblindoff == NULL) {
		colorblindoff= new Button("colorblindbuttonoff.png", "colorblindbuttonoffdown.png", 56,156);
		return;
	}
	
}
Buttons::~Buttons(void)
{
}
