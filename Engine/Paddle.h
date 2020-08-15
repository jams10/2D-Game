#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Wall.h"

class Paddle
{
public:
	Paddle( const Vec2& pos_in, float halfWidth_in, float halfHeight_in );
	void Draw( Graphics& gfx )const;
	bool DoBallCollision( Ball& ball ); // When the ball collides with pad, only changes ball's statements
	void DoWallCollision( const Wall& wall ); // Check if the pad is outside of the wall
	void Update( const Keyboard& kbd, float dt );
	RectF GetRect() const;
	void ResetCoolDown();
private:
	static constexpr float wingWidth = 10.0f;
	Color wingColor = Colors::Red;
	Color color = Colors::White;
	float speed = 300.0f;
	float exitXFactor = 0.045f; // ball 충돌시 direction 값 설정을 위한 scale factor
	float fixedZoneHalfWidth = 15.0f; // ball 가운데 충돌시 수직으로 튕겨져 나가는 것을 방지하기 위한 값.
	                                  // 가운데 충돌할 경우 ball과 paddle의 x 위치가 같으므로 수직으로 튕김. 따라서 대신 이 값을 사용.
	float halfWidth;
	float halfHeight;
	Vec2 pos;
	bool isCooldown = false;
};