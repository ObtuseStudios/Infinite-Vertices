//Copyright 2016, Cameron bell, All rights reserved

#pragma once
	
#include "Vector.h"
#include <math.h>

namespace Penguin
{
	class SearchCell
	{
	public:
		SearchCell* parent;
		Vector coordinate;

		float H;
		float G;
		int ID;

		SearchCell() : parent(NULL) {}
		SearchCell(Vector coord, SearchCell* parentRef = NULL)
			: coordinate(coord), parent(parentRef) 
		{
			ID = coordinate.y * 40 + coordinate.x;
			H = 0;
			G = 0;
		}

		float GetScore() { return G + H; }
		
		float ManHattanDistance(SearchCell* nodeEnd)
		{
			float x = (float)(fabs((float)(this->coordinate.x - nodeEnd->coordinate.x)));
			float y = (float)(fabs((float)(this->coordinate.y - nodeEnd->coordinate.y)));

			return y * 40 + x;
		}
	};
}