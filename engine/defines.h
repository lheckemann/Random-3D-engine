#ifndef DEFINES_H
#define DEFINES_H
#define FPS 63.0 // Set a bit higher so that the FPS should average 60.
#include <SDL.h>

typedef struct {
	bool running;
	SDL_Surface* Display;
} communicator;

extern communicator State;

#endif
