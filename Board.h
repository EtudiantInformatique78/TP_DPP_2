#pragma once
#include <iostream>
#include <deque>
#include <iostream>

class Point
{
private:
	int coordX;
	int coordY;

public:
	//constructor
	Point(int _coordX, int _coordY)
	{
		coordX = _coordX;
		coordY = _coordY;
	}

	//destructor
	~Point()
	{
		std::cout << "point destroyed" << std::endl;
	}

	//getters & setter
	int getX()
	{
		return coordX;
	}
	int getY()
	{
		return coordY;
	}
};

class Board
{
private:
	std::deque<std::deque<std::shared_ptr<Point>>> board;

public:
	Board() {
		for (int i = 0; i <= 5; i++)
		{

			std::deque<std::shared_ptr<Point>> deck;
			for (int j = 0; j <= 6; j++)
			{
				deck.push_back(std::shared_ptr<Point>(new Point(j, i)));
			}
			board.push_back(deck);

		}
	};
	virtual ~Board() {};

	void printBoard()
	{
		std::deque<std::deque<std::shared_ptr<Point>>>::iterator it1;
		std::deque<std::shared_ptr<Point>>::iterator it2;

		std::cout << "----------------------------------" << std::endl;

		for (it1 = board.begin(); it1 != board.end(); it1++)
		{
			for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
			{
				std::cout << " | (" << (*it2)->getX() << "," << (*it2)->getY() << ") | ";
			}
			std::cout << std::endl;
		}

		std::cout << "----------------------------------" << std::endl;
	}

	/*
	void push_est(int i)
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

	void push_est(int value, int index)
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

	void push_west(int i)
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

	void push_west(int value, int index)
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


	void push_south(int value)
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

	void push_south(int value, int index)
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

	void push_north(int value)
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

	void push_north(int value, int index)
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
	*/
};