#include <SDL/SDL.h>
#include "defines.h"

void update() {
	SDL_Event current;
	while (SDL_PollEvent(&current)) {
		if (current.type == SDL_QUIT) {
			running = false;
		}
	}
}
