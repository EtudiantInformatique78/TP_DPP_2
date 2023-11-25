// TP_DDP_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <vector>
#include <queue>

#include "Board.h"
#include "PathFindingStrategy.h"
#include "AdjacencyList.h"
#include "ComparePointDistQueue.h"


#define PPU std::pair<std::shared_ptr<Point>, unsigned int>




int main()
{

    //Board b = Board();
    
    std::shared_ptr<Board> bptr = std::shared_ptr<Board>(new Board());
    AdjacencyListPoint adj_point = AdjacencyListPoint(bptr);
    adj_point.setMap();
    bptr.get()->printBoard();
    adj_point.DijkstraAlgorithm(std::shared_ptr<Point>(new Point(-7, 5)), std::shared_ptr<Point>(new Point(-5, 5)));

    
    /*
    custom_priority_queue cpq;


    std::shared_ptr<Point> p0 = std::shared_ptr<Point>(new Point(0, 0));
    std::shared_ptr<Point> p1 = std::shared_ptr<Point>(new Point(0, 1));
    std::shared_ptr<Point> p2 = std::shared_ptr<Point>(new Point(0, 2));
    std::shared_ptr<Point> p3 = std::shared_ptr<Point>(new Point(0, 3));


    std::pair < std::shared_ptr<Point>, PPU> pair0 = std::pair < std::shared_ptr<Point>, PPU>(p0, { nullptr,  2 });
    std::pair < std::shared_ptr<Point>, PPU> pair1 = std::pair < std::shared_ptr<Point>, PPU>(p1, { p2,  7});
    std::pair < std::shared_ptr<Point>, PPU> pair2 = std::pair < std::shared_ptr<Point>, PPU>(p2, { p3,  3 });

    cpq.push(pair0);
    cpq.push(pair1);
    cpq.push(pair2);

    while (!cpq.empty())
    {
        std::cout << cpq.top().first << "  ;  " << cpq.top().second.first << " ; dist = " << cpq.top().second.second;
        cpq.pop();

        if (!cpq.empty())
        {
            std::cout << ", ";
        }
    }
    */

    return 0;

}
