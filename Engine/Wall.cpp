#include "Wall.h"
#include <assert.h>

Wall::Wall(const RectF& rect_in, float offset_in, Color color_in)
	:
	rect(rect_in),
	offset(offset_in),
	color(color_in)
{
}

RectF Wall::GetRect() const
{
	return rect;
}

void Wall::Draw(Graphics& gfx)
{
	for (int y = rect.top - offset; y <= rect.bottom + offset; y++)
	{
		assert(y >= 0 && y < gfx.ScreenHeight);
		for (int x = rect.left - offset; x <= rect.right + offset; x++)
		{
			if (y <= rect.top || x <= rect.left || y >= rect.bottom || x >= rect.right)
			{
				assert(x >= 0 && x < gfx.ScreenWidth);
				gfx.PutPixel(x, y, color);
			}
		}
	}
}
