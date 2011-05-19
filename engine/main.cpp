#include <dlfcn.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "error.h"
#include "timing.h"
#include "defines.h"
#include <cstdio>

void setup_GL();

int main(int argc, char** argv) {
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		error("Failed to init SDL");
		return -1;
	}
	SDL_Surface* Display;
	if((Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_RESIZABLE)) == NULL) {
		error("Failed to set up display");
		return -1;
	}
	int lastUpdate = 0;
	int now = 0;
	setup_GL();
	float currentfps;
	FILE *log;
	int lastFPS;
	log = fopen("3dengine.log", "w");
	
	void *lib_handle;
	void (*draw)(void) = NULL;
	void (*update)(communicator&) = NULL;
	char *err;
	char *gamelib_location;
	if (argc == 2) {
		gamelib_location = argv[1];
	}
	else {
		printf("No game file provided. Please provide one at the command line.");
		return -1;
	}
	lib_handle = dlopen(gamelib_location, RTLD_LAZY);
	if (!lib_handle) {
		error("Failed to load game (it is necessary to use ./game.so as opposed to game.so)");
		return -1;
	}
	draw = (void(*)()) dlsym(lib_handle, "draw");
	if ((err = dlerror()) != NULL) {
		fprintf(stderr, "Failed some stuff while loading game library. Error message:\n%s\n", err);
		return -1;
	}
	update = (void(*)(communicator &state)) dlsym(lib_handle, "update");
	if ((err = dlerror()) != NULL) {
		fprintf(stderr, "Failed some stuff while loading game library. Error message:\n%s\n", err);
		return -1;
	}
	
	State.running = true;
	while (State.running) {
		now = SDL_GetTicks();
		if (now > lastUpdate + 1000.0/FPS) {
			if (now > lastFPS + 10000) {
				lastFPS = now;
				currentfps = 1000.0/(now - lastUpdate);
				fprintf(log, "%f FPS\n", currentfps);
			}
			(*update)(State);
			(*draw)();
			SDL_GL_SwapBuffers();
			lastUpdate = now;
		}
		SDL_Delay(1);
	}
	fclose(log);
}

void setup_GL() {
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
}
