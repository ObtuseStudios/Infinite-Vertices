//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "PenguinMaths.h"
#include "Window.h"

namespace Penguin
{
	class Camera
	{
		friend class Window;

	public:
		Vector position = Vector(0, 0);
		Vector levelSize;
		Vector screenSize;

		float scale = 1;

		void Init(Vector size, float s = 1, Vector level = Vector(-1, -1), Vector startP = Vector(0, 0))
		{
			screenSize = size;
			position = startP;
			scale = s;

			if (level == Vector(-1, -1))
				levelSize = screenSize;

			else
			{
				levelSize.x = level.x * scale;
				levelSize.y = level.y * scale;
			}
		}

		void Follow(Vector pos, float speed = 0.05f)
		{
			centerCamera(pos, speed);
		}


		void adjustMouse(Input* in)
		{
			in->mouseNudge = position;
		}

	protected:
		
		void centerCamera(Vector playerpos, float time)
		{
			playerpos.x *= scale;
			playerpos.y *= scale;

			position.x = Maths::lerp(position.x, (playerpos.x - (screenSize.x / 2)), time);
			position.y = Maths::lerp(position.y, (playerpos.y - (screenSize.y / 2)), time);

			if (position.x <= 0) { position.x = 0; }
			if (position.y <= 0) { position.y = 0; }

			if (position.x >= levelSize.x - screenSize.x) { position.x = (levelSize.x - screenSize.x); }
			if (position.y >= levelSize.y - screenSize.y) { position.y = (levelSize.y - screenSize.y); }
		}

	};
}