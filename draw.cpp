#include <gl.h>
#include <glu.h>
void draw() {
	glBegin(GL_LINES);
	glVertex2f(-10., 10.);
	glVertex2f(10., -10.);
	glEnd();
}

