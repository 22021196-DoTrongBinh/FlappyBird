#pragma once
#include"lib.h"

class PIPE : LIB {
public:
	SDL_Texture* pipe_texture = NULL;
	SDL_Texture* piranha_texture = NULL;
	SDL_Texture* turret_texture = NULL;
	SDL_Texture* bullet_texture = NULL;
	position pipePos;
	position bulletPos;
	int ahead = 0;
	int score = 0;
	int index_pipe = 0;
	int bestscore = 0;
	int pipe_speed[4] = {1, 1, 1, 1};
	int piranha_height = 0;
	void init();
	void render();
	void update();
	void score_render();
	SDL_Rect score_rect = { 270, 80, 30, 45 };
	SDL_Rect piranha_rect = { 0, 0, 96, 105 };
	SDL_Rect turret_rect1 = { 0, 0, 48, 100 };
	SDL_Rect turret_rect2 = { 0, 0, 48, 100 };
	SDL_Rect bullet_rect = { SCREEN_WIDTH, 0, 58, 48 };
	void restart();
	void scoreAndBest();
	SDL_Rect score_b = { 210, 253, 25, 37 };
	SDL_Rect best_s = { 210, 313, 25, 37 };
};