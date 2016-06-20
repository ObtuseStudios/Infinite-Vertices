//Copyright 2016, Cameron bell, All rights reserved

#include "FPS.h"

namespace Penguin
{
	FPS::FPS()
	{
		countedFrames = 0;
		fpsTimer.start();
	}

	void FPS::Start()
	{
		capTimer.start();
		deltaTime = stepTimer.getTicks() / 1000.0f;
	}

	void FPS::EndMovement()
	{
		stepTimer.start();
	}

	std::string FPS::Update(int cap)
	{
		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		//Set text to be rendered
		timeText = "FPS (Capped): " + std::to_string(avgFPS);

		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < cap)
		{
			//Wait remaining time
			SDL_Delay(cap - frameTicks);
		}

		return timeText;
	}
}