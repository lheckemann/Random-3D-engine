#include <SDL/SDL.h>
#include <gl.h>
#include <glu.h>
#include "defines.h"
#include "game_prototype.h"

#include "event_handler.h"

//#include "swarmer.h"

void update(communicator &State) {
	SDL_Event e;
	float ratio;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			State.running = false;
		}
		if (e.type == SDL_VIDEORESIZE) {
			ratio = ((float) e.resize.w)/e.resize.h;
			glViewport(0, 0, e.resize.w, e.resize.h);
			glMatrixMode(GL_PROJECTION);
			gluPerspective(45, ratio, 0.1, 10000);
			glClearColor(0., 0., 0., 0.);
			glPointSize(2);
			glLineWidth(2);
		}
		if (e.type == SDL_KEYDOWN) {
			handle_key(e.key, State);
		}
	}
}

void cube() {
	GLfloat vertices [] = {
		-1, -1, -1, // 0
		-1, -1,  1, // 1
		-1,  1, -1, // 2
		-1,  1,  1, // 3
		 1, -1, -1, // 4
		 1, -1,  1, // 5
		 1,  1, -1, // 6
		 1,  1,  1  // 7
	};
	GLubyte indices [] = {
		0, 1,
		0, 2,
		0, 4,
	};
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, indices);
	
	glDisableClientState(GL_VERTEX_ARRAY);
}

void draw() {
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(0.0f, 0.0f, -20.0f);
	cube();
}
