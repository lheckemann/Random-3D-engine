// Standard Library and library includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
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
	for (int i = 0; i<2048; i++) {
		s.generate();
		s.draw();
	}
	glEnd();
	glEndList();
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
}

void draw() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCallList(stars_lst);
	glBegin(GL_POINTS);
	glColor3ub(255, 255, 255);
	glVertex3f(0.0, 0.0, 5.0);
	glEnd();
}
