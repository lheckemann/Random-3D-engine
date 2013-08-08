#include <cmath>
#include <cstdlib>

#include "swarmer.h"
#include "misc.h"

extern int width, height;
extern bool exponential, random_enabled;



void update_swarmer(Swarmer &swarmer, int mx, int my, bool repel) {
	if (!swarmer.live) return;
	float diffx = mx - swarmer.x;
	float diffy = my - swarmer.y;
	float total_diff = 0;

	total_diff = sqrt(diffx*diffx + diffy*diffy); // Pythagoras...

	if (total_diff == 0) return;
  if (exponential) {
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
  else {
    if (!repel) {
      swarmer.x += ((diffx / total_diff) * SWARMER_SPEED + rand() % 1000 / 1000.0 - 0.5) * speed;
      swarmer.y += ((diffy / total_diff) * SWARMER_SPEED + rand() % 1000 / 1000.0 - 0.5) * speed;
      swarmer.x2 = swarmer.x - (diffx / total_diff) * SWARMER_LENGTH;
      swarmer.y2 = swarmer.y - (diffy / total_diff) * SWARMER_LENGTH;
    }
    else {
      swarmer.x -= ((diffx / total_diff) * SWARMER_SPEED + rand() % 1000 / 1000.0 - 0.5) * speed;
      swarmer.y -= ((diffy / total_diff) * SWARMER_SPEED + rand() % 1000 / 1000.0 - 0.5) * speed;
      swarmer.x2 = swarmer.x + (diffx / total_diff) * SWARMER_LENGTH;
      swarmer.y2 = swarmer.y + (diffy / total_diff) * SWARMER_LENGTH;
    }
  }
  if (swarmer.extra_random && random_enabled) {
    swarmer.x += rand() % 2000 / 100.0 - 10;
    swarmer.y += rand() % 2000 / 100.0 - 10;
  }
  /*while (swarmer.x > width) {
    swarmer.x -= width;
  }
  while (swarmer.x < 0) {
    swarmer.x += width;
  }
  while (swarmer.y > height) {
    swarmer.y -= height;
  }
  while (swarmer.y < 0) {
    swarmer.y += height;
  }*/
}

void clear_swarmer(Swarmer &swarmer) {
	swarmer.live = false;
	swarmer.x = 0;
	swarmer.y = 0;
	swarmer.x2 = 0;
	swarmer.y2 = 0;
}
