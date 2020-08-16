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
	static constexpr Color wingColor = Colors::Red;
	static constexpr Color color = Colors::White;
	static constexpr float wingWidth = 10.0f;
	static constexpr float speed = 300.0f;
	// paddle rebound 동작 제어 변수
	static constexpr float maximumExitRatio = 2.6f; // paddle 끝에 충돌시 ball이 rebound 되는 최대 각도 제어(vector y값(1)에 대해 x값의 비율을 얼마나 줄것인가)
	static constexpr float fixedZoneWidthRatio = 0.2f; // 아래 fixedZoneHalfWidth를 제어하는 값.(paddle 길이에 따라 zone width를 dynamic 하게 설정하기 위함)
	// -----------------------------------------------
	float halfWidth;
	float halfHeight;
	// paddle rebound 동작 제어 변수들에 의해 계산되는 값들
	float exitXFactor; // ball 충돌시 direction 값 설정을 위한 scale factor
	float fixedZoneHalfWidth; // ball 가운데 충돌시 수직으로 튕겨져 나가는 것을 방지하기 위한 값.
						      // 가운데 충돌할 경우 ball과 paddle의 x 위치가 같으므로 수직으로 튕김. 따라서 대신 이 값을 사용.
	float fixedZoneExitX;
	// -----------------------------------------------
	Vec2 pos;
	bool isCooldown = false;
};