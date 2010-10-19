#pragma once
#include "Module.h"
/*
* splash screen when game starts
*/
class CSplash : public CModule
{
public:
	CSplash(void);
public:
	~CSplash(void);
	void Update();
	void Render(int alpha = 255);
	void AnimateTo();
	void AnimateFrom();
};
