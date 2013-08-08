#include <SDL/SDL.h>

#include "../engine/defines.h"
#include "gl_setup.h"
#include "projection.h"
#include "misc.h"

extern int width, height;
extern bool exponential, random_enabled;
extern bool trails, random_colours;

void handle_key(SDL_KeyboardEvent &k, communicator &State) {
    switch (k.keysym.sym) {
        case SDLK_ESCAPE: State.running = false; break;
        case SDLK_SPACE: invert_repulsion = !invert_repulsion; break;
        case SDLK_PLUS: case SDLK_EQUALS: case SDLK_KP_PLUS: speed *= 1.2; break;
        case SDLK_MINUS: speed /= 1.2; break;
        case SDLK_e: exponential = !exponential; break;
        case SDLK_r: random_enabled = !random_enabled; break;
        case SDLK_t: trails = !trails; break;
        case SDLK_c: random_colours = !random_colours; break;
        default: break;
    }
}

void handle(SDL_Event &e, communicator &State) {
	if (e.type == SDL_QUIT) {
		State.running = false;
	}
	if (e.type == SDL_VIDEORESIZE) {
    width = e.resize.w;
    height = e.resize.h;
		State.Display = SDL_SetVideoMode(e.resize.w, e.resize.h, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE);
		adjust_projection(e.resize.w, e.resize.h);
	}
	if (e.type == SDL_KEYDOWN) {
		handle_key(e.key, State);
	}
}
