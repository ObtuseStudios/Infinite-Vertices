//Copyright 2016, Cameron bell, All rights reserved

#pragma once
#include "Object.h"

namespace Penguin
{
	class Sprite : public Object
	{
	public:
		Sprite(Vector p = Vector(0, 0), Vector s = Vector(100, 100), Colour c = Colour(255, 255, 255), float r = 0)
			: Object(p, s, c, r) {};
		void Draw(Window* rend, bool stick= false) override;
		void Load(SDL_Renderer* rend, std::string, bool org = false);

		void resetColourMod(Colour);

		inline SDL_Texture* getRawTexture() { return Texture; }
		inline void setRawTexture(SDL_Texture* tex) { Texture = tex; }
		
	protected:
		SDL_Texture* Texture;
		SDL_Texture* newTexture;
	};
}