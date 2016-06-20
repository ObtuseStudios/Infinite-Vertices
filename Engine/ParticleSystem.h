//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Particle.h"
#include <ctime>

namespace Penguin
{
	enum DestroyTypes
	{
		Fadeout, TimeOut, ColourizeFade, Colourize
	};

	class ParticleSystem
	{
	private:
		int timer = 0;
		int numberDead = 0;

	public:

		int TOTAL_PARTICLES = 1;

		vector<Particle*> particles;

		Sprite img;

		DestroyTypes removeType;

		
		ParticleSystem(int parts, std::string path, SDL_Renderer* rend, DestroyTypes type = DestroyTypes::Fadeout)
			: removeType(type), TOTAL_PARTICLES(parts)
		{
			for (int i = 0; i < TOTAL_PARTICLES; i++)
				particles.push_back(NULL);

			srand(unsigned int(time(NULL)));

			img.Load(rend, path ,true);
		}

		~ParticleSystem()
		{
			for (int i = 0; i < TOTAL_PARTICLES; i++)
				delete particles[i];
		}

		void RenderParticle(Window* win, Vector pos, Vector size, int speed = 20)
		{
			//Go through particles
			for (int i = 0; i < TOTAL_PARTICLES; ++i)
			{
				if (particles[i] == NULL)
					particles[i] = new Particle(img, pos, size);

				//Delete and replace dead particles
				if (particles[i]->isDead())
				{
					delete particles[i];
					particles[i] = new Particle(img, pos, size);
				}
			}

			//Show particles
			for (int i = 0; i < TOTAL_PARTICLES; ++i)
			{
				if (removeType == DestroyTypes::Fadeout)
					particles[i]->ChangeAlpha(win, speed);
				else if (removeType == DestroyTypes::TimeOut)
					particles[i]->destroyAfterTime(win, speed);
				else if (removeType == DestroyTypes::Colourize)
					particles[i]->ChangeColour(win, speed);
				else if (removeType == DestroyTypes::ColourizeFade)
					particles[i]->ChangeColourFade(win, speed);
			}
		}

		void resetSystem()
		{
			numberDead = 0;
			timer = 0;

			for (int i = 0; i < TOTAL_PARTICLES; i++)
				delete particles[i];
		}
	};
}