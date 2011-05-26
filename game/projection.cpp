#include <GL/gl.h>
#include <SDL/SDL.h>

void adjust_projection() {
//	float ratio = w/h; // When using gluPerspective
	const SDL_VideoInfo *i = SDL_GetVideoInfo();
	float w = i -> current_w;
	float h = i -> current_h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, w, h, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
