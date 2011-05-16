#include <SDL/SDL.h>
#include "defines.h"

void update(gamestate &State) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			State.running = false;
		}
		else if (e.type == SDL_KEYDOWN) {
			State.running = false;
		}
	}
}

