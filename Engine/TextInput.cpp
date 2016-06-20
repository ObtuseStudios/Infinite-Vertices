//Copyright 2016, Cameron bell, All rights reserved

#include "TextInput.h"

namespace Penguin
{
	TextInput::TextInput(SDL_Renderer* rend, std::string fontPath, int fontSize, std::string startingText, Colour textCol, Uint32 wL)
	{ 
		inputText = startingText;
		textColour = textCol;

		wrapLength = wL;

		inputTextTexture.Load(rend, fontPath, inputText, fontSize, wrapLength);
	}

	void TextInput::Update(Window& rend)
	{
		bool renderText = false;

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_BACKSPACE] && inputText.length() > 0)
		{
			inputText.pop_back();
			renderText = true;
		}

		else if (currentKeyStates[SDL_SCANCODE_C] && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(inputText.c_str());
		}

		else if (currentKeyStates[SDL_SCANCODE_V] && SDL_GetModState() & KMOD_CTRL)
		{
			inputText = SDL_GetClipboardText();
			renderText = true;
		}

		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_TEXTINPUT)
			{
				if (!((ev.text.text[0] == 'c' || ev.text.text[0] == 'C') && (ev.text.text[0] == 'v' || ev.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{
					inputText += ev.text.text;
					renderText = true;
				}
			}
		}

		if (renderText)
		{
			if (inputText != "") inputTextTexture.SetText(rend.GetRenderer(), inputText, wrapLength);
			else inputTextTexture.SetText(rend.GetRenderer(), " ", wrapLength);
		}

		inputTextTexture.Draw(&rend);
	}
}