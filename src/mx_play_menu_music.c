#include "../inc/header.h"

void mx_play_menu_music(const char *musicPath, int MusicFlag)
{
	//initialize sdl mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//Load audio files
	Mix_Music *backgroundSound = Mix_LoadMUS(musicPath);
	Mix_Music *GameplayBackgroundSound = Mix_LoadMUS(musicPath);
	
	if(MusicFlag == 1) {
		Mix_PlayMusic(backgroundSound, -1);
	} else {
		Mix_PlayMusic(GameplayBackgroundSound, -1);
	}

}
