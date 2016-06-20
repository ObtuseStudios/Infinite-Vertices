//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Sprite.h"

namespace Penguin
{
	class Particle
	{
	public:
		//Initialize position and animation
		Particle(Sprite s, Vector pos, Vector range);

		//Shows the particle
		void ChangeAlpha(Window* win, int fallSpeed = 10);
		void ChangeColourFade(Window* win, int time = 10);
		void ChangeColour(Window* win, int time = 10);
		void destroyAfterTime(Window* win, int time = 10);

		//Checks if particle is dead
		bool isDead();

	private:
		void Draw(Window* win);

		//Offsets
		Vector position;
		int destroyFrames;
		int channel;

		bool dead;

		//Current frame of animation
		Colour currentCol;

		//Type of particle
		Sprite mTexture;
	};
}