//Copyright 2016, Cameron bell, All rights reserved

#include "Particle.h"

namespace Penguin
{
	Particle::Particle(Sprite s, Vector pos, Vector range)
		: dead(false)
	{
		//Set offsets
		position = Vector(pos.x + (rand() % int(range.x)), pos.y + (rand() % int(range.y)));
		mTexture = s;

		mTexture = s;
		mTexture.Position = position;

		channel = rand() % 3;

		currentCol = Colour();
	}

	void Particle::ChangeAlpha(Window* win, int fallSpeed)
	{
		Draw(win);

		currentCol.Alpha -= rand() % fallSpeed;

		mTexture.Col = currentCol;

		if (currentCol.Alpha < 0) dead = true;
	}

	void Particle::ChangeColourFade(Window* win, int time)
	{
		Draw(win);

		destroyFrames++;

		if (destroyFrames == 1)
		{
			if (channel == 0) currentCol = Colour(255, 0, 0);
			if (channel == 1) currentCol = Colour(0, 255, 0);
			if (channel == 2) currentCol = Colour(0, 0, 255);
		}

		currentCol.Alpha -= rand() % time;
		mTexture.Col = currentCol;

		if (currentCol.Alpha < 0)
			dead = true;
	}
	
	void Particle::ChangeColour(Window* win, int time)
	{
		Draw(win);

		if (destroyFrames == 0)
		{
			if (channel == 0) currentCol = Colour(255, 0, 0);
			if (channel == 1) currentCol = Colour(0, 255, 0);
			if (channel == 2) currentCol = Colour(0, 0, 255);
		}

		destroyFrames += rand() % (time / (time / 10));

		if (destroyFrames > time) dead = true;
	}

	void Particle::destroyAfterTime(Window* win, int time)
	{
		Draw(win);

		destroyFrames += rand() % (time / (time / 10));

		if (destroyFrames > time) dead = true;
	}

	void Particle::Draw(Window* win)
	{
		mTexture.resetColourMod(currentCol);
		mTexture.Draw(win);
	}

	bool Particle::isDead()
	{
		return dead;
	}
}