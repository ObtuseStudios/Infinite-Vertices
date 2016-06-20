//Copyright 2016, Cameron bell, All rights reserved

#pragma once

//Include every other file in the library
#include "SpriteSheet.h"
#include "Window.h"
#include "Colour.h"
#include "Presets.h"
#include "Text.h"
#include "Body.h"
#include "TextInput.h"
#include "Debug.h"
#include "Sound.h"
#include "Rectangle.h"
#include "Sprite.h"
#include "Scrolling.h"
#include "ParticleSystem.h"
#include "Vector.h"
#include "Input.h"
#include "TileMap.h"
#include "Key.h"
#include "FPS.h"
#include "Button.h"
#include "FileReader.h"
#include "PenguinMaths.h"
#include "Physics.h"
#include "SearchCell.h"
#include "PathFinding.h"

namespace Penguin
{
	class Engine
	{
	public:
		Window Window;
		Input Input;
		Colour Colour;
		Presets Presets;
		Physics Physics;
		Debug Debug;
		Vector Vector;
		PathFinding PathFinding;
		Key Key;
		FPS FPS;
		FileReader FileReader;
		Sound Sound;
		Maths Maths;
	};
}