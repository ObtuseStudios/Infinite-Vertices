//Copyright 2016, Cameron bell, All rights reserved

#include "Text.h"

namespace Penguin
{
	void Text::Load(SDL_Renderer* rend, std::string fontPath, std::string message, int size, Uint32 wrapLength)
	{
		SDL_DestroyTexture(newTexture);
		newTexture = NULL;

		SetPos();
		font = TTF_OpenFont(fontPath.c_str(), size);

		if (font == NULL)
		{
			Debug::Fatal("Could not load the font: " + fontPath);
		}

		SDL_Color textCol = { Col.Red, Col.Green, Col.Blue, Col.Alpha };

		SDL_Surface* loadedSurface = NULL;

		//Load image at specified path
		if (wrapLength != 0)
			loadedSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textCol, wrapLength);
		else
			loadedSurface = TTF_RenderText_Blended(font, message.c_str(), textCol);

		if (loadedSurface == NULL) Debug::Fatal("Could not load text");

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);

		Scale.x = loadedSurface->w;
		Scale.y = loadedSurface->h;

		if (newTexture == NULL) Debug::Fatal("Could not create texture from text");

		//Get size
		Scale.x = loadedSurface->w;
		Scale.y = loadedSurface->h;

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

		Texture = newTexture;

		currentText = message;
	}

	void Text::SetText(SDL_Renderer* rend, std::string message, Uint32 wrapLength)
	{
		SDL_DestroyTexture(newTexture);
		newTexture = NULL;

		SDL_Color textCol = { Col.Red, Col.Green, Col.Blue, Col.Alpha };

		SDL_Surface* loadedSurface = NULL;

		//Load image at specified path
		if (wrapLength != 0)
			loadedSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textCol, wrapLength);
		else
			loadedSurface = TTF_RenderText_Blended(font, message.c_str(), textCol);

		if (loadedSurface == NULL) Debug::Fatal("Could not load text");

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);

		if (newTexture == NULL) Debug::Fatal("Could not create texture from text");
		
		Scale.x = loadedSurface->w;
		Scale.y = loadedSurface->h;

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

		Texture = newTexture;

		currentText = message;
	}

	void Text::Draw(Window* rend, bool stick)
	{
		SetPos();

		SDL_Rect temp = Source;
		
		if (!stick)
		{
			temp.x -= rend->Camera.position.x / rend->Camera.scale;
			temp.y -= rend->Camera.position.y / rend->Camera.scale;

			temp.x *= rend->Camera.scale;
			temp.y *= rend->Camera.scale;

			temp.w *= rend->Camera.scale;
			temp.h *= rend->Camera.scale;

			Vector roundedPos = Vector(temp.x, temp.y);

			roundedPos.x /= rend->Camera.scale;
			roundedPos.y /= rend->Camera.scale;

			temp.x = std::round(roundedPos.x) * rend->Camera.scale;
			temp.y = std::round(roundedPos.y) * rend->Camera.scale;
		}

		SDL_RenderCopyEx(rend->GetRenderer(), Texture, NULL, &temp, rotation, &centerPoint, flipSDL);
	}

	void Text::resetColourMod(Colour col)
	{
		SDL_SetTextureColorMod(Texture, col.Red, col.Green, col.Blue);
	}
}