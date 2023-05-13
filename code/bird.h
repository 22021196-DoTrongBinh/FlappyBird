#pragma once
#include"lib.h"
#include"pipe.h"

class BIRD : LIB {
public:
	position birdPos;
	SDL_Texture* bird_texture = NULL;
	int angle = 0;
	int time = 0;
	int x0 = bird_rect[0].y;
	int angleSpeed = 3;
	const int wing_speed = 5;
	int index_wing = 2 * wing_speed;
	int wing = 1;
	void render();
	void update();
	void restart();
};