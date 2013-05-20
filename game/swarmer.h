#ifndef SWARMER_H
#define SWARMER_H

#include "misc.h"

#define SWARMER_SPEED 2
#define SWARMER_LENGTH 80

typedef struct {
	float x, y, x2, y2;
	bool live;
} Swarmer;

void update_swarmer(Swarmer&, int, int, bool);
void clear_swarmer(Swarmer&);
#endif
