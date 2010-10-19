#include "StdAfx.h"
#include "Particle.h"

Particle::Particle(void)
{
}

Particle::~Particle(void)
{
}

void Particle::Init() {
	colorR= colorG= colorB = 0;
	startR= startG= startB = 0;
	endR= endG= endB = 0;
	color = 0;
	vx = vy = ax = ay = 0;
	x = y = 0;
	type = 0;
	alive = false;
	lifeLeft = 0;
	alpha  = 255;
	fadeVelocity= 1;
	scale= 1;
	scaleVelocity = 1;
	isColorChanging= -1;
}

void Particle::Update() {
	lifeLeft--;
	if (lifeLeft == 0) {
		Init();
		return;
	}
	alpha *= fadeVelocity;
	scale *= scaleVelocity;
	x += vx;
	y += vy;
	vx += ax;
	vy += ay;
	if (isColorChanging != -1) {
		colorR += (endR - startR)/isColorChanging;
		colorG += (endG - startG)/isColorChanging;
		colorB += (endB - startB)/isColorChanging;
	}
}