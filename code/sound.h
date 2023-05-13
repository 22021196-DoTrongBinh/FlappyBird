#pragma once

#include <SDL_mixer.h>
#include "lib.h"

class SOUND : LIB {
public:
	static Mix_Chunk* flap_m;
	static Mix_Chunk* hit_m;
	static Mix_Music* die_m;
	static Mix_Chunk* point_m;
	static Mix_Chunk* swosh_m;
	static Mix_Music* intro_m;
	bool init();
	void flap();
	void hit();
	void die();
	void point();
	void swosh();
	void intro();
	void restart();
	void free();
};