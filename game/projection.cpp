#include <GL/gl.h>
#include <SDL/SDL.h>



/*void adjust_projection() {
	const SDL_VideoInfo *i = SDL_GetVideoInfo();
	float w = i -> current_w;
	float h = i -> current_h;
//	float ratio = w/h; // When using gluPerspective
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}*/
void adjust_projection(int width, int height) {
//	float ratio = w/h; // When using gluPerspective
	float w = (float) width;
	float h = (float) height;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
