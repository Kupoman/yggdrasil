#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "core/engine.h"
#include "modules/nameexample/name_example_system.h"
#include "modules/assimploader/assimploader.h"
#include "modules/ogrerender/ogrerender.h"


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
		SDL_WINDOW_SHOWN
		);

	if (window == NULL) {
		printf("Failed to create and SDL window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_SysWMinfo wminfo;
	SDL_VERSION(&wminfo.version);

	if (SDL_GetWindowWMInfo(window, &wminfo) == SDL_FALSE) {
		printf("Failed to get WM info: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	unsigned long winhandle = 0;
	if (wminfo.subsystem == SDL_SYSWM_X11)
			winhandle = wminfo.info.x11.window;
	// ToDo support win32 and OS X
	else {
		printf("Unrecognized WM: %d\n", wminfo.subsystem);
		return EXIT_FAILURE;
	}

	{
	Ygg::Engine engine;
	Ygg::AssimpLoaderSystem *loader_system = new Ygg::AssimpLoaderSystem();
	engine.AddSystem(loader_system);
	Ygg::OgreRenderSystem *system = new Ygg::OgreRenderSystem(winhandle, loader_system);
	engine.AddSystem(system);
	loader_system->LoadResource(&engine, "./scene.dae");

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

		engine.Update(0.f);
	}
	}

	/* Free SDL resources */
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
