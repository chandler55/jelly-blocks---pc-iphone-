#pragma once

#include "module.h"

class CModule;
class CTitle :
	public CModule
{
public:
	CTitle(void);
public:
	~CTitle(void);
	void Update();
	void Render(int alpha = 255);
	void AnimateTo();
	void AnimateFrom();
};
