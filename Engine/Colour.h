//Copyright 2016, Cameron bell, All rights reserved

//Include guards
#pragma once

//Namespace
namespace Penguin
{
	struct Colour
	{
		//The class constructor can take some rgba ints.
		Colour(int r = 255, int g = 255, int b = 255, int a = 255)
		{
			//Set each parameter to the corrisponding variable
			Red = r;
			Green = g;
			Blue = b;
			Alpha = a;
		}

		//The actual colour components.
		int Red;
		int Green;
		int Blue;
		int Alpha;
	};
}