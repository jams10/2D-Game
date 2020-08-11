#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const Vec2& center,Graphics& gfx );
	static void DrawGameOver(const Vec2& center, Graphics& gfx);
	static void DrawGameStart(const Vec2& center, Graphics& gfx);
	static void DrawFace(const Vec2& center, Graphics& gfx);
};