#pragma once
//#include "SDL_mixer.h"

class CMusicPlayer
{
//	Mix_Music *music;
public:
	CMusicPlayer(void);
public:
	~CMusicPlayer(void);
	void startMusic();
	void musicDone();
};
