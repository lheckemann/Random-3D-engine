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

void set_default_attribs();

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
	set_default_attribs();
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, -1, 1);
	glClearColor(0., 0., 0., 0.);
	glColor3b(255, 255, 255);
	glPointSize(10);
	while (running) {
		now = SDL_GetTicks();
		if (now > lastUpdate + 1000/FPS) {
			update();
			lastUpdate = now;
		}
		draw();
		SDL_GL_SwapBuffers();
		SDL_Delay(10);
	}
}

void set_default_attribs() {
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
