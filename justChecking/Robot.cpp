#include "Robot.h"



#include "Robot.h"
#include "stdio.h"
#include <GL\glut.h>
#include "DataModel.h"
#define degree 0.0174532925  //1degree = (2pi / 360)radian 
#include <math.h>
const Vec3d robotEyeOffset = Vec3d(0, 4.5, 0);  //Vec3d(0.5,4,-2);


#define PI 3.14159265358979323846264


//Constructor to initiliaze the values
Robot::Robot()
{

	//reset to default values 

	robot_Pos         =			 Vec3d(-7, 1.3, 32);   //this shouldn't be hard-coded , it's need to be able take those values in the arguments of the constructors
	viewDirection     =			 Vec3d(0, 0, 1);
	viewHeadDirection =			 Vec3d(0, 0, -1);
	up				  =			 Vec3d(0, 1, 0);
	right			  =			(right.cross(viewDirection, up)*-1);
	//right.x = -4; //right.y = 0; 	//right.z = -15;
}



void Robot::draw()
{
	GLfloat rotateAngle = (GLfloat)viewDirection.convertViewVectorToAngle(Vec3d(0, 0, 1) );

	//draw the body and the Head
	glPushMatrix();

	glPushMatrix();

	glColor3f(1.0, 1.0, 0.0);

	glTranslatef(this->robot_Pos.x, this->robot_Pos.y, this->robot_Pos.z); // Place the robot on the the x-z board


	glRotatef(rotateAngle, 0, 1, 0);		//move the robot according to user request
											//need to be computed from the view direction :)
	glPushMatrix();

	//This is the Head
	glPushMatrix();
	glTranslatef(0, 2.5, 0);
	glRotatef(-this->headYAngle, 0, 1, 0);
	glRotatef(-this->headXAngle, 1, 0, 0);
	//glTranslatef(0, -0.0, 0);
	glutSolidSphere(1.0, 10, 10);

	glColor3f(0.0, 1, 0); //the color of eyes..

	glPushMatrix();  //Eye
	glTranslatef(0.3, 0.5, -0.8);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();

	glPushMatrix();  //Eye
	glTranslatef(-0.6, 0.5, -0.8);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();

	glPopMatrix();

	//This is the Body
	glPushMatrix();
	glColor3f(0.5, 0.9, 0.0);
	glutSolidCube(3.0);
	glPopMatrix();

	glTranslatef(2.0, 1.0, 0);
	glRotatef(90, 0.0, 1, 0.0);


	//The Left hand of the robot
	/****************/
	/*Draw robot arm*/
	/****************/

	glColor3f(0.8, 0.1, 0.0);
	//draw shoulder
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef((GLfloat)this->shoulderAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//draw elbow
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)this->elbowAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//one plier

	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)this->wristAngle, 0.0, 0.0, 1.0);
	glRotatef(45 - this->plierAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//Second plier

	glTranslatef(-1.0, 0.0, 0.0);

	glRotatef(-90 + 2 * this->plierAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();


	glPopMatrix();

	//The legs
	glPushMatrix();
	glTranslatef(0, -3, -1);
	glScalef(1, 2, 1);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidCube(1.0);

	glTranslated(0, -0.6, 0);     //The feet
	glColor3f(0.0, 0.0, 0.5);
	glutSolidSphere(0.3, 10, 10);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	glTranslatef(0, -3, -3);
	glScalef(1, 2, 1);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidCube(1.0);

	glTranslated(0, -0.6, 0);     //The second feet
	glColor3f(0.0, 0.0, 0.5);
	glutSolidSphere(0.3, 10, 10);
	glPopMatrix();



	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();

	glPopMatrix();



}


//rotate the head up and down according to angle
void Robot::rotateHeadUPDOWN(int angle)
{
	this->headXAngle = (this->headXAngle + angle) % 360;
	//restrict the head movement to 60 degree


	if (headXAngle > 60)
		headXAngle = 60;
	if (headXAngle < -60)
		headXAngle = -60;


	viewHeadDirection.y = -sin(headXAngle* PI / 180);

	//convert also the  Head view vector according 
}

//rotate the head to the sides (left , right)
void Robot::rotateHeadToTheSIDES(int angle)
{
	this->headYAngle = (this->headYAngle + angle) % 360;

	//Restrict the head movement to 60 degree
	if (headYAngle > 60)
		headYAngle = 60;
	if (headYAngle < -60)
		headYAngle = -60;

 
	Vec3d temp = viewDirection*-1;
	
	//Rotate also the  Head view vector  in function of the viewDirection
	this->viewHeadDirection.x = (float)(cos(headYAngle*PI / 180)*temp.x - sin(headYAngle*PI / 180)*temp.z);

	this->viewHeadDirection.z = (float)(sin(headYAngle*PI / 180)*temp.x + cos(headYAngle*PI / 180)*temp.z);
	viewHeadDirection.normalize();



}



//move the position robot forward
void Robot::move_forward()
{
	this->robot_Pos += viewDirection*-1;

}


//move the position robot backward
void Robot::move_backward()
{
	this->robot_Pos += viewDirection;

}


//move a side , positive value means move right,
//				negative value means move left
void Robot::move_a_side(float delta)
{
	this->robot_Pos+= (right*delta);


}


//Rotate body according to the angle
void Robot::rotate_body(float angle)
{


	bodyYangle += (int)angle % 360;

	Vec3d temp = this->viewDirection;//this->viewDirection-this->robot_Pos;  // 


	this->viewDirection.x = (float)(cos(angle*PI/180)*temp.x - sin(angle*PI/180)*temp.z);     // perform a rotation matrix around the y -axis
	this->viewDirection.z = (float)(sin(angle*PI/180)*temp.x + cos(angle*PI/180)*temp.z);

	this->viewDirection.normalize();// is it matter? the matrix rotation should be unitary...s

	//Re-compute the right vector for later calculation
	this->right = temp.cross(viewDirection, up)*-1;
	
	

	////// Rotate the head with the body

	temp = viewDirection*-1;
	
	//rotate also the  Head view vector  in function of the viewDirection
	this->viewHeadDirection.x = (float)(cos(headYAngle*PI / 180)*temp.x - sin(headYAngle*PI / 180)*temp.z); // perform a rotation matrix around the y - axis
	this->viewHeadDirection.z = (float)(sin(headYAngle*PI / 180)*temp.x + cos(headYAngle*PI / 180)*temp.z);
	viewHeadDirection.normalize();

}


//Rotate shoulder by an angle
void Robot::rotateShoulder(int angle)
{
	if (angle > 0)
	{
		if (shoulderAngle < 70)//restriction on the angle of rotation
		{
			shoulderAngle = (shoulderAngle + 5) % 360;

		}
	}
	else
	{
		if (shoulderAngle > -70)//restriction on the angle of rotation
		{
			shoulderAngle = (shoulderAngle - 5) % 360;

		}
	}

}
//Rotate the elbow by an angle
void Robot::rotateElbow(int angle)
{

	if (angle > 0)
	{
		if (elbowAngle < 70)//restriction on the angle of rotation
		{
			elbowAngle = (elbowAngle + 5) % 360;

		}
	}
	else
	{
		if (elbowAngle > -70)//restriction on the angle of rotation
		{
			elbowAngle = (elbowAngle - 5) % 360;

		}
	}

}
//Rotate the Wrist by an angle
void Robot::rotateWrist(int angle)
{
	if (angle > 0)
	{
		if (wristAngle < 70)//restriction on the angle of rotation
		{
			wristAngle = (wristAngle + 5) % 360;

		}
	}
	else
	{
		if (wristAngle > -70)//restriction on the angle of rotation
		{
			wristAngle = (wristAngle - 5) % 360;

		}
	}
}
//open the "Pliers" of the robot
void Robot::rotateWristAngle(int angle)
{
	if (angle > 0)
	{
		if (plierAngle < 35)//restriction on the angle of rotation
		{
			plierAngle = (plierAngle + 5) % 360;

		}
	}
	else
	{
		if (plierAngle > -35)//restriction on the angle of rotation
		{
			plierAngle = (plierAngle - 5) % 360;

		}
	}


}

//set the look into the robot eyes
void Robot::look()
{
	Vec3d eyePosition = robot_Pos + robotEyeOffset  ; // compute the position where we look according to the robot position.
	Vec3d center = eyePosition + viewHeadDirection;


	gluLookAt(eyePosition.x	 , eyePosition.y, eyePosition.z,	//make the position exactly at the robot eye
			  center.x		, center.y		, center.z,				//make the direction as the head
			  0				, 1				, 0);					  																	//Up vector


}


