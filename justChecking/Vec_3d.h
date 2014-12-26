#pragma once
// a class for regular eulers vectors
class Vec3d
{
public:
	float x, y, z;

public:
	Vec3d();
	Vec3d(float newX, float newY, float newZ);
	Vec3d multiply(Vec3d temp);
	float lenght();
	Vec3d  cross(Vec3d &temp1, Vec3d &temp2);
	float convertViewVectorToAngle(Vec3d &vec2);
	void normalize();


	//overload the following operators to make a good  vector regular operations
	Vec3d& operator += (const Vec3d& tmp);
	Vec3d& operator *= (const float tmp);
	Vec3d operator -(const Vec3d tmp1);
	Vec3d operator =(const Vec3d tmp1);
	Vec3d operator +(const Vec3d tmp1);

	Vec3d operator * (float tmp);
	float dot(Vec3d &temp1, Vec3d &temp2);


};

