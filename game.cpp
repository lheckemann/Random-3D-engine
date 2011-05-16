#include <SDL/SDL.h>
#include "defines.h"

#include "game_prototype.h"

void update(gamestate &State) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			State.running = false;
		}
		else if (e.type == SDL_KEYDOWN) {
			State.running = false;
		}
	}
}

#include <gl.h>
#include <glu.h>
void draw() {
	glColor3ub(0, 0, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		glVertex2f(0., 0.);
	glEnd();
}

