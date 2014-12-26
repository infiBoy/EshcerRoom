
#include "Vec_3D.h"
#include <math.h>
#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)



//Compute euclidean lenght of the vector from the origing
inline float Vec3d::lenght()
{
	//Vec3d RetVec;
	return sqrtf(((this->x *this->x) + (this->y *this->y) + (this->z *this->z)));
}

//Cross product of vectors
Vec3d Vec3d::cross(Vec3d &temp1, Vec3d &temp2)
{
	Vec3d RetVec;
	RetVec.x = (temp1.y*temp2.z) - (temp1.z*temp2.y);
	RetVec.y = (temp1.z*temp2.x) - (temp1.x*temp2.z);
	RetVec.z = (temp1.x*temp2.y) - (temp1.y*temp2.x);

	return RetVec;

}

//return dot product 
float Vec3d::dot(Vec3d &temp1, Vec3d &temp2)
{
	return (temp1.x*temp2.x + temp1.y*temp2.y + temp1.z*temp2.z);

}

//a.y()*b.z() - a.z()*b.y(),                // 
//a.z()*b.x() - a.x()*b.z(),                // notation
//a.x()*b.y() - a.y()*b.x());


//Simple vector addition
Vec3d &Vec3d::operator+=(const Vec3d& tmp)
{

	this->x = this->x + tmp.x;
	this->y = this->y + tmp.y;
	this->z = this->z + tmp.z;

	return *this;

}

//Simple vector multiplying
Vec3d& Vec3d::operator*=(float tmp)
{
	this->x = this->x * tmp;
	this->y = this->y * tmp;
	this->z = this->z * tmp;
	return *this;

}
//Simple vector multiplying by a scalar
Vec3d Vec3d::operator*(float  tmp)
{

	return Vec3d(this->x*tmp, this->y*tmp, this->z*tmp);
}
//Constructor
Vec3d::Vec3d(float newX, float newY, float newZ)
{
	this->x = newX;
	this->y = newY;
	this->z = newZ;
}

//Another constructor
Vec3d::Vec3d()
{

}

//Simple vector subtraction
Vec3d Vec3d::operator-(const Vec3d tmp1)
{

	return Vec3d(this->x - tmp1.x, this->y - tmp1.y, this->z - tmp1.z);

}

//Normalize vector to make it unit vecotr
void Vec3d::normalize()
{
	float len = this->lenght();
	if (len != 0)
	{
		this->x = this->x / len;
		this->y = this->y / len;
		this->z = this->z / len;
	}
}

//Vector assignment
Vec3d Vec3d::operator=(const Vec3d tmp1)
{
	//return(Vec3d(tmp1.x, tmp1.y, tmp1.z));
	this->x = tmp1.x;
	this->y = tmp1.y;
	this->z = tmp1.z;
	return *this;


}
//Vector addition by a scalar
Vec3d Vec3d::operator+(const Vec3d tmp1)
{

	return Vec3d(this->x + tmp1.x, this->y + tmp1.y, this->z + tmp1.z);

}

//calculate the angle between two vector on X-Z plane.
//using this formula: angle = arctan (sin/cos),while:
// sin = (Vec1 (cross) Vec2)
// cos = (Vec1 (dot) Vec2 )/ ||Vec1|| *||Vec2||
//the function return value in radian in domain[0,PI], so we convert it to angle between 0-360 degree.
float Vec3d::convertViewVectorToAngle(Vec3d &vec2)
{

		Vec3d res_cross= cross(*this, vec2);
		
		float dotDivLength = dot(*this, vec2) / ((*this).lenght() * ((vec2).lenght()));
		
		if (dotDivLength > 1)   //according to calculation that are not accurate
			dotDivLength = 1;
		if(dotDivLength<-1)
			dotDivLength = -1;

		float angle = acosf(dotDivLength);
		angle = angle *180/PI;  //to make it in range [0,180]
		angle *= -1;			//change the angle orientation
		
		if (res_cross.y < 0)    // This is assumption that we make angle of the vector on the X-Z plane
								//that means it in the IV.III quarter  of the perpendicular vector of the cross
			return 360 - angle;
		else
			return angle;
	




}

