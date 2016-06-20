//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Object.h"
#include <SDL\SDL_ttf.h>

namespace Penguin
{
	class Text : public Object
	{
	public:
		Text(Vector p = Vector(0, 0), Colour c = Colour(0, 0, 0), float r = 0)
			: Object(p, Vector(100, 100), c, r) {};
		
		void Load(SDL_Renderer* rend, std::string fontPath, std::string message, int size = 15, Uint32 wrapLength = 0);

		void Draw(Window* rend, bool stick = false) override;
		void SetText(SDL_Renderer* rend, std::string message, Uint32 wrapLength = 0);
		void resetColourMod(Colour col);

		string getText() { return currentText; }
	private:
		SDL_Texture* newTexture;
		string currentText;
		TTF_Font* font;
		SDL_Texture* Texture;
	};
}