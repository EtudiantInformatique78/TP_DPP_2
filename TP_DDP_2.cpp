// TP_DDP_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <vector>

#include "Board.h"

void AstarAlgorithm(Board board, std::shared_ptr<Point> objective, std::shared_ptr<Point> start)
{
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
        std::shared_ptr<Point> neighbor = board.get_point(actualPoint->getX()-1, actualPoint->getY()-1);


    }
}

int main()
{
    Board b = Board();
    b.printBoard();

    b.push_est();
    b.printBoard();

    b.push_south();
    b.printBoard();

    b.push_west();
    b.printBoard();

    b.push_north();
    b.printBoard();

    b.push_point(7, 7);
    b.printBoard();

    std::shared_ptr<Point> point = b.get_point(2, 5);

    std::cout << "(" << point->getX() << "," << point->getY() << ") : " << point->getCost() << std::endl;
    b.printBoard();
}
