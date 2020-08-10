#pragma once

#include "RectF.h"
#include "Graphics.h"

class Wall
{
public:
	Wall(const RectF& rect_in, float offset, Color color_in);
	RectF GetRect() const;
	void Draw(Graphics& gfx);
private:
	RectF rect;
	float offset;
	Color color;
};