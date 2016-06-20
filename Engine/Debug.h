//Copyright 2016, Cameron bell, All rights reserved

//Include Guards
#pragma once

//All the nessisary files
#include <SDL\SDL.h>
#include <iostream>
#include <string>

//Namespace
namespace Penguin
{
	class Debug
	{
	public:
		//All functions of the Debug class.
		template <class F>

		static void Fatal(F Message) //Stops the program and prints an error.
		{
			//Print the users error.
			std::cout << "A fatal error occured: " << Message << std::endl;
			std::cout << "\nPress enter to continue..." << std::endl;

			//Wait for input
			getchar();

			//Close
			Quit();
		}

		template <class W>

		static void Warning(W Message) //Prints out a warning to the console.
		{
			//Print.
			std::cout << "Warning: " << Message << std::endl;
		}

		template <class P>

		static void Print(P Message) //Just prints a message.
		{
			//Print
			std::cout << Message << std::endl;
		}

		inline static void Quit() //Closes the program
		{
			//Close
			exit(-1);
		}

		inline static void Wait(Uint32 Time)  //Wait time in seconds.
		{
			//Wait using SDL_Delay, convert to seconds.
			SDL_Delay(Time);
		}
	};
}