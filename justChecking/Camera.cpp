#pragma once

#include "Camera.h"
#include <gl/glut.h>
#include <math.h>
#include "Vec_3D.h"
#include "DataModel.h"
#include "stdio.h"

#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)

//this camera is inspired by http://www.gamedev.net/page/resources/_/technical/math-and-physics/a-simple-quaternion-based-camera-r1997 tutorial




Camera::Camera(void)
{
	//reset to default values 

	this->pos = Vec3d(-10, 4, -23);

	this->viewDirection = Vec3d(0, 0, 1);

	this->up = Vec3d(0, 1, 0);

	this->right = Vec3d(1, 0, 0); //right = cross(view,up)
	//right(1.0, 0.0, 0.0);


	//To Remove: angleX, angleY, angleZ = 0;
}

//deconstructor
Camera::~Camera(void)
{

}

void Camera::look(void)
{
	Vec3d viewPoint = this->pos + this->viewDirection;

	gluLookAt((GLdouble)this->pos.x, (GLdouble) this->pos.y, (GLdouble) this->pos.z,
		(GLdouble)viewPoint.x, (GLdouble)viewPoint.y, (GLdouble)viewPoint.z,
		(GLdouble) this->up.x, (GLdouble) this->up.y, (GLdouble)this->up.z);

	//for debugging:
	//printf("\n posx=%f , posy=%f , posz =%f \n,viewx=%f ,viexY=%f,viewZ =%f, \n upx = %f, upy = %f, upz = %f \n", this->pos.x, this->pos.y, this->pos.z,
	//	viewPoint.x, viewPoint.y, viewPoint.z,
	//	this->up.x, this->up.y, this->up.z);

}



//The rotation is around a vector(x,y,z) using the quaternion math.
// occured on Rotation axis, with that math: NewVector= R*V*R' , where R' is the conjucate vector
//each R mult is getting a , and it's done on 4 dim space..
//angle must be a radian...
void Camera::RotateAroundQuaternion(double Angle, double x, double y, double z)

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


	result = mult(qRotationVector,mult( qViewTemp, conjugate(qRotationVector)));  //The core of the Rotation  R*V*R'
																				   //the order is  not important-according to associative!


	//now build a rotation matrix, and then 
	this->viewDirection.x = result.x;
	this->viewDirection.y = result.y;
	this->viewDirection.z = result.z;

}


//This function control the position of the camera according to the direction.
void Camera::move(Direction dir)
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
		pos += (right*delta);
		break;
	case RIGHT:
		pos += (right*delta*-1);
		break;
	case FORWARD:
		this->pos = this->pos + (viewDirection*delta);
		break;
	case BACKWARD:
		this->pos = this->pos + (viewDirection*-1*delta);
		break;
	default:
		break;
	}

}



//just initialize the camera values --- maybe not be necessary at the end..
void Camera::setValues(Vec3d newPos, Vec3d newView, Vec3d newUp) //,double positionX,double positionY,double positionZ,double viewX,double viewY,double viewZ,double UpX,double upY,double upZ)
{

	this->pos.x = newPos.x;
	this->pos.y = newPos.y;
	this->pos.z = newPos.z;
	this->viewDirection.x = newView.x;
	this->viewDirection.y = newView.y;
	this->viewDirection.z = newView.z;
	this->up.x = newUp.x;
	this->up.y = newUp.y;
	this->up.z = newUp.z;


	//gluLookAt(positionX,positionY,positionZ,viewX,viewY,viewZ,UpX,upY,upZ);

}


//The objective of the function is to spin the camera around the camera that is pointing.
//using quaternions vectors.
//params: deltaX =mouse-x axis ,  deltaY= mouse-Y axis
//X axis positive = right  ; Y axis positiv = down  the sceren
//The function is inspied concisely by this site:
//http://www.gamedev.net/page/resources/_/technical/math-and-physics/a-simple-quaternion-based-camera-r1997
void Camera::changeViewDirection(float deltaX, float deltaY)
{

	//printf("x:%f ,y:%f \n",deltaX,deltaY); //for debug usage




	Vec3d tmp = this->viewDirection -this->pos;
	Vec3d Axis= tmp.cross(tmp,this->up); //actually this is (view-pos)x up
	Axis.normalize();
	RotateAroundQuaternion(deltaY, Axis.x, Axis.y, Axis.z);
	RotateAroundQuaternion(deltaX, 0, 1, 0);

	this->right = (right.cross(viewDirection, up)*-1);
	//	printf("Mousedir : Axis.x=%f , Axis.y=%f , z=%f \n", Axis.x, Axis.y, Axis.z); //for debug

}

