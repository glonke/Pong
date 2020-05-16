#include "Paddle.h"
#include "Graphics.h"

void Paddle::draw(Graphics& gfx)
{
    //draw paddle
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            gfx.PutPixel(xPos + i, yPos + j, Colors::White);
        }
    }

    //draw score
    if (player)
    {

    }
}