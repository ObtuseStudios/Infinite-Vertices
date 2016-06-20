//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "Vector.h"
#include "Colour.h"
#include "Debug.h"
#include "Window.h"
#include "Body.h"

#include <string>
#include <SDL\SDL.h>
#include <IMG\SDL_image.h>

namespace Penguin
{
	class Window;
	class PathFinding;

	class Object
	{

	friend class Physics;
	friend class PathFinding;
	
	public:
		Object() = default;
		Object(Vector p, Vector s, Colour c, float r)
			: Position(p), Scale(s), Col(c), center(p), rotation(r), Velocity(Vector(0, 0))
		{
			Collider.ObjCollider = Collider::Box;
			Collider.ObjType = Type::Static;

			SetPos();
		}

		virtual void Draw(Window* rend, bool stick)
		{
			Debug::Warning("No draw routine has bee implemented!");
		}

		float rotation;
		Vector Velocity;
		Vector center;
		Vector Flip;

		Vector Position;
		Vector Scale;
		Colour Col;

		Body Collider;

	protected:
		SDL_Rect Source;
		SDL_Point centerPoint;
		SDL_RendererFlip flipSDL;

		virtual void SetPos()
		{
			//Set source
			Source.x = int(Position.x);
			Source.y = int(Position.y);
			Source.w = int(Scale.x);
			Source.h = int(Scale.y);

			flipSDL = SDL_RendererFlip((int(Flip.x) * SDL_FLIP_HORIZONTAL) | (int(Flip.y) * SDL_FLIP_VERTICAL));

			centerPoint.x = int(center.x);
			centerPoint.y = int(center.y);
		}
	};
}