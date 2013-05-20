#include <cmath>
#include <cstdlib>
#include <SDL.h>

#include "swarmer.h"
#include "misc.h"

void update_swarmer(Swarmer &swarmer, int mx, int my, bool repel) {
	if (!swarmer.live) return;
	float diffx = mx - swarmer.x;
	float diffy = my - swarmer.y;
	float total_diff = 0;

	total_diff = sqrt(diffx*diffx + diffy*diffy); // Pythagoras...

	if (total_diff == 0) return;
	if (!repel) {
		swarmer.x += ((diffx / total_diff) * SWARMER_SPEED * (total_diff*total_diff+4000) / 5000.0 + rand() % 1000 / 4000.0 - 0.125) * speed;
		swarmer.y += ((diffy / total_diff) * SWARMER_SPEED * (total_diff*total_diff+4000) / 5000.0 + rand() % 1000 / 4000.0 - 0.125) * speed;
		swarmer.x2 = swarmer.x - (diffx / total_diff) * SWARMER_LENGTH;
		swarmer.y2 = swarmer.y - (diffy / total_diff) * SWARMER_LENGTH;
	}
	else {
		swarmer.x -= ((diffx / total_diff) * SWARMER_SPEED / (total_diff + 0.64) * 380 + rand() % 1000 / 4000.0 - 0.125) * speed;
		swarmer.y -= ((diffy / total_diff) * SWARMER_SPEED / (total_diff + 0.64) * 380 + rand() % 1000 / 4000.0 - 0.125) * speed;
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
