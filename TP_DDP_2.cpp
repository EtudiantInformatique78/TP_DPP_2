// TP_DDP_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <vector>

#include "Board.h"

#include "PathFindingStrategy.h"


int main()
{
    Board b = Board();
    
    ContextPathFinding cpf;

    std::shared_ptr<Point> p1 = std::shared_ptr<Point>(new Point(4, -2));

    std::shared_ptr<Point> p2 = std::shared_ptr<Point>(new Point(6, 17));

    cpf.setStrategy(std::shared_ptr<PathFindingStrategy>(new AStarStrategy()));

    cpf.findPath(b, p1, p2);

    
    std::shared_ptr<Point> point = b.get_point(2, 5);

    std::cout << "(" << point->getX() << "," << point->getY() << ") : "  << std::endl;
    b.printBoard();
}
