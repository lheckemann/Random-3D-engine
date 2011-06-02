#ifndef STAR_H
#define STAR_H

class Star {
	private:
		GLubyte r, g, b;
		GLfloat x, y, z;
	public:
		void generate();
		void draw();
		Star();
		~Star();
};
#endif
