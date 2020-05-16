#include "Ball.h"
#include "Graphics.h"

void Ball::draw(Graphics& gfx)
{
	for (int i = 0; i < radius; i++)
	{
		for (int j = 0; j < radius; j++)
		{
			gfx.PutPixel(xPos + i, yPos + j, Colors::White);
		}
	}
}