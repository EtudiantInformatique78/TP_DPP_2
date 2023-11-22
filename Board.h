#pragma once
#include <iostream>
#include <deque>
#include <iostream>

class Point
{
private:
	int coordX;
	int coordY;
	std::string name;

public:
	//constructor
	Point(int _coordX, int _coordY, std::string _name)
	{
		coordX = _coordX;
		coordY = _coordY;
		name = _name;
	}

	//destructor
	~Point()
	{
		std::cout << "point destroyed" << std::endl;
	}
};

class Board
{
private:
	std::deque<std::deque<int>> board;

public:
	Board() {
		for(int i =1 ; i <= 5; i++)
		{
			
			std::deque<int> deck;
			for(int j=1; j <= 6; j++)
			{
				deck.push_back(i*j);
			}
			board.push_back(deck);
			
		}
	};
	virtual ~Board() {};


	void printBoard()
	{
		std::deque<std::deque<int>>::iterator it1;
		std::deque<int>::iterator it2;

		std::cout << "----------------------------------" << std::endl;
		  
		for(it1 = board.begin(); it1 != board.end(); it1++)
		{
			for(it2 = (*it1).begin(); it2 != (*it1).end() ; it2++ )
			{
				std::cout << " | " << (*it2) << " | ";
			}
			std::cout << std::endl;
		}

		std::cout << "----------------------------------" << std::endl;
	}

	//add a node to the end of a column (so as a new row)
	void push_back_column()
	{
		std::deque<int> newRow;
		std::deque<int>::iterator it;
		int i = 0;
		for(it = board[0].begin(); it != board[0].end(); it++)
		{
			newRow.push_front(0);
		}
		board.push_back(newRow);
	}

};