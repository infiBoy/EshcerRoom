#pragma once
#include "Vec_3d.h"
#include "DataModel.h"
#include <GL/glut.h>



class Camera
{
public:
	Camera(void);
	~Camera(void);
	void setValues(Vec3d newPos, Vec3d newView, Vec3d newUp);

	//Transformation

	void move(Direction dir);

	//change view funcitons:
	void changeViewDirection(float deltaX, float deltaY);
	void rotatebyMouse(Vec3d oldPosition, Vec3d newPosition);
	void RotateAroundQuaternion(double Angle, double x, double y, double z);

	void look();

public:

	Vec3d viewDirection; // the view vector is actually summation of (Position +viewDirection)
	Vec3d right; //it's actually the cross between :view and up vector.
	Vec3d up;
	Vec3d pos;


	//helpful functions
	//GLfloat angleX, angleY, angleZ;



private:

	//double rotAngle;
	//float mouseSensetivity = 5;  //toRemove


};

