#include "Paddle.h"
#include <cmath>

Paddle::Paddle( const Vec2& pos_in, float halfWidth_in, float halfHeight_in )
	:
	pos(pos_in),
	halfWidth( halfWidth_in ),
	halfHeight( halfHeight_in ),
	exitXFactor( maximumExitRatio / halfWidth ),
	fixedZoneHalfWidth( halfWidth * fixedZoneWidthRatio ),
	fixedZoneExitX( fixedZoneHalfWidth * exitXFactor )
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
			if( std::signbit( ball.GetVelocity().x ) == std::signbit( (ballPos - pos).x ) 
				|| (ballPos.x >= rect.left && ballPos.y <= rect.right) )
			{
				Vec2 dir;
				const float xDifference = ballPos.x - pos.x;
				const float fixedXComponent = fixedZoneHalfWidth * exitXFactor;

				if( std::abs( xDifference ) < fixedZoneHalfWidth ) // 설정한 x 값 범위에 들어올 경우 고정된 각도로 튕겨져 나감.
				{
					if( xDifference < 0.0f ) // paddle 기준 왼쪽에서 접근
					{
						dir = Vec2( -fixedZoneExitX, -1.0f );
					}
					else // paddle 기준 오른쪽에서 접근
					{
						dir = Vec2( fixedZoneExitX, -1.0f );
					}
				}
				else
				{
					dir = Vec2( xDifference * exitXFactor, -1.0f );
				}
				ball.SetDirection( dir );
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

void Paddle::DoWallCollision( const Wall& wall )
{
	const RectF rect = GetRect();
	if( rect.left < wall.GetRect().left )
	{
		pos.x += wall.GetRect().left - rect.left;
	}
	else if( rect.right > wall.GetRect().right )
	{
		pos.x -= rect.right - wall.GetRect().right;
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
