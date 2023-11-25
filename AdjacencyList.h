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
#include "utilsDDP.h"
#include "ComparePointDistQueue.h"


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
		
		
		PQueue pq = PQueue();
		pq.insertQueue(source, nullptr, 0);

		PPU ref = pq.top();

		std::shared_ptr<Point> pointPivot = ref.first;
		unsigned int distPair = ref.second;

		//std::shared_ptr<Point> ref = source;
		unsigned int sourceId = getIdOfPoint(source, bptr);
		std::list<std::shared_ptr<Point>> lstOfSource = this->themap[sourceId];
		std::list<std::shared_ptr<Point>> lstOfVertex = pq.trueNeighborg(lstOfSource);


		while (!pointsAreEquivalent(pointPivot, dest, bptr))
		{
			ref = pq.top();
			std::shared_ptr<Point> pointPivot = ref.first;
			unsigned int distPair = ref.second;

			unsigned int Id = getIdOfPoint(pointPivot, bptr);
			lstOfSource = this->themap[Id];
			lstOfVertex = pq.trueNeighborg(lstOfSource);

			std::list<std::shared_ptr<Point>>::iterator it;
			for (it = lstOfVertex.begin(); it != lstOfVertex.end(); ++it)
			{
				unsigned int distanceBetween = distPair + weight(*pointPivot.get(), (*(*it).get()));
				if (!pq.isInQueue(*it))
				{
					pq.insertQueue(*it, pointPivot, distanceBetween);
				}
				else
				{
					PPU pairIt = pq.getValue(*it);
					unsigned int qdist = pairIt.second;

					if (distanceBetween <= qdist)
					{
						pq.updateQueue(*it, pointPivot, distanceBetween);
					}
				}
			}

			pq.pop();


		}

		pq.printPath(source, dest, bptr);

	

		
	
	}

};



