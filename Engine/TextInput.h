//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Text.h"
#include "Colour.h"
#include "Text.h"
#include "Key.h"

#include "Window.h"

namespace Penguin
{
	class TextInput
	{
	private:
		Text inputTextTexture;
		Colour textColour;

		std::string inputText;

		SDL_Event ev;
		Uint32 wrapLength;

	public:
		TextInput(SDL_Renderer* rend,
			std::string fontPath,
			int fontSize = 12, 
			std::string startingText = "Enter some text!", 
			Colour textCol = Colour(0, 0, 0), 
			Uint32 wL = 0);

		void Update(Window& rend);

		void SetPosition(Vector pos) { inputTextTexture.Position = pos; };
	};
}