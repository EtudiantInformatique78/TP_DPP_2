// TP_DDP_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <deque>

#include "Board.h"

int main()
{
    //std::cout << "Hello World!\n";
    Board b = Board();
    b.printBoard();
    
    b.push_west_back(2);
    std::cout << std::endl;
    b.printBoard();

    b.push_west_front(5);

    std::cout << std::endl;
    b.printBoard();
    /*
    b.push_north_back(1);
    std::cout << std::endl;
    b.printBoard();

    b.push_north_front(3);
    std::cout << std::endl;
    b.printBoard();

    b.push_north_back(1, 3);
    std::cout << std::endl;
    b.printBoard();

    b.push_north_front(5, 2);
    std::cout << std::endl;
    b.printBoard();
    */

    

    /*
    std::deque<int> gquizz;
    gquizz.push_back(10);
    gquizz.push_front(20);
    gquizz.push_back(30);
    gquizz.push_front(15);

    std::deque<int>::iterator it;
    for(it = gquizz.begin(); it != gquizz.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "Size of gquizz : " << gquizz.size() << std::endl;
    std::cout << "Max Size of gquizz : " << gquizz.max_size() << std::endl;

    std::cout << "gquizz.at(2): " << gquizz.at(2) << std::endl;

    std::cout << "gquizz.front(): " << gquizz.front() << std::endl;
    std::cout << "gquizz.back(): " << gquizz.back() << std::endl;
    */
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
