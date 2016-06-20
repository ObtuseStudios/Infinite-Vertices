//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Rectangle.h"
#include "Sprite.h"

#include <algorithm>
#include <vector>
#include <map>

namespace Penguin
{
	struct Tile : Object
	{
		bool shouldDraw;
		bool shouldCollide;
		SDL_Texture* tex;
		SDL_Rect cropping;

		int positionInLevel;
		int ID = -1;

		Tile(Vector p = Vector(0, 0), Vector s = Vector(32, 32), Colour c = Colour(), float r = 0)
			: Object(p, s, c, r),  shouldDraw(true), shouldCollide(true) {}

		void Draw(Window* rend, bool stick = false) override
		{
			if (!shouldDraw)
				return;

			SetPos();
			
			if (Col.Red != 255 || Col.Green != 255 || Col.Blue != 255 || Col.Alpha != 255)
				SDL_SetTextureColorMod(tex, Col.Red, Col.Green, Col.Blue);

			SDL_Rect temp = Source;

			if (!shouldDraw) return;

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

				//SDL_Rect drawRect = { Position.x, Position.y, Scale.x, Scale.y };

			}

			SDL_RenderCopyEx(rend->GetRenderer(), tex, &cropping, &temp, rotation, &centerPoint, flipSDL);
		}

	};

	class TileMap
	{
	public:
		TileMap(std::string p, Sprite* image, Vector RBC, Vector mapSize, Vector size);

		void Draw(Window* win);

		Tile* GetFirstByID(int ID);
		vector<Tile*> GetByID(int ID);

		std::map<int, Tile>* GetEntireLevel() { return &levelData; }

	private:
		inline int findNumberInArray(int row, int col);

		int rows;
		int columns;

		int tileMapWidth;
		int tileMapHeight;

		char* levelMapSymbols = NULL;

		Vector tileSize;
		Sprite tileImage;

		std::string path;
		std::map<int, Tile> levelData;
		std::unordered_map<int, SDL_Rect> tiles;
	};
}