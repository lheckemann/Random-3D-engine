#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <gl.h>
#include <glu.h>
#include "error.h"
#include "timing.h"
#include "defines.h"
#include "logic.h"
#include "draw.h"
#include <cstdio>

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
	bool running = true;
	int lastUpdate = 0;
	int now = 0;
	while (running) {
		now = SDL_GetTicks();
		if (now > lastUpdate + 1000/FPS) {
			update();
			lastUpdate = now;
		}
		draw();
	}
}

