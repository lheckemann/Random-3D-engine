// Standard Library and library includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

// Engine includes
#include "defines.h"

// Game includes
#include "events.h"
#include "swarmer.h"
#include "gl_setup.h"
#include "misc.h"

#define MAX_SWARMERS 4096

bool set_up = false;

Swarmer swarmers [MAX_SWARMERS];

void generic_setup() {
	extern GLubyte colours [MAX_SWARMERS * 6];
	extern GLint indices [MAX_SWARMERS * 2];
	for (int i = 0; i < MAX_SWARMERS; i++) {
		colours[i*6] = 255;
		colours[i*6+1] = 0;
		colours[i*6+2] = 0;
		colours[i*6+3] = 0;
		colours[i*6+4] = 0;
		colours[i*6+5] = 0;
		indices[i] = i;
	}
	srand(time(0));
	for (int i = 0; i < MAX_SWARMERS; i++) {
		clear_swarmer(swarmers[i]);
	}
	for (int i = 0; i < 2048; i++) {
		swarmers[i].x = 0;
		swarmers[i].y = 0;
		swarmers[i].live = true;
		update_swarmer(swarmers[i], 0, 0, 0);
	}
}

void update(communicator &State) {
	if (!set_up) {
		set_up = true;
		generic_setup();
		gl_setup();
	}
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		handle(e, State);
	}
	int mx, my;
	Uint8 ms = SDL_GetMouseState(&mx, &my);
	for (int i = 0; i < MAX_SWARMERS; i++) {
		if (!swarmers[i].live) break;
		update_swarmer(swarmers[i], mx, my, ms);
	}
}


GLubyte colours [MAX_SWARMERS * 6];
GLint indices [MAX_SWARMERS * 2];
void draw() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat coords [MAX_SWARMERS * 4];
	int extent;
	for (int i = 0; i < MAX_SWARMERS; i++) {
		if (!swarmers[i].live) {
			extent = i;
			break;
		}
		coords[i*4] = swarmers[i].x;
		coords[i*4+1] = swarmers[i].y;
		coords[i*4+2] = swarmers[i].x2;
		coords[i*4+3] = swarmers[i].y2;
	}
/*	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, coords);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colours);
	glDrawElements(GL_LINES, extent, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);*/
	glBegin(GL_LINES);
	for (int i = 0; i < MAX_SWARMERS; i++) {
		if (!swarmers[i].live) break;
		glColor3ub(255, 0, 0);
		glVertex2f(swarmers[i].x, swarmers[i].y);
		glColor3ub(0, 0, 0);
		glVertex2f(swarmers[i].x2, swarmers[i].y2);
	}
	glEnd();
}
