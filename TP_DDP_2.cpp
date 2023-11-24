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

    //adj_point.displayAdjList();
    
    adj_point.DijkstraAlgorithm(std::shared_ptr<Point>(new Point(-7, 5)), std::shared_ptr<Point>(new Point(-5, 5)));
    


    return 0;

}
