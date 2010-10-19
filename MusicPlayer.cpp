#include "StdAfx.h"
#include "MusicPlayer.h"

CMusicPlayer::CMusicPlayer(void)
{

	/* We're going to be requesting certain things from our audio
	device, so we set them up beforehand */
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 4096;

	/* This is where we open up our audio device.  Mix_OpenAudio takes
	as its parameters the audio format we'd /like/ to have. */
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		printf("Unable to open audio!\n");
		exit(1);
	}
}

CMusicPlayer::~CMusicPlayer(void)
{
}


/* This is the function that we told SDL_Mixer to call when the music
was finished. In our case, we're going to simply unload the music
as though the player wanted it stopped.  In other applications, a
different music file might be loaded and played. */
void CMusicPlayer::musicDone() {
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = NULL;
}
void CMusicPlayer::startMusic() {

	/* Here we're going to have the 'm' key toggle the music on and
	off.  When it's on, it'll be loaded and 'music' will point to
	something valid.  If it's off, music will be NULL. */

	if(music == NULL) {

		/* Actually loads up the music */
		music = Mix_LoadMUS("jewel.mp3");
		if(!music) 
		{
			printf("Mix_LoadMUS(\"jewel.mp3\"): %s\n", Mix_GetError());
			// this might be a critical error...
		}

		/* This begins playing the music - the first argument is a
		pointer to Mix_Music structure, and the second is how many
		times you want it to loop (use -1 for infinite, and 0 to
		have it just play once) */
		Mix_PlayMusic(music, 0);

		/* We want to know when our music has stopped playing so we
		can free it up and set 'music' back to NULL.  SDL_Mixer
		provides us with a callback routine we can use to do
		exactly that */
		//Mix_HookMusicFinished(MusicPlayer::musicDone);

	} else {
		/* Stop the music from playing */
		Mix_HaltMusic();

		/* Unload the music from memory, since we don't need it
		anymore */
		Mix_FreeMusic(music);

		music = NULL;
	}


}


