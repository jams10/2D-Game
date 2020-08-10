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
	wall(RectF(30.0f, float(gfx.ScreenWidth - 30.0f), 30.0f, float(gfx.ScreenHeight - 30.0f)), 5.0f, Colors::Gray),
	wnd( wnd ),
	gfx( wnd ),
	ball( Vec2( 300.0f + 24.0f, 300.0f ), Vec2( -300.0f, -300.0f ) ),
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
			bricks[i] = Brick( RectF( topLeft + Vec2( x * brickWidth, y * brickHeight ), brickWidth, brickHeight ), c);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	// 한번에 60ms 만큼 업데이트 하는 것이 아닌 60ms 시간을 쪼개 2.5ms 만큼의 시간을 계속 소비하여 업데이트.
	// 이를 통해 시뮬레이션이 좀더 많이 update 됨. (같은 시간 동안 simulation 횟수 증가)
	float elapsedTime = ft.Mark(); 
	while( elapsedTime > 0.0f )
	{
		const float dt = std::min( 0.0025f, elapsedTime ); // dt가 2.5ms를 넘지 않도록 설정.
		UpdateModel( dt );
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{

	pad.Update( wnd.kbd, dt );
	pad.DoWallCollision( wall );

	ball.Update( dt );

	bool collisionHappened = false;
	float curColDistSq;
	int curColIdx;

	for( int i=0; i<nBricks; i++ )
	{
		if( bricks[i].CheckBallCollision( ball ) )
		{
			const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();

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

	if( collisionHappened )
	{
		pad.ResetCoolDown();
		bricks[curColIdx].ExecuteBallCollision( ball );
		soundBrick.Play();
	}

	if( pad.DoBallCollision( ball ) )
	{
		soundPad.Play();
	}

	if( ball.DoWallCollision( wall ) )
	{
		pad.ResetCoolDown();
		soundPad.Play();
	}
}

void Game::ComposeFrame()
{
	wall.Draw( gfx );
	ball.Draw( gfx );
	for( const Brick& b : bricks ) // range-based for loop (loop through every elements)
	{                              // const-> not change values / &-> not copy values
		b.Draw( gfx );
	}
	pad.Draw( gfx );
}
