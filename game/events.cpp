#include <SDL/SDL.h>

#include "defines.h"
#include "gl_setup.h"
#include "projection.h"
#include "misc.h"

void handle_key(SDL_KeyboardEvent &k, communicator &State) {
	if (k.keysym.sym == SDLK_ESCAPE) {
		State.running = false;
	}
}

void handle(SDL_Event &e, communicator &State) {
	if (e.type == SDL_QUIT) {
		State.running = false;
	}
	if (e.type == SDL_VIDEORESIZE) {
		State.Display = SDL_SetVideoMode(e.resize.w, e.resize.h, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_RESIZABLE);
		adjust_projection(e.resize.w, e.resize.h);
	}
	if (e.type == SDL_KEYDOWN) {
		handle_key(e.key, State);
	}
}
