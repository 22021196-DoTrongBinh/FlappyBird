#include"background.h"
#include"utils.h"

void BACKGROUND :: render(){
	background_texture = loadTexture("images\\background2.png", renderer);
	SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
	SDL_DestroyTexture(background_texture);
	background_texture = NULL;
}
