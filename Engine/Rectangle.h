//Copyright 2016, Cameron bell, All rights reserved

#pragma once
#include "Object.h"
namespace Penguin
{
	class Rectangle : public Object
	{
	public:
		Rectangle(Vector p = Vector(0, 0), Vector s = Vector(100, 100), Colour c = Colour(0, 0, 0), float r = 0)
			: Object(p, s, c, r) {};
		void Draw(Window* rend, bool stick = false) override;
		void DrawOutline(Window* rend, bool stick = false);
	};
}