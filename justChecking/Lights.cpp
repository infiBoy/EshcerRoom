#pragma once

#include <stdio.h>


#include "Lights.h"
#include <gl/glut.h>



//directional Light 0 values:
static GLfloat LightAmbientSpot[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //spotlight params RGBA
static GLfloat LightDiffuse[] = { 0.2f, 0.8f, 0.1f, 1.0f };
static GLfloat LightSpecular[] = { 0.0f, 0.5f, 0.0f, 1.0f };


static GLfloat LightAmbientGlobal[] = { 0.7, 0.7, 0.7, 0.0 }; //ambient params RGB


//ambient Light value:
static GLfloat mShininess[] = { 128 }; //set the shininess of the  material



//Constructor - it's should not be hard-coded
Lights::Lights()
{
	pos			  = Vec3d(20, 9, 4);
	viewDirection = Vec3d(-0.8, -0.4, 0.5);
	up			  = Vec3d(0, 1, 0);
	right = right.cross(viewDirection, up);
	ambientLight  = true;
}




//"draw" the lights (ambient +spotlight)
void Lights::draw()
{


	
	glEnable(GL_LIGHTING);
	//glEnable(GL_FLAT);
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE , LightAmbient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mShininess);

	if (ambientLight)
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbientGlobal);
		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbientSpot);
	}


	//Spot light:

	GLfloat LightPosition[] = { (GLfloat)pos.x, (GLfloat)pos.y, (GLfloat)pos.z, 1.0f };
	GLfloat LightDirection[] = { (GLfloat)this->viewDirection.x, (GLfloat)this->viewDirection.y, (GLfloat)this->viewDirection.z };
	glEnable(GL_LIGHT0);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	//values of colors
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbientSpot);		// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);       // Setup The Specular Light
	//setting position.
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);	// Position The Light
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);	// Direction The Light
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);



	//printf("Current ambient value are:Red= %f Blue %f Green %f \n", (float)LightAmbientGlobal[0], (float)LightAmbientGlobal[1], (float)LightAmbientGlobal[2]);  --for debug only


}

//Change the amount of ambient  color
//params: Color = { 1=R, 2=B ,3=G } , amount ={ 0.1 or -0.1}
void Lights::setSpotlightAmbientColor(int color, float amount)
{

	//protect the values of colors to change
	if (amount > 0)
	{

		if (LightAmbientSpot[color] >= 1) /// protect from color to be more than 1;
			return;
	}
	else
	{
		if (LightAmbientSpot[color] <= 0.0) //protect from color to be less than 0;
			return;
	}

	//otherwise add the amount to the ambient color
	switch (color)
	{
	case 0:  //RED
		LightAmbientSpot[0] += amount;
		break;
	case 1:  //GREEN
		LightAmbientSpot[1] += amount;
		break;
	case 2:  //BLUE
		LightAmbientSpot[2] += amount;
		break;

	default:
		break;
	}

}



//control the light moves
void Lights::move(Direction dir)
{
	switch (dir)
	{

	case UP:
		pos += (up*delta);
		break;
	case DOWN:
		pos += (up*-delta);
		break;
	case LEFT:
		pos += (right*-1 * delta);
		break;
	case RIGHT:
		pos += (right*delta);
		break;
	case FORWARD:
		this->pos = this->pos + (viewDirection*delta);
		break;
	case BACKWARD:
		this->pos = this->pos + (viewDirection* delta)*-1;
		break;
	default:
		break;
	}
}



//set the point of view of the light to the screen
void Lights::look()
{
	Vec3d viewPoint = this->pos + this->viewDirection;

	gluLookAt((GLdouble)this->pos.x, (GLdouble) this->pos.y, (GLdouble) this->pos.z,
		(GLdouble)viewPoint.x, (GLdouble)viewPoint.y, (GLdouble)viewPoint.z,
		(GLdouble) this->up.x, (GLdouble) this->up.y, (GLdouble)this->up.z);

	//Debug -remove
	//printf("\n posx=%f , posy=%f , posz =%f \n,viewx=%f ,viexY=%f,viewZ =%f, \n upx = %f, upy = %f, upz = %f \n", this->pos.x, this->pos.y, this->pos.z,
	//	viewPoint.x, viewPoint.y, viewPoint.z,
	//	this->up.x, this->up.y, this->up.z);

}


//This is copy of the camera roation
//The rotation is around a vector(x,y,z) using the quaternion math.
// occured on Rotation axis, with that math: NewVector= R*V*R' , where R' is the conjucate vector
//each R mult is getting a , and it's done on 4 dim space..
//angle must be a radian...
void Lights::RotateAroundQuaternion(double Angle, double x, double y, double z)

{
	quaternion qRotationVector, qViewTemp, result;


	qRotationVector.x = x * sin(Angle / 2);
	qRotationVector.y = y * sin(Angle / 2);
	qRotationVector.z = z * sin(Angle / 2);
	qRotationVector.w = cos(Angle / 2);

	qViewTemp.x = this->viewDirection.x;
	qViewTemp.y = this->viewDirection.y;
	qViewTemp.z = this->viewDirection.z;
	qViewTemp.w = 0;


	result = mult(qRotationVector, mult(qViewTemp, conjugate(qRotationVector)));  //The core of the Rotation  R*V*R'
	//the order is  not important-according to associative!


	//now build a rotation matrix, and then 
	this->viewDirection.x = result.x;
	this->viewDirection.y = result.y;
	this->viewDirection.z = result.z;

}


//The objective of the function is to spin the camera around the camera that is pointing.
//using quaternions vectors.
//params: deltaX =mouse-x axis ,  deltaY= mouse-Y axis
//X axis positive = right  ; Y axis positiv = down  the sceren
//The function is inspied concisely by this site:
//http://www.gamedev.net/page/resources/_/technical/math-and-physics/a-simple-quaternion-based-camera-r1997
void Lights::changeViewDirection(float deltaX, float deltaY)
{



	//printf("x:%f ,y:%f \n", deltaX, deltaY); //for debug usage; 


	Vec3d tmp = this->viewDirection -this->pos;
	Vec3d Axis = tmp.cross(tmp, this->up); //actually this is (view-pos)xup
	Axis.normalize();
	RotateAroundQuaternion(deltaY, Axis.x, Axis.y, Axis.z);
	RotateAroundQuaternion(deltaX, 0, 1, 0);

	this->right = (right.cross(viewDirection, up));
	//printf("Mousedir : Axis.x=%f , Axis.y=%f , z=%f \n", Axis.x, Axis.y, Axis.z);  //for debug

}


//declare teh ambient values
void Lights::setAmbientColor(float red, float green, float blue)
{

	if (red < 0) red = 0;
	if (red > 1) red = 1;
	if (green < 0) green = 0;
	if (green > 1) green = 1;
	if (blue < 0) blue = 0;
	if (blue > 1) blue = 1;

	LightAmbientGlobal[0] = red;
	LightAmbientGlobal[1] = green;
	LightAmbientGlobal[2] = blue;


}









