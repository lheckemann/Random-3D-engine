#include <GL/gl.h>
#include <SDL/SDL.h>

#include "projection.h"

void gl_setup() {
	const SDL_VideoInfo *i = SDL_GetVideoInfo();
	float w = i -> current_w;
	float h = i -> current_h;
	adjust_projection(w, h);

	glClearColor(0.5, 0.5, 0.5, 0.);
	glPointSize(10);
	glLineWidth(2);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}
