#pragma once
#include "module.h"
#include "SDL.h"
class CTransition :
	public CModule
{
	float alpha;
	int transitionTimer;
	CImg *imageFrom, *imageTo;
	SDL_Rect *rect;
	void *pixels;
	int pitch;

public:
	CTransition(void);
public:
	~CTransition(void);
	void Update();
	void Render();
	void AnimateTo();
	void AnimateFrom();
};
