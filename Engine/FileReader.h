//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Penguin
{
	class FileReader
	{
	public:
		static std::vector<std::string> loadTextFile(std::string path)
		{
			std::ifstream file(path);
			
			std::vector<std::string> result;
			std::string currentLine;

			while (std::getline(file, currentLine))
			{
				result.push_back(currentLine);
			}

			return result;
		}

		/*
		static int const TOTAL_DATA = 10;

		Sint32 data[TOTAL_DATA];
		
		void load(std::string path)
		{
			SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r+b");

			if (file == NULL)
			{
				Debug::Warning("Could not find file: " + path + ", Creating it!");

				file = SDL_RWFromFile(path.c_str(), "w+b");

				if (file != NULL)
				{
					Debug::Print("Successfully Created file!");

					for (int i = 0; i < TOTAL_DATA; ++i)
					{
						data[i] = 0;
						SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
					}

					SDL_RWclose(file);
				}
				else
				{
					Debug::Fatal("Could not create the file :(");
				}
			}
			else
			{
				Debug::Print("Reading file: " + path);

				for (int i = 0; i < TOTAL_DATA; i++)
				{
					SDL_RWread(file, &data[i], sizeof(Sint32), 1);
				}

				SDL_RWclose(file);
			}

		}
		*/
	};
}