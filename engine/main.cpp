#include <SDL/SDL.h>
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "error.h"
#include "timing.h"
#include "defines.h"
#include "game_prototype.h"
#include <cstdio>

void setup_GL();

int main(int argc, char* argv[]) {
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		error("Failed to init SDL");
		return -1;
	}
	if((State.Display = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE)) == NULL) {
		error("Failed to set up display");
		return -1;
	}
	int lastUpdate = 0;
	int now = 0;
	float currentfps;
	FILE *log;
	int lastFPS;
	setup_GL();
	log = fopen("3dengine.log", "w");
	
	State.running = true;
	while (State.running) {
		now = SDL_GetTicks();
		if (now > lastUpdate + 1000.0/FPS) {
			if (now > lastFPS + 10000) {
				lastFPS = now;
				currentfps = 1000.0/(now - lastUpdate);
				fprintf(log, "%f FPS\n", currentfps);
			}
			update(State);
			draw();
			SDL_GL_SwapBuffers();
			lastUpdate = now;
		}
		SDL_Delay(1);
	}
	fclose(log);
	return 0;
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
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
