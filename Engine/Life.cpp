#include "Life.h"

Life::Life(const Vec2& pos_in, const int& radius_in, const int& point_in, const Color& color_in)
	:
	pos(pos_in),
	radius(radius_in),
	point(point_in),
	color(color_in)
{
}

void Life::DecreaseLife()
{
	point--;
}

void Life::Draw(Graphics& gfx) const
{
	int offset = 0;
	for (int i = 0; i < point; i++)
	{
		gfx.DrawCircle((int)pos.x + offset, (int)pos.y, radius, color);
		offset+=(pos.x + 1);
	}
}

int Life::GetLifePoint() const
{
	return point;
}

bool Life::isGameOver() const
{
	if (point <= 0)
	{
		return true;
	}
	return false;
}
