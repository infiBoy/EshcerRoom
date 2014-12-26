
#pragma once

//contains:
//quaternion  +//Usefully Enum's like: Direction,Control mode


static const float delta = 0.95;
#define PI 3.14159265358979323846264
#include <math.h>


enum Direction
{
	UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD
};

enum ControlMode
{

	GHOST, ROBOT,LIGHT
};




//struct of quaternion is just a vector in 4 dimension (x*i+y*j+z*k+w)
//we will represent it like:
struct quaternion
{
	double x, y, z, w;
};

//quaternion functions:
double lenght(quaternion quat);
quaternion normalize(quaternion quat);
quaternion conjugate(quaternion quat);
quaternion mult(quaternion A, quaternion B);