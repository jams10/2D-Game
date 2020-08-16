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

			// signbit : �Ű������� ���� ���̸� true ����.(cmath include �ʿ�.)
			if( std::signbit( ball.GetVelocity().x ) == std::signbit( (ballPos - pos).x ) 
				|| (ballPos.x >= rect.left && ballPos.y <= rect.right) )
			{
				Vec2 dir;
				const float xDifference = ballPos.x - pos.x;
				const float fixedXComponent = fixedZoneHalfWidth * exitXFactor;

				if( std::abs( xDifference ) < fixedZoneHalfWidth ) // ������ x �� ������ ���� ��� ������ ������ ƨ���� ����.
				{
					if( xDifference < 0.0f ) // paddle ���� ���ʿ��� ����
					{
						dir = Vec2( -fixedZoneExitX, -1.0f );
					}
					else // paddle ���� �����ʿ��� ����
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
