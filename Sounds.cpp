#include "StdAfx.h"
#include "Sounds.h"

CSounds::CSounds(void)
{
	mixer = new Mixer();
	
}

CSounds::~CSounds(void)
{
}

void CSounds::LoadSounds() {
	drum = new CSound("move.wav",mixer);
	undo = new CSound("simple.wav",mixer);
	switchSound= new CSound("switch.wav",mixer);
	menu = new CSound("menu.wav", mixer);
	winner = new CSound("winner.wav", mixer);
	ending = new CSound("ending.wav",mixer);
}

void CSounds::loadSound(const char *file, CSound *s) {
	SDL_AudioSpec spec;		/* the audio format of the .wav file */
	SDL_AudioCVT cvt;		/* used to convert .wav to output format when formats differ */
	int result;
	if (SDL_LoadWAV(file, &spec, &s->buffer, &s->length) == NULL) {
		fatalError("could not load .wav");
	}
	/* build the audio converter */
	result = SDL_BuildAudioCVT(&cvt, spec.format, spec.channels, spec.freq,
							   mixer->outputSpec.format, mixer->outputSpec.channels, mixer->outputSpec.freq);
	if (result == -1) {
		fatalError("could not build audio CVT");
	}
	else if (result != 0) {
		/* 
		 this happens when the .wav format differs from the output format.
		 we convert the .wav buffer here
		 */
		cvt.buf = (Uint8 *)SDL_malloc(s->length * cvt.len_mult); /* allocate conversion buffer */
		cvt.len = s->length;									  /* set conversion buffer length */
		SDL_memcpy(cvt.buf, s->buffer, s->length);				  /* copy sound to conversion buffer */
		if (SDL_ConvertAudio(&cvt) == -1) {					  /* convert the sound */
			fatalError("could not convert .wav");
		}
		SDL_free(s->buffer);									  /* free the original (unconverted) buffer */
		s->buffer = cvt.buf;									  /* point sound buffer to converted buffer */
		s->length = cvt.len_cvt;								  /* set sound buffer's new length */
	}
}
