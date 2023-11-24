#pragma once
#include "Board.h"
#include <iostream>
#include <cmath>

struct Node
{
	std::shared_ptr<Point> point;
	double cost;
	double heuristic;
};

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
		std::vector<Node> closedList;
		std::vector<Node> openedList;
		std::vector<Node> finalPath;
		Node startNode = { start, 0, heuristicFunction(start, objective) };
		openedList.push_back(startNode);

		//enter the algorithm
		while (openedList.size() > 0)
		{
			Node actualPoint = openedList[0];
			openedList.erase(openedList.begin());

			//check if we arrived
			if (actualPoint.point->getX() == objective->getX() && actualPoint.point->getY() == objective->getY())
			{
				finalPath.push_back(actualPoint);
				std::reverse(closedList.begin(), closedList.end());
				for (Node node : closedList)
				{
					std::cout << node.point->getX() << "-" << node.point->getY() << std::endl;
					finalPath.push_back(node);
				}
				std::reverse(finalPath.begin(), finalPath.end());
				break;
			}

			//check all neighbor and change its value if necessary

			//north-est (<^) neighbor
			std::shared_ptr<Point> neighbor = board.get_point(actualPoint.point->getX() - 1, actualPoint.point->getY() - 1);
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, true);

			//north (^) neighbor
			neighbor = board.get_point(actualPoint.point->getX(), actualPoint.point->getY() - 1);
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, false);

			//north-west (^>) neighbor
			neighbor = board.get_point(actualPoint.point->getX() + 1, actualPoint.point->getY() - 1);
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, true);

			//west (>) neighbor
			neighbor = board.get_point(actualPoint.point->getX() + 1, actualPoint.point->getY());
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, false);

			//south-west (v>) neighbor
			neighbor = board.get_point(actualPoint.point->getX() + 1, actualPoint.point->getY() + 1);
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, true);

			//south (v) neighbor
			neighbor = board.get_point(actualPoint.point->getX(), actualPoint.point->getY() + 1);
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, false);

			//south-est (<v) neighbor
			neighbor = board.get_point(actualPoint.point->getX() - 1, actualPoint.point->getY() + 1);
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, true);

			//est (<) neighbor
			neighbor = board.get_point(actualPoint.point->getX() - 1, actualPoint.point->getY());
			checkNeighbor(neighbor, closedList, openedList, actualPoint, objective, false);

			if (closedList.empty())
			{
				closedList.push_back(actualPoint);
				std::cout << "adding (" << actualPoint.point->getX() << "," << actualPoint.point->getY() << ") to closedList" << std::endl;
			}

			bool founded = false;
			for (Node node : closedList)
			{
				if (node.point->getX() == actualPoint.point->getX() && node.point->getY() == actualPoint.point->getY())
				{
					founded = true;
				}
			}

			if (!founded)
			{
				closedList.push_back(actualPoint);
				std::cout << "adding (" << actualPoint.point->getX() << "," << actualPoint.point->getY() << ") to closedList" << std::endl;
			}
		}
		std::cout << "best path from (" << start->getX() << "," << start->getY() << ") to (" << objective->getX() << "," << objective->getY() << ") :" << std::endl;
		for (Node node : finalPath)
		{
			std::cout << "(" << node.point->getX() << "," << node.point->getY() << ")";
		}
		std::cout << std::endl;
	}

	void checkNeighbor(std::shared_ptr<Point> neighbor, std::vector<Node> &closedList, std::vector<Node> &openedList, Node actual, std::shared_ptr<Point> objective, bool isDiagonale)
	{
		if (neighbor == nullptr)
		{
			std::cout << "got out of the map" << std::endl;
			return;
		}
		if (!neighbor->isPassabe())
		{
			std::cout << "(" << neighbor->getX() << "," << neighbor->getY() << ") not possible" << std::endl;
			return;
		}

		bool isInClosedList = false;
		bool isInOpenedListAndLessCost = false;
		for (Node node : closedList)
		{
			if (node.point->getX() == neighbor->getX() && node.point->getY() == neighbor->getY())
			{
				return;
			}
		}
		for (Node node : openedList)
		{
			if (node.point->getX() == neighbor->getX() && node.point->getY() == neighbor->getY())
			{
				return;
			}
		}

		double cost;
		if (isDiagonale)
		{
			cost = sqrt(2);
		}
		else
		{
			cost = 1;
		}

		Node neighborNode = { neighbor, actual.cost + cost, 0 };
		neighborNode.heuristic = cost * 2 + heuristicFunction(neighborNode.point, objective) * 3;
		int i = 0;
		if (openedList.size() != 0)
		{
			while (neighborNode.heuristic > openedList.at(i).heuristic && i < openedList.size())
			{
				i++;
				if (i == openedList.size())
				{
					break;
				}
			}
		}
		std::cout << "adding (" << neighborNode.point->getX() << "," << neighborNode.point->getY() << ") to openedList with cost :" << neighborNode.heuristic << std::endl;
		openedList.insert(openedList.begin() + i, neighborNode);
		
	}

	double heuristicFunction(std::shared_ptr<Point> point, std::shared_ptr<Point> goal)
	{
		return std::sqrt(std::pow(point->getX() - goal->getX(), 2) + std::pow(point->getY() - goal->getY(), 2));
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