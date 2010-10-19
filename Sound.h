#pragma once
#include "SDL.h"
#include "common.h"
#include "Mixer.h"

class CSound
{
public:
	Mixer *mixer;
	Uint8 *buffer;			/* audio buffer for sound file */
	Uint32 length;			/* length of the buffer (in bytes) */
public:
	CSound(char *filename,Mixer *fmixer);
	~CSound(void);
	int playSound();
	void loadSound(const char *file);
	//void linkMixer(Mixer *mixer) {mixer = fmixer;}
};
