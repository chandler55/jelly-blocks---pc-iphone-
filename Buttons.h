#pragma once
#include "Button.h"
#include "Shared.h"
class CShared;
class Button;
class Buttons
{
public:
	CShared *shared;
	Button *startbutton, *startbutton2;
	Button *rulesbutton;
	Button *leftarrow, *uparrow, *downarrow, *rightarrow;
	Button *undobutton, *menubutton, *backbutton;
	Button *resetbutton, *turnonsound, *turnoffsound;
	Button *levelselect, *backbutton2, *titlescreen;
	Button *leftarrowlevel, *rightarrowlevel;
	Button *previous, *next;
	Button *nextlevel, *colorblindon, *colorblindoff;
public:
	Buttons(void);
	~Buttons(void);
	void InitButtons();
	void LinkShared(CShared *fshared) { shared = fshared; }
};
