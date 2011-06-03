#include <GL/gl.h>
#include <cstdlib>
#include "star.h"

void Star::generate() {
	r = random() % 64 + 192;
	g = random() % 64 + 192;
	b = random() % 64 + 192;
	x = ((random() % 8192)-4096) / 8192.0;
	y = ((random() % 8192)-4096) / 8192.0;
	z = ((random() % 8192)-4096) / 8192.0;
}
void Star::draw() {
	glColor3ub(r, g, b);
	glVertex3f(x, y, z);
}
Star::~Star() {}
Star::Star() {generate();}
