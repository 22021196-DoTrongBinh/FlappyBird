#pragma once
#include"lib.h"


class BACKGROUND : LIB {
	public:
	SDL_Texture* background_texture = NULL;
	void render();
};