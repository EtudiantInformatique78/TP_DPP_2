// TP_DDP_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <vector>

#include "Board.h"

#include "PathFindingStrategy.h"

#include "AdjacencyList.h"


int main()
{




    unsigned int z = coordinateToNumber(40, 5);
    
    std::cout << "z = " << z << std::endl;

    unsigned int x, y ;
    
    compute_x_y_from_z(z, x, y);

    std::cout << "x = " << x << " , y = " << y << std::endl;

    //test();

    /*
    Board b = Board();

    ContextPathFinding cpf;

    cpf.setStrategy(std::shared_ptr<PathFindingStrategy>(new DijkstraStrategy()) ) ;

    std::shared_ptr<Point> p1 = std::shared_ptr<Point>(new Point(5, 3));

    std::shared_ptr<Point> p2 = std::shared_ptr<Point>(new Point(4, 6));

    cpf.findPath(b, p1, p2);

    cpf.setStrategy(std::shared_ptr<PathFindingStrategy>(new AStarStrategy()));

    cpf.findPath(b, p1, p2);


    std::shared_ptr<Point> point = b.get_point(2, 5);

    std::cout << "(" << point->getX() << "," << point->getY() << ") : "  << std::endl;
    b.printBoard();
    */

}
