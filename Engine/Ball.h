#pragma once
#include "Graphics.h"

class Ball
{
public:
	int getX()
	{
		return xPos;
	}
	int getY()
	{
		return yPos;
	}
	void setX(int z)
	{
		xPos = z;
	}
	void setY(int z)
	{
		yPos = z;
	}
	int getRadius()
	{
		return radius;
	}
	float getyVel()
	{
		return yVel;
	}
	float getxVel()
	{
		return xVel;
	}
	void setyVel(int z)
	{
		yVel = z;
	}
	void setxVel(int z)
	{
		xVel = z;
	}
	void setJustBounce(bool z)
	{
		justBounce = z;
	}
	bool getJustBounce()
	{
		return justBounce;
	}

	void draw(Graphics& gfx);

private:
	float xVel, yVel;
	static constexpr int radius = 12;
	int xPos;
	int yPos;
	bool justBounce = false;
};