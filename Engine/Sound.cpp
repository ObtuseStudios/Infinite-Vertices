//Copyright 2016, Cameron bell, All rights reserved

#include "Sound.h"
#include "Debug.h"

namespace Penguin
{
	Sound::Sound()
	: currentMusicID(0), currentSoundID(0), albumNum(0), paused(false)
	{ }

	int Sound::LoadSoundEffect(std::string path)
	{
		Mix_Chunk* temp = NULL;
		temp = Mix_LoadWAV(path.c_str());

		if (temp == NULL)
		{
			Debug::Fatal("Could not load sound file: " + path);
		}

		sfx[currentSoundID] = temp;
		currentSoundID++;

		//Mix_FreeChunk(temp);

		return currentSoundID;
	}

	int Sound::AddSong(std::string path)
	{
		Mix_Music* temp = NULL;
		temp = Mix_LoadMUS(path.c_str());

		if (temp == NULL)
		{
			Debug::Fatal("Could not load song: " + path);
		}

		currentMusicID++;
		music[currentMusicID] = temp;

		//Mix_FreeMusic(temp);

		return currentMusicID;
	}

	void Sound::PlaySFX(int ID, int vol)
	{
		Mix_Volume(ID, vol);
		Mix_PlayChannel(ID, sfx[ID], 0);
	}

	void Sound::PlaySong(int num, bool loop)
	{
		if (loop) Mix_PlayMusic(music[num], -1);
		else Mix_PlayMusic(music[num], 0);
	}

	void Sound::PlayAlbum(bool loop)
	{
		if (Mix_PlayingMusic() == 0)
		{
			albumNum++;

			Mix_PlayMusic(music[albumNum], 0);

			if (albumNum == currentMusicID && loop) albumNum = 0;
			else if (albumNum == currentMusicID) StopMusic();
		}
	}

	void Sound::PauseMusic()
	{
		if (paused)	{ Mix_PauseMusic(); paused = true; }
		else { Mix_ResumeMusic(); paused = false; }
	}

	void Sound::StopMusic()
	{
		Mix_HaltMusic();
	}
}