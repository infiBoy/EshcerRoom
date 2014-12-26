#include "World.h"

#include "SOIL.h"  //library for the textures loader


static GLfloat LightAmbientSpot[] = { 0.0f, 1.0f, 1.0f, 1.0f };


//Gold Metal values (for the teapot)
//those value define how much the color can emit from the teapot
//this according to http://www.real3dtutorials.com/tut00008.php color chart
GLfloat ChromeAmbient[] = { 0.25f, 0.148f, 0.06475f, 1.0f };
GLfloat ChromeDiffuse[] = { 0.4f, 0.2368f, 0.1036f, 1.0f };
GLfloat ChromeSpecular[] = { 0.774597f, 0.458561f, 0.200621f, 1.0f };
GLfloat ChromeShiness[] = { 76.8f };


const int sizecube = 1;  //for the floor

World::World()
{
	roofRotational = 0;
	//LoadGLTextures();
}

//main function of the world class
//draw all the types in the room
void World::draw()
{



	glMatrixMode(GL_MODELVIEW_MATRIX);

	//draw the floor
	glPushMatrix();
	glTranslatef(-30, -3, 0);
	floor();
	glPopMatrix();


	//draw the painting
	glPushMatrix();
	glTranslatef(0, 4, 5);
	glScalef(3, 3, 3);
	glEnable(GL_TEXTURE_2D);
	roof();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	//draw the teapot
	
	glPushMatrix();
	glTranslatef(-20, +1, 6);
	glScalef(0.3, 0.5, 0.3);
	metalValues();
	glutSolidTeapot(2);
	glPopMatrix();


	//draw the table
	glPushMatrix();
	glTranslatef(-20, 0, 6);
	glScalef(0.6, 0.3, 0.3);
	table();
	glPopMatrix();


	//draw the cubes pyramid
	glPushMatrix();
	glTranslatef(0, -1.5, 14);
	pyramid();
	glPopMatrix();
	glPopMatrix();


}

//draw the roof and it's texture
void World::roof()
{
	//To do: check if to remove
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();


		glTranslatef(-3.0f, 0.0f, 1.0f);
		glRotatef(roofRotational, 0.0, 1.0, 0.0);

		glScalef(10, 1, 10);

		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);	 glVertex3f(-1, 3, 0);
			glTexCoord2f(1.0f, 0.0f);	 glVertex3f(0, 3, -1);
			glTexCoord2f(1.0f, 1.0f);	 glVertex3f(1, 3, 0);
			glTexCoord2f(0.0f, 1.0f);	 glVertex3f(0, 3, 1);

		glEnd();


	glPopMatrix();


}

void World::floor()
{

	glMaterialfv(GL_FRONT, GL_AMBIENT, LightAmbientSpot);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);//make the floor shiny

	GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);


	glBegin(GL_QUADS);
	for (int x = 0; x < 50; x++)
		for (int y = 0; y < 50; y++)
		{
			{
				if (((y + x) % 2) == 0) //modulo 2
					glColor3f(1.0f, 1.0f, 1.0f);
				else
					glColor3f(0.0f, 0.0f, 0.0f);


				//draw one tile
				glNormal3f(0, 1, 0); glVertex3f(x*sizecube, 0.5, (y + 1)*sizecube);
				glNormal3f(0, 1, 0); glVertex3f((x + 1)*sizecube, 0.5, (y + 1)*sizecube);
				glNormal3f(0, 1, 0); glVertex3f((x + 1)*sizecube, 0.5, y*sizecube);
				glNormal3f(0, 1, 0); glVertex3f(x*sizecube, 0.5, y*sizecube);

			}


		}
	glEnd();




}

void World::table()
{
	glPushMatrix();

	glColor3f(0.8, 0.4, 0.0); //Brown Table
	//the top
	glPushMatrix();
	glScalef(1.9, 0.5, 3);  //the size of the top
	glutSolidCube(3);
	glPopMatrix();

	glTranslatef(-2, -3.6, -2);
	//construct 4 legs
	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < 2; j++)
		{

			glPushMatrix();
			glTranslatef(i * 4, 0, j * 3);
			glScalef(0.3, 3, 0.3);  //the size of the top

			glutSolidCube(2.9);

			//put it in the 

			glPopMatrix();



		}

	}



	glPopMatrix();

}

void World::pyramid()
{
	glEnable(GL_TEXTURE_2D);

	for (int i = 0; i < 3; i++)
	{
		glTranslatef(-0.8*i, 0, 0);
		for (int j = i; j < 3; j++)
		{
			glPushMatrix();
			glTranslatef(j*2.8, 2 * i, 0);
			cube(i);
			glPopMatrix();

		}

	}





	glDisable(GL_TEXTURE_2D);
}

void World::cube(int i)
{
	glBindTexture(GL_TEXTURE_2D, texture[i]);

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();



}

int World::LoadGLTextures()
{
	/* load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture
		(
		"Texture/escher2.jpg", // 
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	texture[1] = SOIL_load_OGL_texture
		(
		"Texture/escher1.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	//..\Texture\escher3.jpg",
	texture[2] = SOIL_load_OGL_texture
		(
		"Texture/escher3.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[3] = SOIL_load_OGL_texture
		(
		"",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	texture[4] = SOIL_load_OGL_texture
		(
		"Texture/TheRoof.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);



	texture[5] = SOIL_load_OGL_texture
		(
		"Texture/helpme.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y




		);

	if ((texture[0] == 0) || (texture[1] == 0) || (texture[2] == 0) || (texture[3] == 0) || (texture[4] == 0) || (texture[5] == 0))
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR); //using mipmap for antialias
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;                                        // Return Success


}

void World::metalValues()
{

	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ChromeAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ChromeDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ChromeSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, ChromeShiness);


}

