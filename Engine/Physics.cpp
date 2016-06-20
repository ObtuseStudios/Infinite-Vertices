//Copyright 2016, Cameron bell, All rights reserved

#include "Physics.h"

namespace Penguin
{
	Manifold Physics::CheckCollision(Object a, Object b)
	{
		a.Position.x -= 3;
		a.Position.y -= 3;

		//Target rot
		float targetRot = 45 - abs(a.rotation - 45);

		//Find the collision vectors
		float vectorX = (a.Position.x + (a.Scale.x / 2)) - (b.Position.x + (b.Scale.x / 2));
		float vectorY = (a.Position.y + (a.Scale.y / 2)) - (b.Position.y + (b.Scale.y / 2));

		//Find the distance between the two objects
		float deltaWidth = (a.Scale.x / 2) + (b.Scale.x / 2);
		float deltaHeight = (a.Scale.y / 2) + (b.Scale.y / 2);

		//Check if the two objects are intersecting on the x and y axis
		if (fabs(vectorX) < deltaWidth && fabs(vectorY) <= deltaHeight)
		{
			//The direction of collision
			int directionX = deltaWidth - abs(vectorX);
			int directionY = deltaHeight - abs(vectorY);

			//Check for vertical collision
			if (directionX > directionY)
			{
				//Check for collisions from the top
				if (vectorY >= 0)
					return Manifold(directionY, Direction::Up);

				//Collisions form the botttom
				else
					return Manifold(directionY, Direction::Down);
			}

			if (directionX < directionY)
			{
				//Check for collisions from the left
				if (vectorX < 0)
					return Manifold(directionX, Direction::Right, targetRot);

				//Collisions form the right side
				else
					return Manifold(directionX, Direction::Left, targetRot);
			}
		}

		//Return the direction.
		return Manifold(0, Direction::None);
	}

	void Physics::ResolveCollision(Manifold* data, Object& a, float Scale)
	{
		if (data->Dir == Direction::None) return;


		if (data->Dir == Direction::Up)
		{
			a.Position.y += data->Depth;
		}

		if (data->Dir == Direction::Down)
		{
			a.Position.y -= data->Depth;

			if (a.Velocity.y > 0) a.Velocity.y = 0;
		}
		
		if (data->Dir == Direction::Left)
		{
			a.Position.x += data->Depth;

			//if (a.Velocity.x < 0) a.Velocity.x = 0;
		}

		if (data->Dir == Direction::Right)
		{
			a.Position.x -= data->Depth;
			
			//if (a.Velocity.x > 0) a.Velocity.x = 0;
		}

		if (data->rotation != 0)
		{
			//a.Position.x -= data->rotation / (45 / a.Scale.x);
		}
	}

	bool Physics::SimpleCollision(Object& a, Object& b)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a.Position.x;
		rightA = a.Position.x + a.Scale.x;
		topA = a.Position.y;
		bottomA = a.Position.y + a.Scale.y;

		//Calculate the sides of rect B
		leftB = b.Position.x;
		rightB = b.Position.x + b.Scale.x;
		topB = b.Position.y;
		bottomB = b.Position.y + b.Scale.y;

		//If any of the sides from A are outside of B
		if (bottomA <= topB)
			return false;

		if (topA >= bottomB)
			return false;

		if (rightA <= leftB)
			return false;

		if (leftA >= rightB)
			return false;

		//If none of the sides from A are outside B
		return true;
	}
}