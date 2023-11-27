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
    adj_point.Dijkstra(std::shared_ptr<Point>(new Point(-7, 5)), std::shared_ptr<Point>(new Point(9, 4)));


    ContextPathFinding cpf;
    std::shared_ptr<Point> p1 = std::shared_ptr<Point>(new Point(4, -2));

    std::shared_ptr<Point> p2 = std::shared_ptr<Point>(new Point(6, 17));

    cpf.setStrategy(std::shared_ptr<PathFindingStrategy>(new AStarStrategy()));

    cpf.findPath(*bptr.get(), p1, p2);

    (*bptr.get()).printBoard();
    

    return 0;

}
