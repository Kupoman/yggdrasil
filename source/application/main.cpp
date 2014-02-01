#include <iostream>

#include "SDL2/SDL.h"


int main(int argc, char **argv)
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("Failed to init SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	/* Create an SDL window */
	SDL_Window *window = SDL_CreateWindow(
		"Yggdrasil",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		600,
		SDL_WINDOW_OPENGL /* SDL_WINDOW_OPENGL is required to setup an OpenGL context */
		);

	if (window == NULL) {
		printf("Failed to create and SDL window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Event event;
	int quit = 0;
	while (quit != 1) {
		/* First Check for SDL events */
		while (SDL_PollEvent(&event)) {
			/* Only checking for SDL_QUIT (window close), could check for
			* others to handles things like keyboard input */
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
		}
	}

	/* Free SDL resources */
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}