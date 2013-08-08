#ifndef SWARMER_H
#define SWARMER_H

#include "misc.h"
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define SWARMER_SPEED 2
#define SWARMER_LENGTH 30

typedef struct {
	GLfloat x, y, x2, y2;
    GLfloat colour[3];
	bool live;
  bool extra_random;
} Swarmer;

void update_swarmer(Swarmer&, int, int, bool);
void clear_swarmer(Swarmer&);
#endif
