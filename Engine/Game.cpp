/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
    p1.setX(40);
    p2.setX(gfx.ScreenWidth - 60);
    p1.setPlayer(true);
    p2.setPlayer(false);
    ballRand(false);
}

void Game::Go()
{
    gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    if (scored)
    {
        b1.setX(gfx.ScreenWidth / 2 - b1.getRadius() / 2);
        b1.setY(gfx.ScreenHeight / 2 + b1.getRadius() / 2);
        scored = false;
    }

    updatePaddle(p1);
    updatePaddle(p2);
    updateBall();

}

void Game::ComposeFrame()
{
    p1.draw(gfx);
    p2.draw(gfx);
    b1.draw(gfx);
    drawWalls();
}

void Game::updatePaddle(Paddle& p)
{
    if (p.getPlayer())
    {
        if (wnd.kbd.KeyIsPressed(0x57))
        {
            p.setY(p.getY() - 3);
        }
        else if (wnd.kbd.KeyIsPressed(0x53))
        {
            p.setY(p.getY() + 3);
        }
    }
    else
    {
        if (wnd.kbd.KeyIsPressed(VK_UP))
        {
            p.setY(p.getY() - 3);
        }
        else if (wnd.kbd.KeyIsPressed(VK_DOWN))
        {
            p.setY(p.getY() + 3);
        }
    }

    if (p.getY() < 20)
    {
        p.setY(20);
    }
    else if (p.getY() + p.getHeight() >= gfx.ScreenHeight - 20)
    {
        p.setY(gfx.ScreenHeight - p.getHeight() - 20);
    }
}

void Game::updateBall()
{
    b1.setX(b1.getX() + b1.getxVel());
    b1.setY(b1.getY() + b1.getyVel());

    //ball bouncing off top checks
    if (b1.getY() + b1.getRadius() > gfx.ScreenHeight - 21)
    {
        int yDisp = b1.getY() + b1.getRadius() - (gfx.ScreenHeight - 21);
        b1.setY(gfx.ScreenHeight - 21 - b1.getRadius() - yDisp);
        b1.setyVel(-b1.getyVel());
    }
    else if (b1.getY() < 20)
    {
        int yDisp = 20 - b1.getY();
        b1.setY(20 + yDisp);
        b1.setyVel(-b1.getyVel());
    }
    //ball scoring checks
    else if (b1.getX() <= 0)
    {
        p2.setScore(p2.getScore() + 1);
        b1.setX(gfx.ScreenWidth / 2);
        b1.setY(gfx.ScreenHeight / 2);
    }
    else if (b1.getX() + b1.getRadius() >= gfx.ScreenWidth)
    {
        p1.setScore(p1.getScore() + 1);
        b1.setX(gfx.ScreenWidth / 2);
        b1.setY(gfx.ScreenHeight / 2);
    }
    //ball bouncing off paddle checks
    else if (b1.getX() <= p1.getWidth() + p1.getX() && b1.getX() >= p1.getX() && b1.getY() + b1.getRadius() >= p1.getY() && b1.getY() <= p1.getY() + p1.getHeight())
    {
        ballRand(true);
        b1.setJustBounce(true);
    }
    else if (b1.getX() <= p2.getWidth() + p2.getX() && b1.getX() + b1.getRadius() >= p2.getX() && b1.getY() + b1.getRadius() >= p2.getY() && b1.getY() <= p2.getY() + p2.getHeight())
    {
        ballRand(true);
        b1.setJustBounce(true);
    }
    else if (b1.getJustBounce() == true)
    {
        b1.setJustBounce(false);
    }


}

void Game::drawWalls()
{
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < gfx.ScreenWidth; i++)
        {
            gfx.PutPixel(i, j, Colors::Cyan);
        }
    }

    for (int j = 1; j < 21; j++)
    {
        for (int i = 0; i < gfx.ScreenWidth; i++)
        {
            gfx.PutPixel(i, gfx.ScreenHeight - j, Colors::Cyan);
        }
    }
}

void Game::ballRand(bool paddleBounce) //make it so paddlebounce does not reset xVel
{
    //generate random values != 0
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> xDist(-4, 4);
    std::uniform_real_distribution<float> yDist(-4, 4);
    float xRNG, yRNG;
    do
    {
    xRNG = xDist(rng);
    yRNG = yDist(rng);
    } while (abs(xRNG) < 2 || abs(yRNG) < 1);
    
    //makes sure xVel gets reversed if the ball bounced on the paddle
    if (paddleBounce && b1.getJustBounce())
    {
    }
    else if (paddleBounce)
    {
        if (b1.getxVel() < 0)
        {
            b1.setxVel(abs(xRNG));
        }
        else if (b1.getxVel() > 0)
        {
            b1.setxVel(-abs(xRNG));
        }
        b1.setyVel(yRNG);
    }
    else
    {
        b1.setxVel(xRNG);
        b1.setyVel(yRNG);
    }

}