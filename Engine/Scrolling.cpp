//Copyright 2016, Cameron bell, All rights reserved

#include "Scrolling.h"

namespace Penguin
{
	void Scrolling::Draw(Window* rend, bool stick)
	{
		scrollOffset -= scrollSpeed / rend->Camera.scale;
		if (scrollOffset < -Scale.x)
			scrollOffset = 0;

		if (!stick)
		{
			Position.x = scrollOffset * rend->Camera.scale;
			Position.x += Scale.x * rend->Camera.scale;
		}

		Sprite::Draw(rend);

		Position.x -= Scale.x * rend->Camera.scale;
		Sprite::Draw(rend);
	}
}