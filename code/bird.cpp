#include"bird.h"
#include"pipe.h"

void BIRD :: render() {
	index_wing += wing;
	if (index_wing >= 4 * wing_speed - 1 || index_wing <= wing_speed + 1)	wing *= -1;
	bird_texture = loadTexture("images\\bird.jpg", renderer);
	SDL_RenderCopyEx(renderer, bird_texture, &bird_rect[index_wing / wing_speed], &bird_rect[0], angle, NULL, SDL_FLIP_NONE);
	SDL_DestroyTexture(bird_texture);
	bird_texture = NULL;
}

void BIRD :: update() {
	if (time == 0)
	{
		angle = -25;
		x0 = bird_rect[0].y;
	}
	else if (angle < 70 && time > 30)
	{
		angle += angleSpeed;
	}
	if (time >= 0)
	{
		bird_rect[0].y = x0 + time * time * 0.21 - 8.4 * time;
		time++;
	}
	if (bird_rect[0].y + BIRD_HEIGHT + 5 > BACKGROUND_HEIGHT) {
		bird_rect[0].y = BACKGROUND_HEIGHT - BIRD_HEIGHT;
		angleSpeed = 0;
	}
	birdPos.getPos(bird_rect[0].x, bird_rect[0].y);
}

void BIRD::restart() {
	bird_rect[0] = { BIRD_START_X, BIRD_START_Y, BIRD_WIDTH, BIRD_HEIGHT };
	angle = 0;
	wing = 1;
	index_wing = 2 * wing_speed;
	angleSpeed = 3;
}