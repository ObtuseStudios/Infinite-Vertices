//Copyright 2016, Cameron bell, All rights reserved

#include "SpriteSheet.h"


namespace Penguin
{
	void SpriteSheet::Draw(Window* rend, bool stick)
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

		SDL_Rect* currentClip = &clips[currentFrame / framesNumber];

		SDL_RenderCopyEx(rend->GetRenderer(), tex, currentClip, &temp, rotation, &centerPoint, flipSDL);

		//Go to next frame
		++timer;

		if (timer >= animSpeed)
		{
			++currentFrame;
			timer = 0;
		}

		//Cycle animation
		if (currentFrame / framesNumber >= framesNumber)
		{
			currentFrame = 0;
		}
	}

	bool SpriteSheet::Load(SDL_Renderer* rend, std::string path, int numberOfFrames, int speed, bool org)
	{
		framesNumber = numberOfFrames;
		animSpeed = speed;
		timer = 0;

		int imgWidth;
		int imgHeght;

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) return false;

		imgWidth = loadedSurface->w;
		imgHeght = loadedSurface->h;

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);

		if (newTexture == NULL) return false;
		if (org) Scale = Vector(imgWidth / numberOfFrames, imgHeght);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

		tex = newTexture;

		SDL_SetTextureColorMod(tex, Col.Red, Col.Green, Col.Blue);

		int widthPerFrame = imgWidth / framesNumber;

		for (int i = 0; i < framesNumber; i++)
		{
			SDL_Rect temp = {i * widthPerFrame, 0, widthPerFrame, imgHeght};

			clips.push_back(temp);
		}

		return true;
	}

	void SpriteSheet::resetColourMod(Colour col)
	{
		SDL_SetTextureColorMod(tex, col.Red, col.Green, col.Blue);
		SDL_SetTextureAlphaMod(tex, col.Alpha);
	}
}