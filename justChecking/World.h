#pragma once 
#include <gl/glut.h>


class World

{

public:
	World();
	void draw();

private:
	void roof();
	void floor();//draw the rotated roof
	void table();//basic table, consist 4 legs.
	void pyramid();
	void cube(int i); //Draw a single cube with texture number i

	void metalValues();


public:
	int LoadGLTextures(); // A function to load an Texture using SOIL library..



private:

	GLuint texture[6]; //Array that's hold the textures

public:
	int roofRotational;

};

