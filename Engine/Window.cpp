//Copyright 2016, Cameron bell, All rights reserved

//Including header files.
#include "Window.h"
#include "Presets.h"

//Namespace
namespace Penguin
{
	//Called when class object is created.
	Window::Window()
	{
		//The window is running.
		Running = true;

		//Set pointer values to nothing.
		screen = NULL;
		render = NULL;

		mMouseFocus = false;
		mKeyboardFocus = false;
		mFullScreen = false;
		mMinimized = false;
	}

	void Window::Create(string t, Vector s, Colour b)
	{
		//Set
		Title = t;
		Size = s;
		Background = b;

		Presets presets;

		//Set the default window properties.
		Position = presets.POS_CENTERED;

		//Setup SDL, and store the error code
		int Setup = SDL_Init(SDL_INIT_EVERYTHING);

		//If the setup returned an error, create a fatal error.
		if (Setup < 0)
		{
			Debug::Fatal("could not setup media layer.");
		}

		//Create a new window, based on class variables, then store the return value.
		screen = SDL_CreateWindow(Title.c_str(), Position.x, Position.y, Size.x, Size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		//If SDL was unable to create the window.
		if (screen == NULL)
		{
			Debug::Fatal("could not create the main window.");
		}

		//Create the game renderer, and store it.
		//This renderer uses the GPU.
		render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		//If the renderer could not be made.
		if (render == NULL)
		{
			Debug::Fatal("could not create the renderer.");
		}

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			Debug::Fatal("Could no t setup PNG loader");
		}

		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			Debug::Fatal("Could not setup the text loader");
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			Debug::Fatal("Could not setup sound mixer at: 44100hz");
		}

		SDL_RenderSetLogicalSize(render, Size.x, Size.y);

		mMouseFocus = true;
		mKeyboardFocus = true;

		SDL_GL_SetSwapInterval(1);

		//Make the windows background Backgroundour appropriate.
		SDL_SetRenderDrawColor(render, Background.Red, Background.Green, Background.Blue, Background.Alpha);

		Debug::Print("Setup successfully");
	}

	void Window::Clear()
	{
		//Clear screen of everything
		SDL_SetRenderDrawColor(render, Background.Red, Background.Green, Background.Blue, Background.Alpha);
		SDL_RenderClear(render);
	}

	void Window::Draw()
	{
		//Update screen
		SDL_RenderPresent(render);
		//Camera.Update();
	}

	void Window::setFullScreen()
	{
		if (mFullScreen)
		{
			SDL_SetWindowFullscreen(screen, SDL_FALSE);
			mFullScreen = false;
		}
		else
		{
			SDL_SetWindowFullscreen(screen, SDL_TRUE);
			mFullScreen = true;
			mMinimized = false;
		}
	}

	void Window::setShowMouseCursor(bool a)
	{
		if (a) SDL_ShowCursor(SDL_ENABLE);
		else SDL_ShowCursor(SDL_DISABLE);
	}

	void Window::Quit()
	{
		Debug::Print("Closing up!");

		//No longer running.
		Running = false;

		//Delete textures.
		SDL_DestroyWindow(screen);
		SDL_DestroyRenderer(render);

		//Quit SDL.
		Mix_Quit();
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		//Close
		exit(0);
	}

	void Window::SetWindowIcon(string path)
	{
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) Debug::Fatal("Could not load image: " + path);

		SDL_SetWindowIcon(screen, loadedSurface);
	}

	bool Window::isMinimised() { return mMinimized; }
	bool Window::hasMouseFocus() { return mMouseFocus; }
	bool Window::hasKeyboardFocus() { return mKeyboardFocus; }
}