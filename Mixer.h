#pragma once
#define NUM_CHANNELS 8				/* max number of sounds we can play at once */
#include "SDL.h"

struct Mixer {
	/* channel array holds information about currently playing sounds */
	struct {
		Uint8 *position;		/* what is the current position in the buffer of this sound ? */
		Uint32 remaining;		/* how many bytes remaining before we're done playing the sound ? */
		Uint32 timestamp;		/* when did this sound start playing ? */
	} channels[NUM_CHANNELS];
	SDL_AudioSpec outputSpec;	/* what audio format are we using for output? */
	int numSoundsPlaying;		/* how many sounds are currently playing */
};