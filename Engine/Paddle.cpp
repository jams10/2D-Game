#include "Paddle.h"
#include <cmath>

Paddle::Paddle( const Vec2& pos_in, float halfWidth_in, float halfHeight_in )
	:
	pos(pos_in),
	halfWidth( halfWidth_in ),
	halfHeight( halfHeight_in )
{
}

void Paddle::Draw( Graphics& gfx )const
{
	RectF rect = GetRect();
	gfx.DrawRect( rect, wingColor ); // Draw full rect
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect( rect, color ); // Draw shortened rect top of original rect
}

bool Paddle::DoBallCollision( Ball& ball )
{
	if( !isCooldown )
	{
		const RectF rect = GetRect();
		if( rect.IsOverlappingWith( ball.GetRect() ) )
		{
			const Vec2 ballPos = ball.GetPosition();

			// signbit : 매개변수가 음의 값이면 true 리턴.(cmath include 필요.)
			if( std::signbit( ball.GetVelocity().x ) == std::signbit( (ballPos - pos).x ) )
			{
				ball.ReboundY();
			}
			else if( ballPos.x >= rect.left && ballPos.x <= rect.right )
			{
				ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}
			isCooldown = true;
			return true;
		}
	}
	return false;
}

void Paddle::DoWallCollision( const RectF& walls )
{
	const RectF rect = GetRect();
	if( rect.left < walls.left )
	{
		pos.x += walls.left - rect.left;
	}
	else if( rect.right > walls.right )
	{
		pos.x -= rect.right - walls.right;
	}
}

void Paddle::Update( const Keyboard& kbd, float dt )
{
	if( kbd.KeyIsPressed( VK_LEFT ) )
	{
		pos.x -= speed * dt;
	}
	if( kbd.KeyIsPressed( VK_RIGHT ) )
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter( pos, halfWidth, halfHeight );
}

void Paddle::ResetCoolDown()
{
	isCooldown = false;
}
