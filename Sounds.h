#pragma once
#include "Sound.h"
#include "SDL.h"
#include "common.h"


class CSounds
{
public:
	Mixer *mixer;
	CSound *drum;
	CSound *switchSound,*menu, *popping, *combo, *chaincombo, *made3;
	CSound *undo, *winner, *ending;
	//struct sound test;
public:
	CSounds(void);
	~CSounds(void);
	void LoadSounds();
	void loadSound(const char *file, CSound *s);

	//void linkMixer(Mixer *mixer) {mixer = fmixer;}


};
