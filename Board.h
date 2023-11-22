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
		for (int i = 1; i <= 5; i++)
		{

			std::deque<int> deck;
			for (int j = 1; j <= 6; j++)
			{
				deck.push_back(j);
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

		for (it1 = board.begin(); it1 != board.end(); it1++)
		{
			for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
			{
				std::cout << " | " << (*it2) << " | ";
			}
			std::cout << std::endl;
		}

		std::cout << "----------------------------------" << std::endl;
	}

	void push_north_back(int i)
	{
		std::deque<std::deque<int>>::iterator it;
		for(it = board.begin(); it != board.end(); it++)
		{
			if(it == board.begin())
			{
				(*it).push_back(i);
			}
			else
			{
				(*it).push_back(0);
			}
		}

		//std::cout << "Tata" << std::endl;
	}

	void push_north_back(int value, int index)
	{
		std::deque<std::deque<int>>::iterator it;
		int ind = 0;
		for (it = board.begin(); it != board.end(); it++)
		{
			if(ind == index)
			{
				(*it).push_back(value);
			}			
			else
			{
				(*it).push_back(0);
			}
			ind += 1;
		}
	}

	void push_north_front(int i)
	{
		std::deque<std::deque<int>>::iterator it;
		for (it = board.begin(); it != board.end(); it++)
		{
			if (it == board.begin())
			{
				(*it).push_front(i);
			}
			else
			{
				(*it).push_front(0);
			}
		}
	}

	void push_north_front(int value, int index)
	{
		std::deque<std::deque<int>>::iterator it;
		int ind = 0;
		for (it = board.begin(); it != board.end(); it++)
		{
			if (ind == index)
			{
				(*it).push_front(value);
			}
			else
			{
				(*it).push_front(0);
			}
			ind += 1;
		}
	}


	void push_west_back(int value)
	{
		std::deque<int> newRow;
		unsigned int size = board.at(0).size();
		for(unsigned int i = 0; i < size ; i++)
		{
			if(i == 0)
			{
				newRow.push_back(value);
			}
			else
			{
				newRow.push_back(0);
			}
		}
		board.push_back(newRow);
	}

	void push_west_back(int value, int index)
	{
		std::deque<int> newRow;
		unsigned int size = board.at(0).size();
		for (unsigned int i = 0; i < size; i++)
		{
			if (i == index)
			{
				newRow.push_back(value);
			}
			else
			{
				newRow.push_back(0);
			}
		}
		board.push_back(newRow);
	}

	void push_west_front(int value)
	{
		std::deque<int> newRow;
		unsigned int size = board.at(0).size();
		for(unsigned int i = 0; i < size ; i++)
		{
			if(i == 0)
			{
				newRow.push_back(value);
			}
			else
			{
				newRow.push_back(0);
			}
		}
		board.push_front(newRow);
	}

	void push_west_front(int value, int index)
	{
		std::deque<int> newRow;
		unsigned int size = board.at(0).size();
		for (unsigned int i = 0; i < size; i++)
		{
			if (i == index)
			{
				newRow.push_back(value);
			}
			else
			{
				newRow.push_back(0);
			}
		}
		board.push_front(newRow);
	}
};