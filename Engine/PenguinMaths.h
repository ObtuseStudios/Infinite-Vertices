//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Vector.h"

namespace Penguin
{
	struct Maths
	{
		inline static float lerp(float current, float target, float time) 
		{ return (1 - time) * current + time * target; }

		inline static Vector vectorLerp(Vector current, Vector target, float time)
		{ return Vector((1 - time) * current.x + time * target.x, (1 - time) * current.y + time * target.y); }
	};
}