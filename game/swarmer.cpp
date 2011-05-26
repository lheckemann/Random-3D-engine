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

	total_diff = sqrt(diffx*diffx + diffy*diffy); // Pythagoras...

//	if (pr) {
//		printf("mx: %i, my: %i, sx: %f, sy: %f\n", mx, my, swarmer.x, swarmer.y);
//		printf("x diff: %f, y diff: %f, total diff: %f\n", diffx, diffy, total_diff);
//	}

	if (total_diff == 0) return;
	if (!(ms & SDL_BUTTON(SDL_BUTTON_LEFT))) {
		swarmer.x += (diffx / total_diff) * SWARMER_SPEED + random() % 1000 / 1000.0;
		swarmer.y += (diffy / total_diff) * SWARMER_SPEED + random() % 1000 / 1000.0;
		swarmer.x2 = swarmer.x - (diffx / total_diff) * SWARMER_LENGTH;
		swarmer.y2 = swarmer.y - (diffy / total_diff) * SWARMER_LENGTH;
	}
	else {
		swarmer.x -= (diffx / total_diff) * SWARMER_SPEED + random() % 1000 / 1000.0;
		swarmer.y -= (diffy / total_diff) * SWARMER_SPEED + random() % 1000 / 1000.0;
		swarmer.x2 = swarmer.x + (diffx / total_diff) * SWARMER_LENGTH;
		swarmer.y2 = swarmer.y + (diffy / total_diff) * SWARMER_LENGTH;
	}
}

void clear_swarmer(Swarmer &swarmer) {
	swarmer.live = false;
	swarmer.x = 0;
	swarmer.y = 0;
	swarmer.x2 = 0;
	swarmer.y2 = 0;
}
