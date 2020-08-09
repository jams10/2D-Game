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
	gfx( wnd ),
	ball( Vec2( 300.0f + 16.0f, 300.0f ), Vec2( -300.0f, -300.0f ) ),
	walls( 0.0f, float( gfx.ScreenWidth ), 0.0f, float( gfx.ScreenHeight ) ),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" ),
	pad( Vec2( 400.0f, 500.0f ), 25.0f, 7.5f )
{
	const Color colors[4] = { Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan };

	const Vec2 topLeft( 40.0f, 40.0f );

	int i = 0;
	for( int y = 0; y < nBricksDown; y++ )
	{
		const Color c = colors[y];
		for( int x = 0; x < nBricksAcross; x++ )
		{
			if( x == 3 && y == 3 )
			{
				bricks[i] = Brick( RectF( 
					topLeft + Vec2( x * brickWidth, y * brickHeight ),
					brickWidth, brickHeight ), c );
			}
			i++;
		}
	}
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
	const float dt = ft.Mark();

	pad.Update( wnd.kbd, dt );
	pad.DoWallCollision( walls );

	ball.Update( dt );

	bool collisionHappened = false;
	float curColDistSq;
	int curColIdx;

	for( int i=0; i<nBricks; i++ )
	{
		if( bricks[i].CheckBallCollision( ball ) ) // 모든 블록들에 대해 collision 체크를 수행
		{
			// ball 과 블록의 거리를 구하고
			const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();

			// ball과의 거리가 가장 짧은 블록을 구함(ball이 블록들 사이에 충돌 했을 때 이를 처리하기 위함)
			if( collisionHappened )
			{
				if( newColDistSq < curColDistSq )
				{
					curColDistSq = newColDistSq;
					curColIdx = i;
				}
			}
			else
			{
				curColDistSq = newColDistSq;
				curColIdx = i;
				collisionHappened = true;
			}
		}
	}

	if( collisionHappened ) // collision 발생 시 collision 후의 작업 수행
	{
		bricks[curColIdx].ExecuteBallCollision( ball );
		soundBrick.Play();
	}

	if( pad.DoBallCollision( ball ) )
	{
		soundPad.Play();
	}

	if( ball.DoWallCollision( walls ) )
	{
		soundPad.Play();
	}
}

void Game::ComposeFrame()
{
	ball.Draw( gfx );
	for( const Brick& b : bricks ) // range-based for loop (loop through every elements)
	{                              // const-> not change values / &-> not copy values
		b.Draw( gfx );
	}
	pad.Draw( gfx );
}
