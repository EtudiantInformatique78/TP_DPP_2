#pragma once
#include "Board.h"
#include <iostream>

class PathFindingStrategy
{
public:
	virtual ~PathFindingStrategy() {};
	virtual void findPath(Board& board, std::shared_ptr<Point> objective, std::shared_ptr<Point> start) = 0;
};

class AStarStrategy : public PathFindingStrategy
{
	void findPath(Board& board, std::shared_ptr<Point> objective, std::shared_ptr<Point> start)
	{
		std::cout << "A* path finding algorithm" << std::endl;
		//init the two lists
		std::vector<std::shared_ptr<Point>> closedList;
		std::vector<std::shared_ptr<Point>> openedList;
		openedList.push_back(start);

		//enter the algorithm
		while (openedList.size() > 0)
		{
			std::shared_ptr<Point> actualPoint = openedList[0];
			openedList.erase(openedList.begin());

			//check if we arrived
			if (actualPoint->getX() == objective->getX() && actualPoint->getY() == objective->getY())
			{
				//DO SOMETHING LIKE DISPLAY CLOSEDLIST
			}
			std::shared_ptr<Point> neighbor = board.get_point(actualPoint->getX() - 1, actualPoint->getY() - 1);


		}

	}
};

class DijkstraStrategy : public PathFindingStrategy
{
	void findPath(Board& board, std::shared_ptr<Point> objective, std::shared_ptr<Point> start)
	{
		
		
		std::cout << "Dijkstra path finding algorithm" << std::endl;
	
	
	}
};

class ContextPathFinding
{
private:
	std::shared_ptr<PathFindingStrategy> strategy;

public:
	void setStrategy(std::shared_ptr<PathFindingStrategy> _strategy)
	{
		strategy = _strategy;
	}

	void findPath(Board & board, std::shared_ptr<Point> objective, std::shared_ptr<Point> start)
	{
		strategy.get()->findPath(board, objective, start);
	}

};