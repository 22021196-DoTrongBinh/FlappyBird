#include"lib.h"
#include"utils.h"
#include"bird.h"
#include"pipe.h"
#include"background.h"
#include"sound.h"

using namespace std;

const short int FPS = 60;
const short int frameDelay = 1000 / FPS;
int mouse_x, mouse_y;

SDL_Event e;
bool play = false;
bool die = false;
bool replay = false;
bool music = false;

BACKGROUND background;
PIPE pipe;
BIRD bird;
LIB lib;
SOUND sound;

void checkReplay();
void restart();
void gameover();
bool score();
void intro();
bool bulletCollision();

int main(int argc, char* argv[]) {
	Uint32 frameStart;
	short int frameTime;
	srand(time(0));

	initSDL(lib.window, lib.renderer, lib.SCREEN_WIDTH, lib.SCREEN_HEIGHT, "Flappy Bird");
	pipe.init();
	sound.init();

	while (!(SDL_PollEvent(&e) != 0 && (e.type == SDL_QUIT))) {
		SDL_RenderClear(lib.renderer);
		frameStart = SDL_GetTicks();
		if (!die) {
			background.render();
			pipe.render();
			bird.render();
			if (e.type == SDL_MOUSEBUTTONDOWN || (e.type == SDL_KEYDOWN &&
				(e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) && e.key.repeat == 0)) {
					play = true;
			}

			if (play == true) {
				pipe.score_render();
				pipe.update();
				if (score()) {
					pipe.score++;
					sound.point();
				}
				if (e.type == SDL_MOUSEBUTTONDOWN || (e.type == SDL_KEYDOWN &&
					(e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) && e.key.repeat == 0)) {
					sound.flap();
					bird.time = 0;
				}
				bird.update();
				
				if ((bird.birdPos.x + lib.BIRD_WIDTH > pipe.pipePos.x && bird.birdPos.x < pipe.pipePos.x + lib.PIPE_WIDTH
					&& ((bird.birdPos.y + lib.BIRD_HEIGHT + 5 > pipe.pipePos.y - pipe.piranha_height) || bird.birdPos.y - 5 < pipe.pipePos.y - lib.PIPE_SPACE - pipe.piranha_height))
					|| bird.birdPos.y + lib.BIRD_HEIGHT + 5 >= lib.BACKGROUND_HEIGHT || bulletCollision()) {
						sound.hit();
						die = true;
						sound.die();
				}
			}
			else {
				intro();
				if (music == false) {
					sound.intro();
					music = true;
				}
			}
		}
		else {
			bird.wing = 0;
			background.render();
			pipe.render();
			bird.render();
			bird.update();
			gameover();

			checkReplay();
			if (replay == true) {
				restart();
				sound.swosh();
			}
		}
		SDL_RenderPresent(lib.renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	sound.free();
	quitSDL(lib.window, lib.renderer);
	return 0;
}

void checkReplay() {
	SDL_Texture* replay_texture = loadTexture("images\\restart.jpg", lib.renderer);
	SDL_Rect replay_r;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (mouse_x >= 195 && mouse_x <= 345 && mouse_y >= 450 && mouse_y <= 504) {
		replay_r = { 182, 445, 175, 63 };
		if (e.type == SDL_MOUSEBUTTONDOWN)	replay = true;
	}
	else {
		replay_r = { 195, 450, 150, 54 };
	}
	SDL_RenderCopy(lib.renderer, replay_texture, NULL, &replay_r);
	SDL_DestroyTexture(replay_texture);
}

void restart() {
	die = false;
	play = false;
	replay = false;
	music = false;
	pipe.restart();
	bird.restart();
	sound.restart();
}

void gameover() {
	SDL_Texture* gameover_texture = loadTexture("images\\gameover.png", lib.renderer);
	SDL_Texture* score_t = loadTexture("images\\score.png", lib.renderer);
	SDL_Rect gameover_rect = {90 ,100 , 360, 100};
	SDL_Rect score_r = { 210, 210, 120, 160 };
	SDL_RenderCopy(lib.renderer, gameover_texture, NULL, &gameover_rect);
	SDL_RenderCopy(lib.renderer, score_t, NULL, &score_r);
	SDL_DestroyTexture(gameover_texture);
	SDL_DestroyTexture(score_t);
	pipe.scoreAndBest();
}

bool score() {
	if (pipe.pipePos.x < 135) {
		return true;
	}
	return false;
}

void intro() {
	SDL_Texture* getready_texture = loadTexture("images\\getready.png", lib.renderer);
	SDL_Texture* flappybird_texture = loadTexture("images\\flappybird.png", lib.renderer);
	SDL_Rect getready_r = { 90, 210, 360, 218 };
	SDL_Rect flappybird_r = { 90, 50, 360, 120 };
	SDL_RenderCopy(lib.renderer, getready_texture, NULL, &getready_r);
	SDL_RenderCopy(lib.renderer, flappybird_texture, NULL, &flappybird_r);
	SDL_DestroyTexture(getready_texture);
	SDL_DestroyTexture(flappybird_texture);
}

bool bulletCollision() {
	if (bird.birdPos.x + lib.BIRD_WIDTH > pipe.bulletPos.x && bird.birdPos.x < pipe.bulletPos.x + 58 &&
		bird.birdPos.y + lib.BIRD_HEIGHT + 5 > pipe.bulletPos.y && bird.birdPos.y < pipe.bulletPos.y + 48)	return true;
	return false;
}