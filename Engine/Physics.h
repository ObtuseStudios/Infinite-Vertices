//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Object.h"
#include "Rectangle.h"

namespace Penguin
{
	enum class Direction { None, Up, Down, Left, Right };

	class Manifold
	{
	public:
		float Depth;
		Direction Dir;
		float rotation;

		Manifold(float _depth, Direction _dir, float _rot = 0)
			: Depth(_depth), Dir(_dir), rotation(_rot){ }
	};

	class Physics
	{
	public:
		static bool SimpleCollision(Object& a, Object& b);
		static Manifold CheckCollision(Object a, Object b);
		static Manifold AdvancedCollisionCheck(Object a, Object b);
		void ResolveCollision(Manifold* data, Object& a, float Scale = 1);
	};
}