//Copyright 2016, Cameron bell, All rights reserved

//Include guards
#pragma once

//The librarys used.
#include <SDL\SDL.h>
#include <string>
#include <IMG\SDL_image.h>
#include <SDL\SDL_ttf.h>
#include <SDL\SDL_mixer.h>

//The data types that are used for the window
#include "Vector.h"
#include "Colour.h"
#include "Debug.h"
#include "Input.h"
#include "Object.h"
#include "Camera.h"

//For strings
using namespace std;

class Object;

//Namespace
namespace Penguin
{
	class Window
	{
	
	friend class Input;
	
	public:
		//Set values and create the window
		Window(); //Constructor

		void Create(string t = "Engine", Vector s = Vector(640, 480), Colour b = Colour(255, 255, 255));
		void Clear();
		void Draw();

		void Quit(); //Closes the entire program.

		void setFullScreen();
		void setShowMouseCursor(bool);

		//Getters
		bool GetWindowState() const { return Running; };
		SDL_Renderer* GetRenderer() const { return render; };
		Vector GetWindowSize() const { return Size; };

		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimised();

		void SetWindowIcon(string path);

		Camera Camera;

	protected:
		//Whather the game is running.
		bool Running;

		//Window properties
		string Title; //The title of the window
		Vector Size; //The vector size of the window.
		Vector Position; //The vector size of the window
		Colour Background; //The RGBA colour of the windows background.

		//The actual SDL properties.
		SDL_Window* screen;
		SDL_Renderer* render;

		//Window focus
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;
	};
}