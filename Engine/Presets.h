//Copyright 2016, Cameron bell, All rights reserved

//Include guards.
#pragma once

//The files used.
#include <SDL\SDL.h>
#include <iostream>
#include <string>

//The datatypes of each constant.
#include "Vector.h"
#include "Colour.h"

//Namespace
namespace Penguin
{
	struct Presets
	{
		//All the consant variables to do with window position.
		const Vector POS_UNDEFINED = Vector(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
		const Vector POS_CENTERED = Vector(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

		//All the consant variables to do with window position.
		const Vector SIZE_DESKTOP = Vector(1920, 1080);
		const Vector SIZE_IPHONE = Vector(640, 1136);
		const Vector SIZE_LAPTOP = Vector(1366, 768);
		const Vector SIZE_TABLET = Vector(1024, 758);
		const Vector SIZE_HIGH = Vector(1440, 900);
		const Vector SIZE_MED = Vector(1280, 720);
		const Vector SIZE_LOW = Vector(640, 360);
		const Vector SIZE_100 = Vector(100, 100);

		//Common vector values.
		const Vector VECTOR_RIGHT = Vector(0, 1);
		const Vector VECTOR_DOWN = Vector(-1, 0);
		const Vector VECTOR_LEFT = Vector(0, -1);
		const Vector VECTOR_ZERO = Vector(0, 0);
		const Vector VECTOR_UP = Vector(1, 0);

		//16 Most common colours
		const Colour COLOUR_FUCHSIA = Colour(255, 255, 255);
		const Colour COLOUR_PURPLE = Colour(0, 0, 0);
		const Colour COLOUR_MAROON = Colour(0, 0, 0);
		const Colour COLOUR_YELLOW = Colour(0, 0, 0);
		const Colour COLOUR_SILVER = Colour(0, 0, 0);
		const Colour COLOUR_BLACK = Colour(0, 0, 0);
		const Colour COLOUR_WHITE = Colour(0, 0, 0);
		const Colour COLOUR_OLIVE = Colour(0, 0, 0);
		const Colour COLOUR_GREEN = Colour(0, 0, 0);
		const Colour COLOUR_GREY = Colour(0, 0, 0);
		const Colour COLOUR_LIME = Colour(0, 0, 0);
		const Colour COLOUR_AQUA = Colour(0, 0, 0);
		const Colour COLOUR_TEAL = Colour(0, 0, 0);
		const Colour COLOUR_BLUE = Colour(0, 0, 0);
		const Colour COLOUR_NAVY = Colour(0, 0, 0);
		const Colour COLOUR_RED = Colour(0, 0, 0);
	};
}