// sdl2.cpp : Defines the entry point for the console application.
//
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <iostream>
#include "SDL.h"
#include "SDL_audio.h"
#include "Shared.h"
#include "Transition.h"
#include "Game.h"
#include "Module.h"
#include "Title.h"
#include "Img.h"
#include "MusicPlayer.h"
#include <vector>
#include <windows.h>
#include "FPSCounter.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define NUM_CHANNELS 8				/* max number of sounds we can play at once */
#define NUM_DRUMS 4					/* number of drums in our set */
#define MILLESECONDS_PER_FRAME 16	/* about 60 frames per second */

using namespace std;
int keyboard(SDL_Event &event);
bool profileTime = false;
CGame *g_skeleton;
/* this array holds the audio for the drum noises */
//static struct sound drums[NUM_DRUMS];

Mixer mixer;

CShared *shared;
SDL_Surface
  *menubackground = NULL,
	*background = NULL,
	*singlebackground = NULL,
	*splash2 = NULL,
	*wifibackground = NULL,
	*sprites = NULL,
	*font = NULL,
	*smalltiles = NULL;


void audioCallback(void *userdata, Uint8 *stream, int len);

void SDLCALL audioCallback(void *userdata, Uint8 *stream, int len) {
	int i;
	int copy_amt;
	SDL_memset(stream, mixer.outputSpec.silence, len); /* initialize buffer to silence */
	/* for each channel, mix in whatever is playing on that channel */
	for (i=0; i<NUM_CHANNELS; i++) {		
		if (mixer.channels[i].position == NULL) {
			/* if no sound is playing on this channel */ 
			continue; /* nothing to do for this channel */
		}
		
		/* copy len bytes to the buffer, unless we have fewer than len bytes remaining */
		copy_amt = mixer.channels[i].remaining < len ? mixer.channels[i].remaining : len;
		
		/* mix this sound effect with the output */
		SDL_MixAudioFormat(stream, mixer.channels[i].position, mixer.outputSpec.format, copy_amt, 150);
		
		/* update buffer position in sound effect and the number of bytes left */
		mixer.channels[i].position    += copy_amt;
		mixer.channels[i].remaining   -= copy_amt;
		
		/* did we finish playing the sound effect ? */
		if (mixer.channels[i].remaining == 0) {
			mixer.channels[i].position = NULL; /* indicates no sound playing on channel anymore */
			mixer.numSoundsPlaying--;
			if (mixer.numSoundsPlaying == 0) {
				/* if no sounds left playing, pause audio callback */
				SDL_PauseAudio(1);
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	SDL_Surface* screen = new SDL_Surface();
	SDL_WindowID windowID;

	Uint8 mousestate;

	LARGE_INTEGER frequency;
	DWORD t0, t1;
	double micros; // want in microseconds, see 1e6 constant
	int x,y;     // Used to hold the mouse coordinates
	CFPSCounter *fpscounter = new CFPSCounter();

	// my init
	unsigned long time1, time2 = 0;
	background = SDL_LoadBMP("blocks.bmp");

	SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO);
	windowID = SDL_CreateWindow(NULL, 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT,\
		SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

	SDL_CreateRenderer(windowID, 2, 0);
	//srand ( SDL_GetTicks() );
	SDL_RendererInfo info;

	SDL_WM_SetCaption("SDL Test", "SDL Test");
	SDL_memset(&mixer, 0, sizeof(mixer));
	/* setup output format */
	mixer.outputSpec.freq = 44100;
	mixer.outputSpec.format = AUDIO_S16LSB;
	mixer.outputSpec.channels = 2;
	mixer.outputSpec.samples = 4096;
	mixer.outputSpec.callback = audioCallback;
	mixer.outputSpec.userdata = NULL;	
	/* open audio for output */
	if (SDL_OpenAudio(&mixer.outputSpec, NULL) != 0) {
		fatalError("Opening audio failed");
	}	
	
	/* load our drum noises */
	
	SDL_Event event;
	int gameover = 0;
	QueryPerformanceFrequency(&frequency);

	// game loop
	fpscounter->Init();

	// initialize game
	g_skeleton = new CGame();
	shared = CShared::getInstance();
	shared->linkMixer(&mixer);

	shared->sounds->LoadSounds();
	time1 = GetTickCount();
	

	while (!gameover)
	{
		uint32_t ticks = SDL_GetTicks();

		profileTime = false;
		gameover = keyboard(event);

		if (profileTime)
			t0 = SDL_GetTicks();
		
		shared->input->buttonPressed = false;

		// update input
		shared->input->Update();

		// update the game
		g_skeleton->Update();

		// render
		SDL_RenderPresent();

		if (profileTime) {
			t1 = SDL_GetTicks();

			printf("Elapse time is %d milliseconds\n",t1 - t0);
		}
		fpscounter->countFPS();

		SDL_Delay(16 - (SDL_GetTicks() - ticks) % 16);
		time2 = SDL_GetTicks();

	}
	shared->SaveToFile();

	SDL_Quit();
	
	return 0;
}

int keyboard(SDL_Event &event) {
	int gameover = 0;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
				case SDL_QUIT:
					shared->SaveToFile();
					gameover = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
				case SDLK_SPACE:
					profileTime = true;
					
					break;
				case SDLK_ESCAPE:
				case SDLK_q:
					gameover = 1;
					break;
					}
					break;
				case SDL_KEYUP:
					//shared->sounds->drum->playSound();
					//startMusic();
					//	mp->startMusic();
					break;
		}
	}
	return gameover;
}
