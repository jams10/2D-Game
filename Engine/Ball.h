#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Wall.h"
#include "Life.h"

class Ball
{
public:
	Ball( const Vec2& pos_in, const Vec2& vel_in );
	void Draw( Graphics& gfx )const;
	void Update( float dt );
	bool DoWallCollision( const Wall& wall, Life& life);
	void ReboundX();
	void ReboundY();
	RectF GetRect() const; // Collider
	Vec2 GetVelocity()const;
	Vec2 GetPosition()const;
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};