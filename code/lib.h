#pragma once
#include<SDL.h>
#include"utils.h"

class LIB {
public:
	class position {
	public:
		short int x, y;
		void getPos(short int x, short int y) {
			this->x = x;
			this->y = y;
		};
	};
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	const int SCREEN_WIDTH = 540;
	const int SCREEN_HEIGHT = 720;
	const int SCREEN_SPEED = 3;

	const int BACKGROUND_WIDTH = 540;
	const int BACKGROUND_HEIGHT = 720;

	const int PIPE_WIDTH = 100;
	const int PIPE_HEIGHT = 575;
	int PIPE_SPACE = 224;
	const int PIPE_GAP = 320;
	int maxrand = 650;
	int minrand = 350;

	const int GROUND_WIDTH = 540;
	const int GROUND_HEIGHT = 90;

	const int BIRD_WIDTH = 69;
	const int BIRD_HEIGHT = 48;
	const int BIRD_START_X = 235;
	const int BIRD_START_Y = 291;

	SDL_Rect background_rect = { 0, 0, 540, 720 };
	SDL_Rect ground_rect = { 0, 630, 540, 90 };
	SDL_Rect groundcopy_rect = { SCREEN_WIDTH, 630, 540, 90 };
	SDL_Rect bird_rect[4] = {
		{235, 291, 69, 48},
		{0, 0, 92, 64},
		{92, 0, 92, 64},
		{184, 0, 92, 64},
	};
	SDL_Rect downpipe_rect[4];
	SDL_Rect uppipe_rect[4];
};