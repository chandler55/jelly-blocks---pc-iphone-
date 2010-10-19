#pragma once

#include "Shared.h"
class CShared;
class CModule
{
protected:
	CShared *shared;
	bool animatingTo, animatingFrom;
	int animatingButtons;
public:
	CModule(void);
public:
	~CModule(void);
	void linkShared(CShared *fshared);
	virtual void Update();
	virtual void Render(int alpha = 255);
	virtual void AnimateTo();
	virtual void AnimateFrom();
};

