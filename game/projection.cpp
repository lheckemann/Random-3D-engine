#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <SDL/SDL.h>

extern int clears;
void adjust_projection(int width, int height) {
	float w = (float) width;
	float h = (float) height;

    //	float ratio = w/h; // When using gluPerspective
    
	glPointSize(2);
	glLineWidth(1);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
    clears = 4;
}
