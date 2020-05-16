#pragma once
#include "Graphics.h"

class Paddle
{
public:
	void setX(int z)
	{
		xPos = z;
	}
	int getX()
	{
		return xPos;
	}
	void setY(int z)
	{
		yPos = z;
	}
	int getY()
	{
		return yPos;
	}
	int getWidth() {
		return width;
	}
	void setHeight(int z)
	{
		height = z;
	}
	int getHeight()
	{
		return height;
	}
	void setPlayer(bool z)
	{
		player = z;
	}
	bool getPlayer()
	{
		return player;
	}
	void setScore(int z)
	{
		score = z;
	}
	int getScore()
	{
		return score;
	}

	void draw(Graphics& gfx);

private:
	//functions
	
	

	//variables
	int xPos;
	static constexpr int width = 20;
	int height = 100;
	int yPos = Graphics::ScreenHeight / 2 - Paddle::height / 2;
	bool player; // 1 for p1, 0 for p2
	int score = 0;


};