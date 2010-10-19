#include "StdAfx.h"
#include "Sound.h"

CSound::CSound(char *filename,Mixer *fmixer)
{
	mixer = fmixer;
	loadSound(filename);
}

CSound::~CSound(void)
{
}

void CSound::loadSound(const char *file) {
	SDL_AudioSpec spec;		/* the audio format of the .wav file */
	SDL_AudioCVT cvt;		/* used to convert .wav to output format when formats differ */
	int result;
	if (SDL_LoadWAV(file, &spec, &buffer, &length) == NULL) {
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
		cvt.buf = (Uint8 *)SDL_malloc(length * cvt.len_mult); /* allocate conversion buffer */
		cvt.len = length;									  /* set conversion buffer length */
		SDL_memcpy(cvt.buf, buffer, length);				  /* copy sound to conversion buffer */
		if (SDL_ConvertAudio(&cvt) == -1) {					  /* convert the sound */
			fatalError("could not convert .wav");
		}
		SDL_free(buffer);									  /* free the original (unconverted) buffer */
		buffer = cvt.buf;									  /* point sound buffer to converted buffer */
		length = cvt.len_cvt;								  /* set sound buffer's new length */
	}
}
int CSound::playSound() {
	/*
		find an empty channel to play on.
		if no channel is available, use oldest channel
	*/
	int i;
	int selected_channel = -1;
	int oldest_channel = 0;
	//printf("%d",mixer->numSoundsPlaying);
	if (mixer->numSoundsPlaying == 0) {
		
		/* we're playing a sound now, so start audio callback back up */
		SDL_PauseAudio(0);
	}	
	
	/* find a sound channel to play the sound on */
	for (i=0; i<NUM_CHANNELS; i++) {
		if (mixer->channels[i].position == NULL) {
			/* if no sound on this channel, select it */
			selected_channel = i;
			break;
		}
		/* if this channel's sound is older than the oldest so far, set it to oldest */
		if (mixer->channels[i].timestamp < mixer->channels[oldest_channel].timestamp)
			oldest_channel = i;
	}
	
	/* no empty channels, take the oldest one */
	if (selected_channel == -1) 
		selected_channel = oldest_channel;
	else 
		mixer->numSoundsPlaying++;
	
	/* point channel data to wav data */
	mixer->channels[selected_channel].position	= this->buffer;
	mixer->channels[selected_channel].remaining	= this->length;
	mixer->channels[selected_channel].timestamp  = SDL_GetTicks();
	
	return selected_channel;
}