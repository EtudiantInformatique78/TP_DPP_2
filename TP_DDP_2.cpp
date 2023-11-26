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


void printPoint(std::shared_ptr<Point> p)
{
    std::cout << "(" << p.get()->getX() << "," << p.get()->getY() << ")";
}



int main()
{

    //Board b = Board();
    
    std::shared_ptr<Board> bptr = std::shared_ptr<Board>(new Board());
    AdjacencyListPoint adj_point = AdjacencyListPoint(bptr);
    adj_point.setMap();
    bptr.get()->printBoard();
    //adj_point.DijkstraAlgorithm(std::shared_ptr<Point>(new Point(-7, 5)), std::shared_ptr<Point>(new Point(-5, 5)));

    adj_point.Dijkstra(std::shared_ptr<Point>(new Point(-7, 5)), std::shared_ptr<Point>(new Point(-5, 5)));

    /*

        custom_priority_queue cpq;

    std::shared_ptr<Point> p0 = std::shared_ptr<Point>(new Point(0, 0));
    std::shared_ptr<Point> p1 = std::shared_ptr<Point>(new Point(0, 1));
    std::shared_ptr<Point> p2 = std::shared_ptr<Point>(new Point(0, 2));
    std::shared_ptr<Point> p3 = std::shared_ptr<Point>(new Point(0, 3));

    std::pair < std::shared_ptr<Point>, PPU> pair0 = std::pair < std::shared_ptr<Point>, PPU>(p0, { nullptr,  2 });
    std::pair < std::shared_ptr<Point>, PPU> pair1 = std::pair < std::shared_ptr<Point>, PPU>(p1, { p0,  19 });
    std::pair < std::shared_ptr<Point>, PPU> pair2 = std::pair < std::shared_ptr<Point>, PPU>(p2, { p1,  7});
    std::pair < std::shared_ptr<Point>, PPU> pair3 = std::pair < std::shared_ptr<Point>, PPU>(p3, { p2,  3 });

    cpq.push(pair0);
    cpq.push(pair1);
    cpq.push(pair2);
    cpq.push(pair3);
    unsigned int i = 0;

    while (i < 3)
    {
        printPoint(cpq.top().first);
        std::cout << "  ;  ";
        if(cpq.top().second.first != nullptr)
        {
            printPoint(cpq.top().second.first);
        }

        std::cout <<  " ; dist = " << cpq.top().second.second;

        cpq.pop();

        if (!cpq.empty())
        {
            std::cout << ", ";
        }
        i += 1;

    }
    std::cout << std::endl;

    std::pair < std::shared_ptr<Point>, PPU> pair00 = std::pair < std::shared_ptr<Point>, PPU>(p0, { p2,  21 });
    std::pair < std::shared_ptr<Point>, PPU> pair10 = std::pair < std::shared_ptr<Point>, PPU>(p1, { p3,  3 });

    cpq.push(pair00);
    cpq.push(pair10);


    while (!cpq.empty())
    {
        printPoint(cpq.top().first);
        std::cout << "  ;  ";
        if (cpq.top().second.first != nullptr)
        {
            printPoint(cpq.top().second.first);
        }

        std::cout << " ; dist = " << cpq.top().second.second;

        cpq.pop();

        if (!cpq.empty())
        {
            std::cout << ", ";
        }

    }
    std::cout << std::endl;

    */
    


    return 0;

}
