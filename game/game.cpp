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
#include "star.h"
#include "gl_setup.h"

bool set_up = false;

GLuint stars_lst;
void generic_setup() {
	Star s;
	stars_lst = glGenLists(1);
	glNewList(stars_lst, GL_COMPILE);
	glBegin(GL_POINTS);
	for (int i = 0; i<1048576; i++) {
		s.generate();
		s.draw();
	}
	glEnd();
	glEndList();
}

float vX = -10.0, vY = 1.0, vZ = 1.0; // View x, y, z

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
	Uint8 *keystate = SDL_GetKeyState(NULL);
	if (keystate[SDLK_UP]) vX += 1;
	if (keystate[SDLK_DOWN]) vX -= 5;
	if (keystate[SDLK_LEFT]) vY += 0.2;
	if (keystate[SDLK_RIGHT]) vY -= 0.2;
	if (keystate[SDLK_w]) vZ += 0.02;
	if (keystate[SDLK_s]) vZ -= 0.02;
}

void draw() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(vX, vY, vZ, // eye
			  vX+1.0, vY, vZ, // center
			  0.0f, 1.0f, 0.0f); // up
	glScalef(4000, 4000, 4000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCallList(stars_lst);
	glBegin(GL_POINTS);
	glColor3ub(255, 255, 255);
	glVertex3f(0.0, 0.0, 5.0);
	glEnd();
}
