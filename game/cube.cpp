#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "defines.h"
#include "game_prototype.h"

#include "event_handler.h"

#include <cstdio>

//#include "swarmer.h"

bool set_up = false;
float xrot = 0, yrot = 0, zrot = 0;

void adjust_size(SDL_Event &e) {
	float ratio = ((float) e.resize.w)/e.resize.h;
	glViewport(0, 0, e.resize.w, e.resize.h);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, ratio, 0.1, 10000);
}

void setup() {
	const SDL_VideoInfo *i = SDL_GetVideoInfo();
	float w = i -> current_w;
	float h = i -> current_h;
	float ratio = ((float) w)/h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, ratio, 0.1, 10000);
	glMatrixMode(GL_MODELVIEW_MATRIX);

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

void update(communicator &State) {
	if (!set_up) {
		set_up = true;
		setup();
	}
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			State.running = false;
		}
		if (e.type == SDL_VIDEORESIZE) {
			adjust_size(e);
		}
		if (e.type == SDL_KEYDOWN) {
			handle_key(e.key, State);
		}
	}
	xrot += 0.3;
	yrot += 0.4;
	zrot += 0.5;
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
	GLubyte colours [] = {
		255, 255, 255, // 0 is white
		255, 255,   0, // 1 is yellow
		255,   0, 255, // 2 is magenta
		  0, 255, 255, // 3 is cyan
		255,   0,   0, // 4 is red
		  0, 255,   0, // 5 is green
		  0,   0, 255, // 6 is blue
		  0,   0,   0  // 7 is black
	};
	GLubyte indices [] = {
		0, 1,
		0, 2,
		0, 4,
		1, 3,
		1, 5,
		2, 6,
		3, 7,
		4, 5,
		6, 7,
		2, 3,
		4, 6,
		7, 5
	};
	GLubyte indices_once [] = {0, 1, 2, 3, 4, 5, 6, 7}; // For drawing as points

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colours);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, indices);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colours);
	glDrawElements(GL_POINTS, 16, GL_UNSIGNED_BYTE, indices_once);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

}

void draw() {
	glColor3ub(255, 255, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glRotatef(zrot, 0, 0, 1);
	cube();
}
