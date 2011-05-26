#include <GL/gl.h>

void adjust_projection(float w, float h) {
//	float ratio = w/h; // When using gluPerspective
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, w, h, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
