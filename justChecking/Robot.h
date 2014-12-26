#pragma once
#include "Vec_3D.h"


class Robot
{
public:
	Vec3d  robot_Pos;		  // (X,const,Z) position of the robot in the world
	Vec3d  viewDirection;	  // the view vector is actually summation of (Position +viewDirection) of the whole robot
	Vec3d  viewHeadDirection; //the direction of the head that is looking at.
	Vec3d  up;
	Vec3d  right;			  //it's actually the cross between :view and up vector.


private:

	int headXAngle = 0, headYAngle = 0;	//Head  angle

	float bodyYangle;  //Body orientation

	int shoulderAngle = 0, elbowAngle = 0, wristAngle = 0, plierAngle = 0;	//arm angles
	



public:

	Robot();

	void draw();  // the function that draw the robot



	//change his parameters
	void move_forward();
	void move_backward();
	void move_a_side(float delta); // positive means right, negative means left

	void rotate_body(float angle);
	void rotate_right();



	void rotateShoulder(int angle);
	void rotateElbow(int angle);
	void rotateWrist(int angle);
	void rotateWristAngle(int angle); //change the plier angle


	void rotateHeadUPDOWN(int angle);//which dimension to move the 
	void rotateHeadToTheSIDES(int angle);

	//render from the robot point of view
	void look();
};

