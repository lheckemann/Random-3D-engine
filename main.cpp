#include <dlfcn.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <gl.h>
#include <glu.h>
#include "error.h"
#include "timing.h"
#include "defines.h"
#include "game_prototype.h"
//#include "logic.h"
//#include "draw.h"


#include <cstdio>

void setup_GL();

int main(int argc, char** argv) {
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		error("Failed to init SDL");
		return -1;
	}
	SDL_Surface* Display;
	if((Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
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
	void (*update)(gamestate&) = NULL;
	char *err;
	lib_handle = dlopen("/tmp/game.so", RTLD_LAZY);
	if (!lib_handle) {
		error("Failed to load game");
		return -1;
	}
	draw = (void(*)()) dlsym(lib_handle, "draw");
	if ((err = dlerror()) != NULL) {
		fprintf(stderr, "Failed some stuff while loading game library. Error message:\n%s\n", err);
		return -1;
	}
	update = (void(*)(gamestate &state)) dlsym(lib_handle, "update");
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

	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, -1, 1);
	glClearColor(0., 1., 1., 0.);
	glPointSize(10);
}
