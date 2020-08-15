#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball( const Vec2& pos_in, const Vec2& dir_in )
	:
	pos( pos_in )
{
	SetDirection( dir_in );
}

void Ball::Draw( Graphics& gfx ) const
{
	SpriteCodex::DrawBall( pos, gfx );
}

void Ball::Update( float dt )
{
	pos += vel * dt;
}

bool Ball::DoWallCollision( const Wall& wall, Life& life)
{
	bool collided = false;
	const RectF rect = GetRect();
	if( rect.left < wall.GetRect().left )
	{
		pos.x += wall.GetRect().left - rect.left;
		ReboundX();
		collided = true;
	}
	else if( rect.right > wall.GetRect().right )
	{
		pos.x -= rect.right - wall.GetRect().right;
		ReboundX();
		collided = true;
	}
	if( rect.top < wall.GetRect().top )
	{
		pos.y += wall.GetRect().top - rect.top;
		ReboundY();
		collided = true;
	} 
	else if( rect.bottom > wall.GetRect().bottom )
	{
		pos.y -= rect.bottom - wall.GetRect().bottom;
		ReboundY();
		collided = true;
		life.DecreaseLife();
	}
	return collided;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter( pos, radius, radius );
}

Vec2 Ball::GetVelocity() const
{
	return vel;
}

Vec2 Ball::GetPosition() const
{
	return pos;
}

void Ball::SetDirection( const Vec2& dir )
{
	vel = dir.GetNormalized() * speed;
}
