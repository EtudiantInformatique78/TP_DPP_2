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
		//std::cout << "point destroyed" << std::endl;
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
		const int initialY = -2;
		const int initialX = -2;
		const int sizeInit = 4;

		const int lastY = initialY + sizeInit;
		const int lastX = initialX + sizeInit;

		for (int i = initialY; i <= lastY; i++)
		{

			std::deque<std::shared_ptr<Point>> deck;
			for (int j = initialX; j <= lastX; j++)
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
	
	//push a point in the map
	void push_point(int coordX, int coordY)
	{

		//init values needed to check where to extend the map
		int sizeLine = board.at(0).size();
		int sizeColumn = board.size();
		int maxIndexLine = board.at(0).at(sizeLine - 1)->getX();
		int maxIndexColumn = board.at(sizeColumn - 1).at(0)->getY();
		int minIndexLine = board.at(0).at(0)->getX();
		int minIndexColumn = board.at(0).at(0)->getY();

		//check if extend west
		if (coordX < minIndexLine)
		{
			for (int i = minIndexLine; i > coordX; i--)
			{
				push_west();
			}
		}

		//check if extend est
		if (coordX > maxIndexLine)
		{
			for (int i = maxIndexLine; i < coordX; i++)
			{
				push_est();
			}
		}

		//check if extend north
		if (coordY < minIndexColumn)
		{
			for (int i = minIndexColumn; i > coordY; i--)
			{
				push_north();
			}
		}

		//check if extend south
		if (coordY > maxIndexColumn)
		{
			for (int i = maxIndexColumn; i < coordY; i++)
			{
				push_south();
			}
		}
	}

	void push_est()
	{
		std::deque<std::deque<std::shared_ptr<Point>>>::iterator it;
		unsigned int size = static_cast<unsigned int>(board.at(0).size());
		int cursor = board.at(0).at(size - 1)->getX();

		int j = board.at(0).at(0)->getY();	
		for (it = board.begin(); it != board.end(); it++)
		{
				(*it).push_back(std::shared_ptr<Point>(new Point(cursor + 1 , j)));
				j++;
		}

	}

	void push_south()
	{
		std::deque<std::shared_ptr<Point>> newRow;
		int sizeLine = board.at(0).size();
		int sizeColumn = board.size();
		int maxIndexLine = board.at(0).at(sizeLine -1)->getX()+1;
		int maxIndexColumn = board.at(sizeColumn - 1).at(0)->getY();
		for (int i = board.at(0).at(0)->getX(); i < maxIndexLine; i++)
		{
			newRow.push_back(std::shared_ptr<Point>(new Point(i, maxIndexColumn + 1)));
		}
		board.push_back(newRow);
	}

	
	void push_west()
	{
		std::deque<std::deque<std::shared_ptr<Point>>>::iterator it;
		unsigned int size = static_cast<unsigned int>(board.at(0).size());
		int cursor = board.at(0).at(0)->getX();
		int j = board.at(0).at(0)->getY();
		for (it = board.begin(); it != board.end(); it++)
		{
			(*it).push_front(std::shared_ptr<Point>(new Point(cursor - 1, j)));
			j++;
		}
	}

	void push_north()
	{
		std::deque<std::shared_ptr<Point>> newRow;
		int sizeLine = board.at(0).size();
		int sizeColumn = board.size();
		int maxIndexLine = board.at(0).at(sizeLine - 1)->getX() + 1;
		int minIndexColumn = board.at(0).at(0)->getY();
		for (int i = board.at(0).at(0)->getX(); i < maxIndexLine; i++)
		{
			newRow.push_back(std::shared_ptr<Point>(new Point(i, minIndexColumn - 1)));
		}
		board.push_front(newRow);
	}
};