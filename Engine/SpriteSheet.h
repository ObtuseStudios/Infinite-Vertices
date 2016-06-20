//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Object.h"
#include <vector>

namespace Penguin
{
	class SpriteSheet: public Object
	{
	public:
		SpriteSheet(Vector p = Vector(0, 0), Vector s = Vector(100, 100), Colour c = Colour(255, 255, 255), float r = 0)
			: Object(p, s, c, r) { currentFrame = 0; };

		bool Load(SDL_Renderer* rend, std::string path, int numberOfFrames, int speed, bool org = false);
		void resetColourMod(Colour);
		void Draw(Window* rend, bool stick = false) override;
	private:
		int framesNumber;
		int currentFrame;
		int timer;
		int animSpeed;
		std::vector<SDL_Rect> clips;
		SDL_Texture* tex;
	};
}