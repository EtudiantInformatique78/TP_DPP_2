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