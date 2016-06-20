//Copyright 2016, Cameron bell, All rights reserved

#include "TileMap.h"

#include <sstream>
#include <fstream>
#include <string>

namespace Penguin
{
	TileMap::TileMap(std::string p, Sprite* image, Vector RBC, Vector mapSize, Vector size)
	{
		path = p;

		rows = RBC.x;
		columns = RBC.y;

		tileMapWidth = mapSize.x;
		tileMapHeight = mapSize.y;

		tileSize = size;
		tileImage = *image;

		levelMapSymbols = new char[tileMapHeight * tileMapWidth];

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < columns; c++)
			{
				SDL_Rect cropping = { c * tileSize.x, r * tileSize.y, tileSize.x, tileSize.y };

				tiles[findNumberInArray(r, c)] = cropping;
			}
		}

		std::string line;
		std::ifstream fileInputTest(path, std::ios::in);

		getline(fileInputTest, line);

		if (line[line.length() - 1] != ',')
		{
			Debug::Print("Reformatting level data file: " + path);

			fileInputTest.clear();
			fileInputTest.seekg(0, std::ios::beg);

			if (fileInputTest.good())
			{
				std::stringstream bufer;

				int currentLineNumber = 1;

				while (getline(fileInputTest, line))
				{
					if (currentLineNumber < tileMapHeight)
						bufer << line << ",\n";
					else
						bufer << line;

					currentLineNumber++;
				}
				std::string contents;
				std::ofstream fout(path, std::ios::out);

				fout << bufer.rdbuf();

				fout.close();
			}

			fileInputTest.close();
		}


		std::ifstream file(path);

		if (!file.is_open()) Debug::Fatal("Could not open tilemap file: " + path);

		int j = 0;

		while (file.good())
		{
			file.getline(levelMapSymbols, 512, ',');

			levelData[j].ID = std::atoi(levelMapSymbols);
			j++;
		}

		file.close();

		int currentX = -1;
		int currentY = 0;

		for (int i = 0; i < tileMapWidth * tileMapHeight; i++)
		{
			currentX++;

			if (currentX >= tileMapWidth)
			{
				currentX = 0;
				currentY++;
			}

			if (levelData[i].ID == -1)
			{
				levelData.erase(i);
				continue;
			}
			
			levelData[i].Scale = tileSize;

			levelData[i].Position.x = currentX * tileSize.x;
			levelData[i].Position.y = currentY * tileSize.y;

			levelData[i].cropping = tiles[levelData[i].ID];

			levelData[i].tex = tileImage.getRawTexture();

			levelData[i].positionInLevel = i;
		}
	}

	void TileMap::Draw(Window* win)
	{
		for (int i = 0; i < levelData.size(); i++)
		{
			if (levelData[i].ID == -1) continue;
			
			levelData[i].Draw(win, false);
		}
	}

	int TileMap::findNumberInArray(int row, int col)
	{
		return row * columns + col;
	}

	/*void TileMap::putTileBackIntoLevel(Tile t)
	{
		levelData[t.positionInLevel] = t;
	}*/

	Tile* TileMap::GetFirstByID(int ID)
	{
		typedef std::map<int, Tile>::iterator it_type;
		for (it_type iterator = levelData.begin(); iterator != levelData.end(); iterator++) {
			if (iterator->second.ID == ID)
				return &iterator->second;
		}

		Debug::Warning("Could not find object with ID:" + ID);
		return NULL;
	}

	vector<Tile*> TileMap::GetByID(int ID)
	{
		vector<Tile*> objs;

		typedef std::map<int, Tile>::iterator it_type;
		for (it_type iterator = levelData.begin(); iterator != levelData.end(); iterator++) {
			if (iterator->second.ID == ID)
				objs.push_back(&iterator->second);
		}

		if (objs.empty()) 
			Debug::Warning("Could not find any objects with the ID:" + ID);

		return objs;
	}
}