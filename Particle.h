#pragma once
#include "SDL.h"
#include "Img.h"
#include "Shared.h"
class Particle
{
public:
	float x, y;
	Uint32 color;
	float vx, vy;
	float ax, ay;
	bool alive; 
	int type;
	int lifeLeft;
	float alpha;
	float fadeVelocity;
	float colorR, colorG, colorB;
	float scale;
	float scaleVelocity;
	float startR, startG, startB;
	float endR, endG, endB;
	float isColorChanging;
public:
	Particle(void);
	~Particle(void);
	void Init();
	void Update();
	void Render();
};
