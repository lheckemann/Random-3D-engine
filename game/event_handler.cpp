#include <SDL/SDL.h>

void handle_key(SDL_KeyboardEvent &e, communicator &State) {
	if (e.keysym.sym == SDLK_ESCAPE) {
		State.running = false;
	}
}
