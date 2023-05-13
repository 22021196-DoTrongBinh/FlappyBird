#include"sound.h"
#include <SDL_mixer.h>

Mix_Chunk* SOUND::flap_m = NULL;
Mix_Chunk* SOUND::hit_m = NULL;
Mix_Music* SOUND::die_m = NULL;
Mix_Chunk* SOUND::point_m = NULL;
Mix_Chunk* SOUND::swosh_m = NULL;
Mix_Music* SOUND::intro_m = NULL;

bool SOUND::init() {
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return false;
	}
	flap_m = Mix_LoadWAV("sound\\flap.wav");
	hit_m = Mix_LoadWAV("sound\\hit.wav");
	die_m = Mix_LoadMUS("sound\\die.mp3");
	point_m = Mix_LoadWAV("sound\\point.wav");
	swosh_m = Mix_LoadWAV("sound\\swosh.wav");
	intro_m = Mix_LoadMUS("sound\\intro1.mp3");
	if (flap_m == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}
	if (hit_m == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}
	if (die_m == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}
	if (point_m == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}
	if (swosh_m == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}
	if (intro_m == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}
	return true;
}

void SOUND::free() {
	Mix_FreeChunk(flap_m);
	Mix_FreeChunk(hit_m);
	Mix_FreeMusic(die_m);
	Mix_FreeChunk(point_m);
	Mix_FreeChunk(swosh_m);
	Mix_FreeMusic(intro_m);
	flap_m = NULL;
	die_m = NULL;
	point_m = NULL;
	swosh_m = NULL;
	intro_m = NULL;
	Mix_Quit();
}

void SOUND::flap() {
	Mix_PlayChannel(-1, flap_m, 0);
}

void SOUND::hit() {
	Mix_PlayChannel(-1, hit_m, 0);
}

void SOUND::die() {
	Mix_PlayMusic(die_m, -1);
}

void SOUND::point() {
	Mix_PlayChannel(-1, point_m, 0);
}

void SOUND::swosh() {
	Mix_PlayChannel(-1, swosh_m, 0);
}

void SOUND::intro() {
	Mix_PlayMusic(intro_m, -1);
}

void SOUND::restart() {
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
}