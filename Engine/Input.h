//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include <SDL\SDL.h>
#include <unordered_map>

#include "Window.h"

//Namespace
namespace Penguin
{
	class Window;

	class Input
	{
		friend class Camera;

	public:
		Input();

		bool ButtonHeld(unsigned int);
		bool ButtonDown(unsigned int);
		bool MouseClick(unsigned int);
		bool ButtonReleased(unsigned int);

		Vector GetMousePos();

		void Check(Window* win);

		SDL_Keymod GetModifierState();

		SDL_Event GetRawInput() { return e; };

	protected:
		Vector mouseNudge = Vector(0, 0);

	private:
		SDL_Event e;
		SDL_MouseButtonEvent m;

		Vector mousePos = Vector(0, 0);

		std::unordered_map<unsigned int, int> DownMap;
		std::unordered_map<unsigned int, bool> HeldMap;
		std::unordered_map<unsigned int, int> ReleaseMap;
		std::unordered_map<unsigned int, bool> MouseButtons;
	};
}