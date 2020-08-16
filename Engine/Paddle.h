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
	// paddle rebound ���� ���� ����
	static constexpr float maximumExitRatio = 2.6f; // paddle ���� �浹�� ball�� rebound �Ǵ� �ִ� ���� ����(vector y��(1)�� ���� x���� ������ �󸶳� �ٰ��ΰ�)
	static constexpr float fixedZoneWidthRatio = 0.2f; // �Ʒ� fixedZoneHalfWidth�� �����ϴ� ��.(paddle ���̿� ���� zone width�� dynamic �ϰ� �����ϱ� ����)
	// -----------------------------------------------
	float halfWidth;
	float halfHeight;
	// paddle rebound ���� ���� �����鿡 ���� ���Ǵ� ����
	float exitXFactor; // ball �浹�� direction �� ������ ���� scale factor
	float fixedZoneHalfWidth; // ball ��� �浹�� �������� ƨ���� ������ ���� �����ϱ� ���� ��.
						      // ��� �浹�� ��� ball�� paddle�� x ��ġ�� �����Ƿ� �������� ƨ��. ���� ��� �� ���� ���.
	float fixedZoneExitX;
	// -----------------------------------------------
	Vec2 pos;
	bool isCooldown = false;
};