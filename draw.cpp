#include <gl.h>
#include <glu.h>
void draw() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		glVertex2f(0., 0.);
	glEnd();
}

