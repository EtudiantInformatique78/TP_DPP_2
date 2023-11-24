#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <cmath>
#include <map>
#include <queue>
#include <set>

#include "Board.h"
#include "structCoord.h"



pairInt coordToInd(int x, int y, int initialX, int initialY)
{
	pairInt pair = {};
	pair.x = x - initialX;
	pair.y = y - initialY;
	return pair;
}

pairInt indToCoord(int x_ind, int y_ind, int initialX, int initialY)
{
	pairInt pair = {};
	pair.x = x_ind + initialX;
	pair.y = y_ind + initialY;
	return pair;
}

// Cantor pairing function
/*
It's a simple bijection between NxN and N
*/
unsigned int coordinateToNumber(unsigned int x, unsigned int y)
{
	unsigned int sum1 = x + y;
	unsigned int sum2 = x + y + 1;
	unsigned int result = static_cast<unsigned int>( (sum1 * sum2) / 2 + y);
	return result;
}
// The inverse function of Cantor pairing function
void compute_x_y_from_z(unsigned int z, unsigned int& x, unsigned int& y)
{
	
	double numerator = std::sqrt(8 * z + 1) - 1;
	unsigned int w = std::floor(numerator/2);

	unsigned int t = static_cast<unsigned int>((w * w + w) / 2);

	y = z - t;
	x = w - y;

}


unsigned int getIdOfPoint(std::shared_ptr<Point> p, std::shared_ptr<Board> bptr)
{
	int x_coord = p.get()->getX();
	int y_coord = p.get()->getY();

	int initX = bptr.get()->getInitialX();
	int initY = bptr.get()->getInitialY();

	pairInt pairSource = coordToInd(x_coord, y_coord, initX, initY);

	unsigned int z = coordinateToNumber(pairSource.x, pairSource.y);
	return z;
}


class AdjacencyListPoint
{
private:
	std::map<unsigned int, std::list<std::shared_ptr<Point>>> themap;
	std::shared_ptr<Board> bptr;

public:
	AdjacencyListPoint(std::shared_ptr<Board> b)
	{
		this->bptr = b;
		themap = {};
	};
	virtual ~AdjacencyListPoint() {};

	void add_edge(std::shared_ptr<Point> pu, std::shared_ptr<Point> pv)
	{
		int initialX = bptr.get()->getInitialX();
		int initialY = bptr.get()->getInitialY();

		pairInt indicesU = coordToInd(pu.get()->getX(), pu.get()->getY(), initialX, initialY);

		unsigned int zU = coordinateToNumber(indicesU.x, indicesU.y);

		if(themap.find(zU) == themap.end())
		{
			// Not in the map
			// creation of the list
			std::list<std::shared_ptr<Point>> listPtr;
			listPtr.push_back(pv);
			themap.insert(std::pair<unsigned int, std::list<std::shared_ptr<Point>>>(zU, listPtr ));
		}
		else
		{
			themap.at(zU).push_back(pv);
		}


		pairInt indicesV = coordToInd(pv.get()->getX(), pv.get()->getY(), initialX, initialY);

		unsigned int zV = coordinateToNumber(indicesV.x, indicesV.y);

		if (themap.find(zV) == themap.end())
		{
			// Not in the map
			// creation of the list
			std::list<std::shared_ptr<Point>> listPtr;
			listPtr.push_back(pu);
			themap.insert(std::pair<unsigned int, std::list<std::shared_ptr<Point>>>(zV, listPtr));
		}
		else
		{
			themap.at(zV).push_back(pu);
		}

	}

	void setMap()
	{
		std::deque<std::deque<std::shared_ptr<Point>>> board = this->bptr.get()->getBoard();

		std::deque<std::deque<std::shared_ptr<Point>>>::iterator it1;
		std::deque<std::shared_ptr<Point>>::iterator it2;

		//std::cout << "----------------------------------" << std::endl;

		for (it1 = board.begin(); it1 != board.end(); it1++)
		{
			for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
			{

				
				if((*it2).get()->isPassabe())
				{
				
					std::list<std::shared_ptr<Point>> listNeigh = this->bptr.get()->lstNeighborg((*it2));

					std::list<std::shared_ptr<Point>>::iterator it3;

					for (it3 = listNeigh.begin(); it3 != listNeigh.end(); ++it3)
					{
						if ((*it3).get()->isPassabe())
						{
							add_edge(*it2, *it3);
						}
					}

				}

				

				//std::cout << *((*it2).get());

				//std::cout << " | (" << (*it2)->getX() << "," << (*it2)->getY() << ") | ";
			}
			//std::cout << std::endl;
		}

		//std::cout << "----------------------------------" << std::endl;


	}

	void displayAdjList()
	{
		std::map<unsigned int, std::list<std::shared_ptr<Point>>>::iterator it;
		for(it = themap.begin(); it != themap.end(); ++it)
		{
			unsigned int x_ind;
			unsigned int y_ind;
			unsigned int z = (it)->first;
			std::list<std::shared_ptr<Point>> list = it->second;
			std::list<std::shared_ptr<Point>>::iterator itList;


			int initialX = bptr.get()->getInitialX();
			int initialY = bptr.get()->getInitialY();


			compute_x_y_from_z(z, x_ind, y_ind);

			pairInt p = indToCoord(x_ind, y_ind, initialX, initialY);
			std::cout << "(" << p.x << "," << p.y << ")" << " : ";
			
			for(itList = list.begin(); itList != list.end(); ++itList)
			{
				std::cout << "(" << itList->get()->getX() << "," << itList->get()->getY() << ")" << " ; ";
			}

			std::cout << std::endl;
		}
	}

	void DijkstraAlgorithm(std::shared_ptr<Point> source, std::shared_ptr<Point> dest)
	{

		unsigned int sourceId = getIdOfPoint(source, bptr);

		std::list<std::shared_ptr<Point>> lstOfSource = this->themap[sourceId];

		// unsigned int for the vertice u
		// int for the distance
		std::map<unsigned int, int> dist = {};

		// unsigned int for the vertice u and the previous one 
		// 
		std::map<unsigned int, unsigned int> prev = {};

		dist.insert(std::pair<unsigned int, int>(sourceId, 0));

		std::queue<std::shared_ptr<Point>> Q;

		std::list<std::shared_ptr<Point>>::iterator it;
		for(it = lstOfSource.begin(); it != lstOfSource.end(); ++it)
		{
			Q.push(*it);
		}

		std::set<std::shared_ptr<Point>> S;

		while (!Q.empty())
		{
			std::shared_ptr<Point> p = Q.front();
			Q.pop();

			S.insert(p);

			std::list<std::shared_ptr<Point>> neigh = bptr.get()->lstNeighborg(p);

			std::list<std::shared_ptr<Point>>::iterator itNeigh;

			for(itNeigh = neigh.begin(); itNeigh != neigh.end(); ++itNeigh)
			{
							
			}

		}

		

	}

};



