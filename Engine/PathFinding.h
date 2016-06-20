//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include "SearchCell.h"
#include "TileMap.h"

#include <vector>

namespace Penguin
{
	class PathFinding
	{
	public:
		PathFinding();
		~PathFinding();

		void FindPath(SDL_Renderer* rend, Vector current, Vector target, std::map<int, Tile>* obst);
		Vector NextPathPos(Object* obj);

		void ClearVisitedList() { visitedList.clear(); }
		void ClearPathToGoal() { pathToGoal.clear(); }
		void ClearOpenList() { openList.clear(); }

		bool changedCell(Vector position);

		bool initializedStartGoal;
		bool foundGoal;

	private:
		void pathOpened(SDL_Renderer* rend, Vector pos, float newCost, SearchCell *parent);
		void setStartGoal(SearchCell start, SearchCell end);
		void continuePath(SDL_Renderer* rend);

		SearchCell* getNextCell();

		SearchCell* startCell;
		SearchCell* goalCell;

		std::map<int, Tile>* Obsticals;

		std::vector<SearchCell*> visitedList;
		std::vector<SearchCell*> openList;
		std::vector<Vector*> pathToGoal;

		Vector targetCurrent;
	};
}