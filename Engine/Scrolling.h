//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Sprite.h"

namespace Penguin
{
	class Scrolling :public Sprite
	{
	public:
		Scrolling(float speed = 1, Vector p = Vector(0, 0), Vector s = Vector(640, 480), Colour c = Colour(255, 255, 255), float r = 0)
			: scrollSpeed(speed), Sprite(p, s, c, r) {};
		void Draw(Window* rend, bool stick = false) override;

		float scrollSpeed = 1;
	private:
		float scrollOffset = 0;
	};
}