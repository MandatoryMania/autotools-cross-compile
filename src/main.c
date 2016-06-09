#include <config.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int main (int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "ERROR - SDL_INIT: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL){
		fprintf(stderr,"ERROR - SDL_CreateWindow: %s\n",SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		fprintf(stderr, "ERROR - SDL_CreateRenderer: %s\n",SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){
				quit = true;
			}
		}
		//Render the frame
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
