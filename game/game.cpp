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

bool set_up = false;

Swarmer swarmers [4096]; // Not sure if this may cause RAM problems with bigger numbers...

void generic_setup() {
	srand(time(0));
	for (int i = 0; i<4096; i++) {
		swarmers[i].live = false;
		swarmers[i].x = 0;
		swarmers[i].y = 0;
		swarmers[i].x2 = 0;
		swarmers[i].y2 = 0;
	}
	for (int i = 0; i<100; i++) {
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
	for (int i = 0; i<4096; i++) {
		if (!swarmers[i].live) break;
		update_swarmer(swarmers[i], mx, my, ms);
	}
}

void draw() {
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat coords [16384];
	GLubyte colours [3*4096];
	GLint indices [4096];
	int extent;
	for (int i = 0; i<4096; i++) {
		if (!swarmers[i].live) {
			extent = i;
			break;
		}
		coords[i*4] = swarmers[i].x;
		coords[i*4+1] = swarmers[i].y;
		coords[i*4+2] = swarmers[i].x2;
		coords[i*4+3] = swarmers[i].y2;
		colours[i*6] = 255;
		colours[i*6+1] = 0;
		colours[i*6+2] = 0;
		colours[i*6+3] = 0;
		colours[i*6+4] = 0;
		colours[i*6+5] = 0;
		indices[i] = i;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, coords);
	glColorPointer(3, GL_INT, 0, colours);
	glDrawElements(GL_LINES, extent, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
