#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Life
{
public:
	Life(const Vec2& pos_in, const int& radius_in, const int& point_in, const Color& color_in);
	void DecreaseLife();
	void Draw(Graphics& gfx) const;
	int GetLifePoint() const;
	bool isGameOver() const;
private:
	int point;
	Vec2 pos;
	int radius;
	Color color;
};