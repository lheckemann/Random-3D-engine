#include <SDL/SDL.h>
#include "defines.h"

void update() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			running = false;
		}
		else if (e.type == SDL_KEYDOWN) {
			running = false;
		}
	}
}
