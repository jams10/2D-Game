#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle( const Vec2& pos_in, float halfWidth_in, float halfHeight_in );
	void Draw( Graphics& gfx )const;
	bool DoBallCollision( Ball& ball ); // When the ball collides with pad, only changes ball's statements
	void DoWallCollision( const RectF& walls ); // Check if the pad is outside of the wall
	void Update( const Keyboard& kbd, float dt );
	RectF GetRect() const;
	void ResetCoolDown();
private:
	static constexpr float wingWidth = 10.0f;
	Color wingColor = Colors::Red;
	Color color = Colors::White;
	float speed = 300.0f;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
	bool isCooldown = false;
};