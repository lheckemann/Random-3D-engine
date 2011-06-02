#include <GL/gl.h>
#include <cstdlib>
#include "star.h"

void Star::generate() {
	r = random() % 128 + 128;
	g = random() % 128 + 128;
	b = random() % 128 + 128;
	x = random() % 8192 / 8192.0;
	y = random() % 8192 / 8192.0;
	z = random() % 8192 / 8192.0;
}
void Star::draw() {
	glColor3ub(r, g, b);
	glVertex3f(x, y, z);
}
Star::~Star() {}
Star::Star() {generate();}
