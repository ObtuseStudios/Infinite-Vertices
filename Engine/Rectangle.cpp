//Copyright 2016, Cameron bell, All rights reserved

#include "Rectangle.h"
#include "Debug.h"

namespace Penguin
{
	void Rectangle::Draw(Window* rend, bool stick)
	{
		SetPos();

		if (!stick)
		{
			Source.x -= rend->Camera.position.x / rend->Camera.scale;
			Source.y -= rend->Camera.position.y / rend->Camera.scale;

			Source.x *= rend->Camera.scale;
			Source.y *= rend->Camera.scale;

			Source.w *= rend->Camera.scale;
			Source.h *= rend->Camera.scale;

			Vector roundedPos = Vector(Source.x, Source.y);

			roundedPos.x /= rend->Camera.scale;
			roundedPos.y /= rend->Camera.scale;

			Source.x = std::round(roundedPos.x) * rend->Camera.scale;
			Source.y = std::round(roundedPos.y) * rend->Camera.scale;
		}

		SDL_SetRenderDrawColor(rend->GetRenderer() , Col.Red, Col.Green, Col.Blue, Col.Alpha);
		SDL_RenderFillRect(rend->GetRenderer(), &Source);
	}

	void Rectangle::DrawOutline(Window* rend, bool stick)
	{
		SetPos();

		if (!stick)
		{
			Source.x -= rend->Camera.position.x / rend->Camera.scale;
			Source.y -= rend->Camera.position.y / rend->Camera.scale;

			Source.x *= rend->Camera.scale;
			Source.y *= rend->Camera.scale;

			Source.w *= rend->Camera.scale;
			Source.h *= rend->Camera.scale;

			Vector roundedPos = Vector(Source.x, Source.y);

			roundedPos.x /= rend->Camera.scale;
			roundedPos.y /= rend->Camera.scale;

			Source.x = std::round(roundedPos.x) * rend->Camera.scale;
			Source.y = std::round(roundedPos.y) * rend->Camera.scale;
		}

		SDL_SetRenderDrawColor(rend->GetRenderer() , Col.Red, Col.Green, Col.Blue, Col.Alpha);
		SDL_RenderDrawRect(rend->GetRenderer(), &Source);
	}
}