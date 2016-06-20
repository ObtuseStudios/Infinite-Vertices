//Copyright 2016, Cameron bell, All rights reserved

#include "Window.h"
#include "Debug.h"
#include <iostream>

//Namespace
namespace Penguin
{
	Input::Input()
	{
		//Remove beggining number
		for (int i = 0; i < 256; i++)
		{
			DownMap[i] = 0;
			HeldMap[i] = false;
		}
	}

	void Input::Check(Window* win)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				HeldMap[e.key.keysym.sym] = true;
				ReleaseMap[e.key.keysym.sym] = 1;
				//DownMap[e.key.keysym.sym]++;
				break;
			}

			if (e.type == SDL_KEYUP)
			{
				HeldMap[e.key.keysym.sym] = false;
				ReleaseMap[e.key.keysym.sym] = 0;
				DownMap[e.key.keysym.sym] = 0;

				if (e.key.keysym.sym == SDLK_ESCAPE) Debug::Quit();
				break;
			}

			if (e.type == SDL_MOUSEMOTION)
			{
				mousePos.x = e.button.x;
				mousePos.y = e.button.y;
			}

			if (e.type == SDL_WINDOWEVENT)
			{
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					win->Size.x = e.window.data1;
					win->Size.y = e.window.data2;

					//win->Draw();
					break;

				case SDL_WINDOWEVENT_EXPOSED:
					//win->Draw();
					break;

				case SDL_WINDOWEVENT_ENTER:
					win->mMouseFocus = true;
					break;

				case SDL_WINDOWEVENT_LEAVE:
					win->mMouseFocus = false;
					break;

				case SDL_WINDOWEVENT_FOCUS_GAINED:
					win->mKeyboardFocus = true;
					break;

				case SDL_WINDOWEVENT_FOCUS_LOST:
					win->mKeyboardFocus = false;
					break;

				case SDL_WINDOWEVENT_MINIMIZED:
					win->mMinimized = true;
					break;

				case SDL_WINDOWEVENT_MAXIMIZED:
					win->mMinimized = false;
					break;

				case SDL_WINDOWEVENT_RESTORED:
					win->mMinimized = false;
					break;
				}
			}

			if (e.type == SDL_QUIT)
			{
				Debug::Quit();
				break;
			}
		}
	}

	bool Input::ButtonHeld(unsigned int ID)
	{
		auto it = HeldMap.find(ID);

		if (it != HeldMap.end())
		{
			return it->second;
		}

		return false;
	}

	bool Input::ButtonDown(unsigned int ID)
	{
		auto downIt = DownMap.find(ID);
		auto heldIt = HeldMap.find(ID);

		if (downIt != DownMap.end() && heldIt != HeldMap.end())
		{
			if (heldIt->second) DownMap[ID]++;

			if (downIt->second == 1) return true;
		}

		return false;
	}

	bool Input::ButtonReleased(unsigned int ID)
	{
		auto it = ReleaseMap.find(ID);

		if (it != ReleaseMap.end())
		{
			ReleaseMap[ID]++;

			if (it->second == 1)
				return true;

			return false;
		}

		return false;
	}

	bool Input::MouseClick(unsigned int ID)
	{
		return SDL_GetMouseState(NULL, NULL) & ID;
	}

	Vector Input::GetMousePos()
	{
		//int x, y;
		//SDL_GetMouseState(&x, &y);

		//x += nudge.x;
		//y += nudge.y;

		return mousePos + mouseNudge;
	}

	SDL_Keymod Input::GetModifierState()
	{
		return SDL_GetModState();
	}
}