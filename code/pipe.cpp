#include "pipe.h"
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include"bird.h"

void PIPE::init() {
	for (int i = 0; i < 4; i++) {
		downpipe_rect[i] = { 2 * SCREEN_WIDTH + i * PIPE_GAP, rand() % (maxrand - minrand + 1) + minrand, PIPE_WIDTH, PIPE_HEIGHT };
		uppipe_rect[i] = downpipe_rect[i];
		uppipe_rect[i].y = downpipe_rect[i].y - PIPE_SPACE - 575;
	}
}

void PIPE::render() {
	pipe_texture = loadTexture("images\\pipe-night.png", renderer);
	piranha_rect.x = downpipe_rect[ahead].x + 2;
	
	if (score >= 12) {
		PIPE_SPACE = 324;
	}

	if (score >= 15 && score < 20) {
		piranha_texture = loadTexture("images\\piranha.png", renderer);
			pipe_speed[0] = 0;
			pipe_speed[1] = 0;
			pipe_speed[2] = 0;
			pipe_speed[3] = 0;
		SDL_RenderCopy(renderer, piranha_texture, NULL, &piranha_rect);
		piranha_height = 100;
	}
	if (score >= 20) {
		if (PIPE_SPACE >= 280)	PIPE_SPACE -= 5;
		turret_texture = loadTexture("images\\turret.png", renderer);
		turret_rect1.x = piranha_rect.x;
		turret_rect1.y = piranha_rect.y + 2;
		turret_rect2.y = turret_rect1.y;
		turret_rect2.x = turret_rect1.x + 48;
		SDL_RenderCopy(renderer, turret_texture, NULL, &turret_rect1);
		SDL_RenderCopy(renderer, turret_texture, NULL, &turret_rect2);
	}
	if (piranha_rect.y >= downpipe_rect[ahead].y - 100) {
		piranha_rect.y -= 2;
	}
	for (int i = 0; i < 4; i++) {
		if (downpipe_rect[i].x <= SCREEN_WIDTH) {
			SDL_RenderCopy(renderer, pipe_texture, NULL, &downpipe_rect[i]);
			SDL_RenderCopyEx(renderer, pipe_texture, NULL, &uppipe_rect[i], 180, NULL, SDL_FLIP_HORIZONTAL);
		}
	}
	if (score >= 20) {
		bullet_texture = loadTexture("images\\bullet.png", renderer);
		if (bullet_rect.x >= -100) {
			bullet_rect.x -= 7;
			SDL_RenderCopy(renderer, bullet_texture, NULL, &bullet_rect);
		}
		SDL_DestroyTexture(bullet_texture);
		bulletPos.getPos(bullet_rect.x, bullet_rect.y);
	}
	SDL_DestroyTexture(piranha_texture);
	piranha_texture = NULL;
	SDL_DestroyTexture(pipe_texture);
	pipe_texture = NULL;
	SDL_DestroyTexture(turret_texture);
	turret_texture = NULL;
}

void PIPE::update() {
	uppipe_rect[0].x -= SCREEN_SPEED;
	downpipe_rect[0].x -= SCREEN_SPEED;
	uppipe_rect[1].x -= SCREEN_SPEED;
	downpipe_rect[1].x -= SCREEN_SPEED;
	uppipe_rect[2].x -= SCREEN_SPEED;
	uppipe_rect[3].x -= SCREEN_SPEED;
	downpipe_rect[2].x -= SCREEN_SPEED;
	downpipe_rect[3].x -= SCREEN_SPEED;

	if (score >= 5 && score <= 15) {
		uppipe_rect[0].y += pipe_speed[0];
		downpipe_rect[0].y += pipe_speed[0];
		if (downpipe_rect[0].y > maxrand || downpipe_rect[0].y < minrand)	pipe_speed[0] *= -1;

		uppipe_rect[1].y += pipe_speed[1];
		downpipe_rect[1].y += pipe_speed[1];
		if (downpipe_rect[1].y > maxrand || downpipe_rect[1].y < minrand)	pipe_speed[1] *= -1;

		uppipe_rect[2].y += pipe_speed[2];
		downpipe_rect[2].y += pipe_speed[2];
		if (downpipe_rect[2].y > maxrand || downpipe_rect[2].y < minrand)	pipe_speed[2] *= -1;

		uppipe_rect[3].y += pipe_speed[3];
		downpipe_rect[3].y += pipe_speed[3];
		if (downpipe_rect[3].y > maxrand || downpipe_rect[3].y < minrand)	pipe_speed[3] *= -1;
		if (score >= 10) {
			if (pipe_speed[0] < 0)	pipe_speed[0] = -2;
			else pipe_speed[0] = 2;
			if (pipe_speed[1] < 0)	pipe_speed[1] = -2;
			else pipe_speed[1] = 2;
			if (pipe_speed[2] < 0)	pipe_speed[2] = -2;
			else pipe_speed[2] = 2;
			if (pipe_speed[3] < 0)	pipe_speed[3] = -2;
			else pipe_speed[3] = 2;
		}
	}

	if (downpipe_rect[index_pipe].x <= -100) {
		downpipe_rect[index_pipe].x = 1180;
		uppipe_rect[index_pipe] = downpipe_rect[index_pipe];
		downpipe_rect[index_pipe].y = rand() % (maxrand - minrand + 1) + minrand;
		uppipe_rect[index_pipe].y = downpipe_rect[index_pipe].y - PIPE_SPACE - 575;
	}
	index_pipe = (index_pipe + 1) % 4;
	pipePos.getPos(downpipe_rect[ahead].x, downpipe_rect[ahead].y);

	if (pipePos.x < 135) {
		ahead = (ahead + 1) % 4;
		piranha_rect.y = downpipe_rect[ahead].y + 20;
		bullet_rect.y = downpipe_rect[(ahead + 3) % 4].y;
		bullet_rect.x = SCREEN_WIDTH + 58;
	}
}

void PIPE::score_render() {
	string s = to_string(score);
	int len = s.length();
	SDL_Texture* point;
	for (int i = 0; i < len; i++) {
		char number = s[i] - '0';
		if (number == 1) {
			point = loadTexture("images/number/1.png", renderer);
		}
		else if (number == 2) {
			point = loadTexture("images/number/2.png", renderer);
		}
		else if (number == 3) {
			point = loadTexture("images/number/3.png", renderer);
		}
		else if (number == 4) {
			point = loadTexture("images/number/4.png", renderer);
		}
		else if (number == 5) {
			point = loadTexture("images/number/5.png", renderer);
		}
		else if (number == 6) {
			point = loadTexture("images/number/6.png", renderer);
		}
		else if (number == 7) {
			point = loadTexture("images/number/7.png", renderer);
		}
		else if (number == 8) {
			point = loadTexture("images/number/8.png", renderer);
		}
		else if (number == 9) {
			point = loadTexture("images/number/9.png", renderer);
		}
		else {
			point = loadTexture("images/number/0.png", renderer);
		}
		score_rect.x = 270 - 15 * len + i * 30;
		SDL_RenderCopy(renderer, point, NULL, &score_rect);
		SDL_DestroyTexture(point);
		point = NULL;
	}
}

void PIPE::restart() {
	PIPE_SPACE = 224;
	init();
	score = 0;
	ahead = 0;
	index_pipe = 0;
	piranha_height = 0;
	pipe_speed[0] = 1;
	pipe_speed[1] = 1;
	pipe_speed[2] = 1;
	pipe_speed[3] = 1;
}

void PIPE::scoreAndBest() {
	string s = to_string(score);
	int len = s.length();
	SDL_Texture* point;
	for (int i = 0; i < len; i++) {
		char number = s[i] - '0';
		if (number == 1) {
			point = loadTexture("images/number/1.png", renderer);
		}
		else if (number == 2) {
			point = loadTexture("images/number/2.png", renderer);
		}
		else if (number == 3) {
			point = loadTexture("images/number/3.png", renderer);
		}
		else if (number == 4) {
			point = loadTexture("images/number/4.png", renderer);
		}
		else if (number == 5) {
			point = loadTexture("images/number/5.png", renderer);
		}
		else if (number == 6) {
			point = loadTexture("images/number/6.png", renderer);
		}
		else if (number == 7) {
			point = loadTexture("images/number/7.png", renderer);
		}
		else if (number == 8) {
			point = loadTexture("images/number/8.png", renderer);
		}
		else if (number == 9) {
			point = loadTexture("images/number/9.png", renderer);
		}
		else {
			point = loadTexture("images/number/0.png", renderer);
		}
		score_b.x = 270 - 12 * len + i * 25;
		SDL_RenderCopy(renderer, point, NULL, &score_b);
		SDL_DestroyTexture(point);
		point = NULL;
	}

	bestscore = max(score, bestscore);

	string x = to_string(bestscore);
	len = x.length();
	SDL_Texture* best;
	for (int i = 0; i < len; i++) {
		char number = x[i] - '0';
		if (number == 1) {
			best = loadTexture("images/number/1.png", renderer);
		}
		else if (number == 2) {
			best = loadTexture("images/number/2.png", renderer);
		}
		else if (number == 3) {
			best = loadTexture("images/number/3.png", renderer);
		}
		else if (number == 4) {
			best = loadTexture("images/number/4.png", renderer);
		}
		else if (number == 5) {
			best = loadTexture("images/number/5.png", renderer);
		}
		else if (number == 6) {
			best = loadTexture("images/number/6.png", renderer);
		}
		else if (number == 7) {
			best = loadTexture("images/number/7.png", renderer);
		}
		else if (number == 8) {
			best = loadTexture("images/number/8.png", renderer);
		}
		else if (number == 9) {
			best = loadTexture("images/number/9.png", renderer);
		}
		else {
			best = loadTexture("images/number/0.png", renderer);
		}
		best_s.x = 270 - 12 * len + i * 25;
		SDL_RenderCopy(renderer, best, NULL, &best_s);
		SDL_DestroyTexture(best);
		best = NULL;
	}
}