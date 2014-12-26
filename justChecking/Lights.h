#pragma once

#include "Vec_3d.h"
#include <gl/glut.h>
#include "DataModel.h"
#ifndef Light_h
#define Light_h




//class that contain: 1 spotlight and 1 ambient light
//both can be configure
class Lights
{
public:
	Lights(void);  //constructor - will build the light source.

	void lightAmbientOff();
	void lightAmbientOn();

	//control the color of the lights sources.
	void setSpotlightAmbientColor(int color, float amount);
	void setAmbientColor(float  red, float green, float blue);
	

	//control the position 
	void setLightpotPosition(Vec3d position);
	void move(Direction dir);



	void RotateAroundQuaternion(double Angle, double x, double y, double z);
	void changeViewDirection(float deltaX, float deltaY);

	

	void draw();
	void look();

public:
	bool ambientLight; // 1= on, 0 =off

private:
	Vec3d pos; 
	Vec3d viewDirection; // the view vector is actually summation of (Position +viewDirection)
	Vec3d up;
	Vec3d right;//it's actually the cross between :view and up vector
	
	//light0 position values:
	//int lightPosX, lightPosY, lightPosZ, lightDirX, lightDirY, lightDirZ, lightVol;



};


#endif

