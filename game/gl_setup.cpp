#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <SDL/SDL.h>

#include "projection.h"

void gl_setup() {
	const SDL_VideoInfo *i = SDL_GetVideoInfo();
	int w = i -> current_w;
	int h = i -> current_h;
	adjust_projection(w, h);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LEQUAL);
}
