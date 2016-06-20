//Copyright 2016, Cameron bell, All rights reserved

#include "PathFinding.h"

namespace Penguin
{
	PathFinding::PathFinding()
	{
		initializedStartGoal = false;
		foundGoal = false;
	}


	PathFinding::~PathFinding()
	{
	}

	void PathFinding::FindPath(SDL_Renderer* rend, Vector current, Vector target, std::map<int, Tile>* obst)
	{
		if (!initializedStartGoal)
		{
			Obsticals = obst;

			targetCurrent = target;

			visitedList.clear();
			pathToGoal.clear();
			openList.clear();

			for(int i = 0; i < openList.size(); i++)
				delete openList[i];

			for (int i = 0; i < visitedList.size(); i++)
				delete visitedList[i];

			for (int i = 0; i < pathToGoal.size(); i++)
				delete pathToGoal[i];

			SearchCell start;
			start.coordinate = current;

			SearchCell goal;
			goal.coordinate = target;

			setStartGoal(start, goal);

			initializedStartGoal = true;
		}

		if (initializedStartGoal) continuePath(rend);
	}

	void PathFinding::setStartGoal(SearchCell start, SearchCell goal)
	{
		startCell = new SearchCell(start.coordinate, NULL);
		goalCell = new SearchCell(goal.coordinate, NULL);

		startCell->G = 0;
		startCell->H = startCell->ManHattanDistance(goalCell);
		startCell->parent = NULL;

		openList.push_back(startCell);
	}

	SearchCell* PathFinding::getNextCell()
	{
		float bestScore = 999999.0f;
		int cellIndex = -1;

		SearchCell* nextCell = NULL;

		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->GetScore() < bestScore)
			{
				bestScore = openList[i]->GetScore();
				cellIndex = i;
			}
		}

		if (cellIndex >= 0)
		{
			nextCell = openList[cellIndex];
			visitedList.push_back(nextCell);

			openList.erase(openList.begin() + cellIndex);
		}

		return nextCell;
	}

	void PathFinding::pathOpened(SDL_Renderer* rend, Vector pos, float newCost, SearchCell *parent)
	{
		typedef std::map<int, Tile>::iterator it_type;
		for (it_type iterator = Obsticals->begin(); iterator != Obsticals->end(); iterator++)
		{
			if (iterator->second.Position == pos)
			{
				newCost = 40 * 1000;
			}
		}

		int id = pos.y * 40 + pos.x;

		for (int i = 0; i < visitedList.size(); i++)
		{
			if (id == visitedList[i]->ID)
				return;
		}

		SearchCell* newChild = new SearchCell(pos, parent);
		newChild->G = newCost;
		newChild->H = parent->ManHattanDistance(goalCell);

		for (int i = 0; i < openList.size(); i++)
		{
			SDL_Rect temp = { openList[i]->coordinate.x, openList[i]->coordinate.y, 40, 40 };
			SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
			SDL_RenderFillRect(rend, &temp);

			if (id == openList[i]->ID)
			{
				float newScore = newChild->G + newCost + openList[i]->H;

				if (openList[i]->GetScore() > newScore)
				{
					openList[i]->G = newChild->G + newCost;
					openList[i]->parent = newChild;
				}
				else
				{
					delete newChild;
					return;
				}
			}
		}

		openList.push_back(newChild);
	}

	void PathFinding::continuePath(SDL_Renderer* rend)
	{
		for (int i = 0; i < 4; i++)
		{
			if (openList.empty())
			{
				Debug::Fatal("Could not find target!");
				return;
			}

			SearchCell* currentCell = getNextCell();

			if (currentCell->ID == goalCell->ID)
			{
				goalCell->parent = currentCell->parent;

				SearchCell* getPath;

				for (getPath = goalCell; getPath != NULL; getPath = getPath->parent)
				{
					pathToGoal.push_back(&getPath->coordinate);
				}

				foundGoal = true;
				return;
			}

			else
			{
				//All directions from the cell
				Vector RightPosition = Vector(currentCell->coordinate.x + 40, currentCell->coordinate.y);
				Vector LeftPosition = Vector(currentCell->coordinate.x - 40, currentCell->coordinate.y);
				Vector UpPosition = Vector(currentCell->coordinate.x, currentCell->coordinate.y + 40);
				Vector DownPosition = Vector(currentCell->coordinate.x, currentCell->coordinate.y - 40);

				//Open all directional paths
				pathOpened(rend, RightPosition, currentCell->G + 40, currentCell);
				pathOpened(rend, LeftPosition, currentCell->G + 40, currentCell);
				pathOpened(rend, UpPosition, currentCell->G + 40, currentCell);
				pathOpened(rend, DownPosition, currentCell->G + 40, currentCell);

				for (int i = 0; i < openList.size(); i++)
				{
					if (currentCell->ID == openList[i]->ID)
						openList.erase(openList.begin() + i);
				}
			}
		}

		//continuePath();
	}

	Vector PathFinding::NextPathPos(Object* obj)
	{
		int index = 1;

		Vector nextPos = *pathToGoal[pathToGoal.size() - index];

		Vector target = nextPos - obj->Position;
		
		float targetMagnitude = sqrt(pow(target.x, 2) + pow(target.y, 2));

		if (index < pathToGoal.size())
		{
			//if (targetMagnitude > obj->Scale.x / 2)
			//{
				pathToGoal.erase(pathToGoal.end() - index);
			//}
		}

		return nextPos;
	}

	bool PathFinding::changedCell(Vector pos)
	{
		Vector reclacPos = Vector(int(pos.x / 40), int(pos.y / 40));
		Vector recalcPrev = Vector(int(targetCurrent.x / 40), int(targetCurrent.y / 40));

		if (recalcPrev != reclacPos)
		{
			targetCurrent = pos;
			return true;
		}

		return false;
	}
}