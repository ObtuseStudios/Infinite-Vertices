//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Timer.h"
#include <string>

namespace Penguin
{
	class FPS
	{
	public:
		FPS();

		void Start();
		std::string Update(int cap);

		void EndMovement();

		double deltaTime;

	private:

		//The frames per second timer
		Timer fpsTimer;
		Timer capTimer;
		Timer stepTimer;

		//In memory text stream
		std::string timeText;

		//Start counting frames per second
		int countedFrames;
	};
}