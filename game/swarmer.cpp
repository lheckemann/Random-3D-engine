#include <cmath>
#include <cstdlib>
#include <SDL/SDL.h>

#include "swarmer.h"
#include "misc.h"

void update_swarmer(Swarmer &swarmer, int mx, int my, Uint8 ms) {
	if (!swarmer.live) return;
	float diffx = mx - swarmer.x;
	float diffy = my - swarmer.y;
	float total_diff = 0;
	if (diffx != 0 or diffy != 0) {
		 total_diff = sqrt(diffx*diffx + diffy*diffy); // Pythagoras...
		if (ms & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			swarmer.x += (diffx - total_diff) * SWARMER_SPEED + random();
			swarmer.x += (diffy - total_diff) * SWARMER_SPEED + random();
			swarmer.x2 = swarmer.x - (diffx / total_diff) * SWARMER_LENGTH;
			swarmer.y2 = swarmer.y - (diffy / total_diff) * SWARMER_LENGTH;
		}
		else {
			swarmer.x -= (diffx - total_diff) * SWARMER_SPEED + random();
			swarmer.x -= (diffy - total_diff) * SWARMER_SPEED + random();
			swarmer.x2 = swarmer.x + (diffx / total_diff) * SWARMER_LENGTH;
			swarmer.y2 = swarmer.y + (diffy / total_diff) * SWARMER_LENGTH;
		}
	}
}
