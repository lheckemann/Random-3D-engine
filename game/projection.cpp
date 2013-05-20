#include <GL/gl.h>
#include <GL/glu.h>

void adjust_projection(int width, int height) {
	float w = (float) width;
	float h = (float) height;
	float ratio = w/h; // When using gluPerspective
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(0, w, h, 0, 0, 1);
	gluPerspective(45, ratio, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}
