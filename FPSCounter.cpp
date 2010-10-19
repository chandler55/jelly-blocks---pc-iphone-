#include "StdAfx.h"
#include "FPSCounter.h"
#include <math.h>
#include <windows.h>
#include "SDL.h"

CFPSCounter::CFPSCounter(void)
{

}

CFPSCounter::~CFPSCounter(void)
{

}
void CFPSCounter::Init() {
	numFrames = 0;
	startTick  = SDL_GetTicks();
}
void CFPSCounter::countFPS() {
	numFrames++;
	float t = (SDL_GetTicks() - startTick) * 0.001;
	if (t > 1) {
		if (numFrames < 60)
		printf("%f %f\n",numFrames, floor((numFrames / t) * 10.0) / 10.0);
		startTick = SDL_GetTicks();
		numFrames =0;
	}

}
