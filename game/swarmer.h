#ifndef SWARMER_H
#define SWARMER_H

#include "misc.h"

#define SWARMER_SPEED 4
#define SWARMER_LENGTH 40

typedef struct {
	float x, y, x2, y2;
	bool live;
} Swarmer;

void update_swarmer(Swarmer&, int, int, Uint8);
void clear_swarmer(Swarmer&);
#endif
