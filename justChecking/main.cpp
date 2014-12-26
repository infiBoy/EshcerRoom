
//General libraries
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#include "Camera.h"
#include "Lights.h"
#include "Robot.h"
#include "World.h"

#include <GL\glut.h>

#define ShowUpvector


//Libraries that relevant to Open_GL:
#include <GL\glut.h>
#include "SOIL.h"  //library for the textures loader



//Camera 
Camera ghost;

//Room objects:
Robot rbt;
Lights lgt;
World w1;
ControlMode mode;

//Windows parameters
int height = 600; 
int width = 800;
int win1, win2; // Contain the glut number for the window.

//Mouse parameters
bool MouseLeftClicked = false;//control the mouse button state
int lastx = 0;  //keep the last x mouse coordinate
int lasty = 0;  //keep the last y mouse coordinate


//Rotation of the roof degree
int curr_rot = 0;


//This method relevant for  screen down message.
//It's Increase the font of the current Viewpoint
void textToScreen(int x, int y, float r, float g, float b, char *string)
{
	//glEnable(GL_TEXTURE_2D); //added this

	int startMODE;
	int endMODE;
	switch (mode)
	{
	case GHOST:
		startMODE = 59;
		endMODE = 63;
		break;
	case ROBOT:
		startMODE = 65;
		endMODE =69;
		break;
	case LIGHT:
		startMODE = 71;
		endMODE = 75;
		break;
	default:
		break;
	}


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	//glDisable(GL_TEXTURE_2D);
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		if ((i>=startMODE)&&(i<=endMODE))
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}
		else
		{ 
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
		}
		//glColor3f(r, g, b);
	}

	glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);

	//draw a black rectangle on the background of the letters:
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);

	glVertex2f(0, 30);
	glVertex2f(0, 0);
	glVertex2f(760, 0);
	glVertex2f(760, 30);

	glEnd();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();






}

//Callback function that resize the window
void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,400.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
	height = y;
	width = x;

	//width = , height =
}

//The main Display loop to draw the scene
void display(void)
{


	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//switch which viewPoint should we look
	switch (mode)
	{
	case GHOST:
		ghost.look();
		break;
	case ROBOT:
		rbt.look();
		break;
	case LIGHT:
		lgt.look();
		break;
	default:
		break;
	}

	
	rbt.draw(); //draw the robot

	w1.draw();    //draw the world

	lgt.draw();  //make the light on 



					// put Help text on the bottom of the windows
	char string[80] = "Shortcuts: F1-Help , Right Mouse-Setting , SPACE TOGGLE - |GHOST|ROBOT|LIGHT|";	
	textToScreen(0, 10, 0.9, 0.0, 1.0, string);


	
	glFlush();  
	glutSwapBuffers();

}

//A function that draw the help window (while pressing - F1).
void displayHelp(void)

{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	glEnable(GL_TEXTURE_2D);								    // Enable Texture Mapping 


	GLuint texture_help = SOIL_load_OGL_texture
		(
		"Texture/helpme.jpg",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y

		);

	if (texture_help == 0)
		printf("ERRROR::can't load the help descrition!!! Error type:'%s'\n", SOIL_last_result());

	glBindTexture(GL_TEXTURE_2D, texture_help);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);


	//Create the rectangle and the texture on it.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.4f, -1.8f, -5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.4f,1.8f, -5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5f, 1.8f, -5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f, -1.8f, -5.0f);
	
	glEnd();



	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();


}

//Callback function that resize the window of the help window
void handleHelpResize(int w , int h)
{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION),
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);

}


//An handler for the Camera move
void handleSpecialKey(int key, int x, int y)

{

	glLoadIdentity();

	if (mode == GHOST)
	{
		switch (key)
		{

		case GLUT_KEY_UP:   //move forward	
			ghost.move(FORWARD);
			break;
		case GLUT_KEY_DOWN: //move reverse
			ghost.move(BACKWARD);
			break;
		case GLUT_KEY_LEFT: //move left
			ghost.move(LEFT);
			break;
		case GLUT_KEY_RIGHT: //move right
			ghost.move(RIGHT);
			break;
		case GLUT_KEY_HOME:  //move up
			ghost.move(UP);
			break;
		case GLUT_KEY_END: //move down
			ghost.move(DOWN);
			break;


		}


	}
	else if (mode==LIGHT)
	{
		switch (key)
		{

		case GLUT_KEY_UP:   //move forward	
			lgt.move(FORWARD);
			break;
		case GLUT_KEY_DOWN: //move reverse
			lgt.move(BACKWARD);
			break;
		case GLUT_KEY_LEFT: //move left
			lgt.move(LEFT);
			break;
		case GLUT_KEY_RIGHT: //move right
			lgt.move(RIGHT);
			break;
		case GLUT_KEY_HOME:  //move up
			lgt.move(UP);
			break;
		case GLUT_KEY_END: //move down
			lgt.move(DOWN);
			break;


		}


	}


		switch (key)
		{
		case  GLUT_KEY_F1:
			glutSetWindow(win2);
			glutShowWindow();
			glutSetWindow(win1);
			display();
			break;

		}

	




	display();

}

//Keyboard control
void keyDown(unsigned char key, int x, int y)
{
	switch (key) 
	{
 	case ' ':
		mode = (ControlMode)((mode + 1) % 3);
		display();
		break;
	case 27:	
		//ESC
		//PostQuitMessage(0);
		break;

	case 'w':
		rbt.move_forward();
		break;

	case 's':
		rbt.move_backward();
		break;
	case 'a':		
		rbt.move_a_side(-2);
		break;
	case 'd':		
		rbt.move_a_side(2);
		break;


	/*robot Arm control*/
	case 't':
		rbt.rotateShoulder(5);
		break;
	case 'g':
		rbt.rotateShoulder(-5);
		break;
	case 'y':
		rbt.rotateElbow(5);
		break;
	case 'h':
		rbt.rotateElbow(-5);
		break;

	case 'u':
		rbt.rotateWrist(5);
		break;
	case 'j':
		rbt.rotateWrist(-5);
		break;

		//control the angle opening of the robot pilers
	case 'v':
		rbt.rotateWristAngle(5);
		break;
	case 'b':
		rbt.rotateWristAngle(-5);
		break;


		/*^^^robot Body orientations control^^^^^^*/

	case 'e':   //rotate right
		rbt.rotate_body(5);
		display();
		break;
	case 'q': //roate left
		rbt.rotate_body(-5);
		display();
		break;

	
	// Robot head control:

	case 'r': //rotate up
		rbt.rotateHeadUPDOWN(-5);
		display();
		break;
	case 'f': //rotate up
		rbt.rotateHeadUPDOWN(5);
		break;
	case 'z':
		rbt.rotateHeadToTheSIDES(-5);
		break;
	case 'x':
		rbt.rotateHeadToTheSIDES(5);
		break;


	//Ambient Light Control
	case '1':
		//lgt.setlightAmbientColor(0, 0.1);
		lgt.setSpotlightAmbientColor(0, 0.1);  // 0 = RED , + 0.1 amount
		break;
	case '2':
		lgt.setSpotlightAmbientColor(0, -0.1);// 0 = RED , - 0.1 amount
		break;
	case '3':
		lgt.setSpotlightAmbientColor(1, 0.1);  // 0 = GREEN, + 0.1 amount
		break;
	case '4':
		lgt.setSpotlightAmbientColor(1, -0.1);  // 0 = GREEN, - 0.1 amount
		break;
	case '5':
		lgt.setSpotlightAmbientColor(2, 0.1);  // 0 = BLUE, + 0.1 amount
		break;
	case '6':
		lgt.setSpotlightAmbientColor(2, -0.1);  // 0 = BLUE, - 0.1 amount
		break;

	}

	display();


}




//Handle the menu clicked button
void menu(int value)
{
	switch (value)
	{
		//int win2;//decleartaion on window2

	case 1: //adjust the ambient light mod
		printf("Adjust ambient colors amount of the colors Red, Green and Blue:\nThe amount must be in range [0,1]:\n---For example 0.9(R value) 0.3(G value) 0.1(B value) for orange color.\n");
		//printf("Current value are:Red= %f Blue %f Green %f \n", (float)LightAmbientGlobal[0], (float)LightAmbientGlobal[1], (float)LightAmbientGlobal[2]);

		float r, g, b;
		scanf_s("%f%f%f", &r, &g, &b);
		lgt.setAmbientColor(r, g, b);

		break;
	case 2:  //show the help window

		glutSetWindow(win2);
		glutShowWindow();


		break;
	case 3:  // quit
		exit(0);
		break;


	}


}

//create a menu button options
void createMenu(void)

{

	// Create a submenu, this has to be done first.
	int leftclick = glutCreateMenu(menu);  //the handler of this mouse is function:menu

	// Add sub menu entry
	glutAddMenuEntry("adjust ambient light", 1);
	glutAddMenuEntry("help", 2);
	glutAddMenuEntry("quit", 3);


	// Let the menu respond on the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);


}


//Callback function when mouuse clicked
//it's raise a flag for the camera movement to start
void mouseClickFunc(int button, int state, int newMousePosX, int newMousePosY)
{

	if (button == GLUT_LEFT_BUTTON)
	{

		lastx = newMousePosX;
		lastx = newMousePosY;

		MouseLeftClicked = true;
		glutSetCursor(GLUT_CURSOR_NONE);
		if (state == GLUT_UP)
		{
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		}


	}
	else
	{
		MouseLeftClicked = false;
		lastx = newMousePosX;
		lastx = newMousePosY;
	}



}

//Callback function when mouse move
//if it's got a move+clicked event, so we need to change 
//the orientation of our look
void mouseMotion(int newMousePosX, int newMousePosY)
{

	if (MouseLeftClicked == true)
	{


		static double CurrentRotationAboutX = 0.0;

		if ((newMousePosX == lastx) && (newMousePosY == lasty))
			return;

		float deltaX = (newMousePosX - lastx) / -15.0f;  //divide by a  const that control the sensitivity
		float deltaY = (newMousePosY - lasty) / -15.0f;
	

		//constrain the deltas of mouse movement
		if (abs(deltaX) >= 1)
		{
			deltaX = deltaX / (abs(deltaX)); //boud it between [-1,1]
		}
		if (abs(deltaY) >= 1)
		{
			deltaY = deltaY / (abs(deltaY)); //boud it between [-1,1]
		}


		switch (mode)
		{
		case GHOST:
			ghost.changeViewDirection(deltaX, deltaY);
			break;
		case ROBOT:
			break;
		case LIGHT:
			lgt.changeViewDirection(deltaX, deltaY);
			
			break;
		default:
			break;
		}

		lastx = newMousePosX;  //save the new mouse coordinate
		lasty = newMousePosY;

		display();

	}


}


//Timer callback function 
//intent for the roof rotation
void timer(int n)
{
	w1.roofRotational+=5;
	glutSetWindow(win1);
	glutTimerFunc(60, timer, 1);
	display();
}


//Init values
void init_values()

{

	glEnable(GL_DEPTH_TEST); //opengl value for the depth test
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //another values

	mode = GHOST; //initial mode start from the GHOST.


}


//main function - start point of the program
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	win1 = glutCreateWindow("Robot inside 'Escher' room");


	//register to callback functions:
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyDown);
	glutSpecialFunc(handleSpecialKey);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseClickFunc);
	glutDisplayFunc(display);
	glutTimerFunc(20,timer, 1);
	createMenu();  //right click menu


	w1.LoadGLTextures(); //need to be called after the window created



	win2 = glutCreateWindow("Help window");
	//glutSetWindow(win2);
	glutDisplayFunc(displayHelp);
	glutReshapeFunc(reshape);
	glutHideWindow();

	glutSetWindow(win1);
	display();
	glutMainLoop();
	return 0;             
}
