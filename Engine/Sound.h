//Copyright 2016, Cameron bell, All rights reserved

#pragma once
#include <map>
#include <vector>
#include <SDL\SDL_mixer.h>

namespace Penguin
{
	class Sound
	{
	public:
		Sound();

		int LoadSoundEffect(std::string path);
		int AddSong(std::string path);

		void PlaySFX(int id, int vol = 128);
		void PlaySong(int num, bool loop = true);
		void PlayAlbum(bool loop = true);

		void PauseMusic();
		void StopMusic();
	private:
		std::map<int, Mix_Music*> music;
		std::map<int, Mix_Chunk*> sfx;

		int currentSoundID;
		int currentMusicID;

		int albumNum;
		bool paused;
	};
}