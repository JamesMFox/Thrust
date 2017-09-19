/****************************************************************************************** 
 *	Chili DirectX Framework Version 14.03.22											  *	
 *	Game.cpp																			  *
 *	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
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
#include "Game.h"
#include "Mat3.h"

Game::Game( HWND hWnd,KeyboardServer& kServer,MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer ),
	model("shipd.dxf")
{
}

Game::~Game()
{
}

void Game::Go()
{
	Mat3 m = {1,2,3,4,5,6,7,8,9};
	Mat3 b = {1,0,0,0,2,0,0,0,3};
	Mat3 c = m*b;
	UpdateModel();
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( )
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		angle -= 0.1f;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		angle += 0.1f;
	}
	switch (mouse.ReadMouse().GetType())
	{
	case MouseEvent::WheelUp:
		scale *= 1.13f;
		break;
	case MouseEvent::WheelDown:
		scale /= 1.13f;
		break;
	}
}

void Game::ComposeFrame()
{
	model.Draw({ (float)mouse.GetMouseX(),(float)mouse.GetMouseY() }, angle,scale, gfx);
}
