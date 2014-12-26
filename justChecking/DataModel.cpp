#include "DataModel.h"


//compute the lenght of quaternion vector
double lenght(quaternion quat)
{

	return sqrt(quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w);

}

//normalize the quaternion vector
quaternion normalize(quaternion quat)
{
	double len = lenght(quat);
	quat.x /= len; quat.y /= len;	quat.z /= len;	quat.w /= len;
	return quat;

}

//compute the conjugate
quaternion conjugate(quaternion quat)  //הצמוד
{
	quat.x = -quat.x; quat.y = -quat.y;	quat.z = -quat.z;	//w is scalar (Real)
	//and w = cos(theha/2)
	//
	return quat;

}

//Compute multiplication between two quaternion
//this function is not! commutative
quaternion mult(quaternion A, quaternion B)
{
	quaternion C;
	C.x = A.w*B.x + A.x*B.w + A.y*B.z - A.z*B.y;    //just regular quaternion multiply - used by formula
	C.y = A.w*B.y - A.x*B.z + A.y*B.w + A.z*B.x;	// expand by the formula (w1,x1,y1,z1)*(w2,x2,y2,z2)
	C.z = A.w*B.z + A.x*B.y - A.y*B.x + A.z*B.w;
	C.w = A.w*B.w - A.x*B.x - A.y*B.y - A.z*B.z;
	return C;
}

//return the value that is restrict to range  [min,max]
int restrictValue(int value, int min, int max)
{
	//assume that  max > min

	if (value > max)
		return max;
	if (value < min)
		return min;
	
	return value;

	
}


//return the value that is restrict to range  [min,max]
float restrictValue(float value, float min, float max)
{
	//assume that  max > min
	if (value > max)
		return max;
	if (value < min)
		return min;

	return value;
 

}

