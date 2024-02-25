#include "../inc/header.h"

void mx_play_menu_music(const char *musicPath)
{
    //initialize sdl mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//Load audio files
	Mix_Music *backgroundSound = Mix_LoadMUS(musicPath);
    //Start music
	Mix_PlayMusic(backgroundSound, -1);
}
