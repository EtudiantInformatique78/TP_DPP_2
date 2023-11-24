#pragma once
#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include "structCoord.h"




class Point
{
private:
	int coordX;
	int coordY;

	bool passable = true;

public:
	//constructor
	Point(int _coordX, int _coordY)
	{
		coordX = _coordX;
		coordY = _coordY;
	}

	Point(int _coordX, int _coordY, bool _passable)
	{
		coordX = _coordX;
		coordY = _coordY;
		passable = _passable;
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

	bool isPassabe()
	{
		return passable;
	}

	friend std::ostream& operator<<(std::ostream& out, Point& p)
	{
		if (p.passable)
		{
			out << " ";
		}
		else
		{
			out << "x";
		}
		//		out << "(" << p.coordY << "," << p.coordX << ")";
		return out;
	}
	

	void setX(int x)
	{
		coordX = x;
	}
	void setY(int y)
	{
		coordY = y;
	}
	


	
};

class Board
{
private:
	std::deque<std::deque<std::shared_ptr<Point>>> board;
	int initialY;
	int initialX;


	void setValueForAPoint(int& x, int&y, bool& passable, std::string word, std::string delimiter)
	{
		int i = 0;
		while (true) {
			size_t pos = word.find(delimiter);
			std::string token = word.substr(0, pos);

			if (i == 0)
			{
				token.erase(0, 1);
				x = std::stoi(token);
			}
			else if (i == 1)
			{
				y = std::stoi(token);
			}
			else if (i == 2)
			{
				if (token == "true)")
				{
					passable = true;
				}
				else if (token == "false)")
				{
					passable = false;
				}
			}
			//std::cout << token << std::endl;
			//i = (i + 1) % 3;
			i += 1;
			if (i == 3)
			{
				break;
			}
			word.erase(0, pos + delimiter.length());

		}


	}

public:
	Board() {

		// Default initialization
		this->initialX = 0;
		this->initialY = 0;

		// file pointer 
		std::fstream fread;

		// opens an existing csv file or creates a new file. 
		fread.open("board.csv", std::ios::in);

		std::string temp;
		std::string line;
		std::string word;

		bool firstCell = true;

		while(fread >> temp)
		{
			std::getline(fread, line);
			std::stringstream s(temp);
			//std::cout << s.str();
			std::deque<std::shared_ptr<Point>> deck;
			while(std::getline(s, word, ';'))
			{

				size_t pos = 0;
				std::string token;
				std::string delimiter = ",";
				int i = 0;
				
				int x;
				int y;
				bool passable = true;


				setValueForAPoint(x, y, passable, word, delimiter);


				if(firstCell)
				{
					this->initialX = x;
					this->initialY = y;
					firstCell = false;
				}

				std::shared_ptr<Point> ptr = std::shared_ptr<Point>(new Point(y, x, passable));
				deck.push_back(ptr);

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
				
				std::cout << *((*it2).get());
				//std::cout << " | (" << (*it2)->getX() << "," << (*it2)->getY() << ") | ";
			}
			std::cout << std::endl;
		}

		std::cout << "----------------------------------" << std::endl;
	}

	int getInitialX()
	{
		return initialX;
	}
	int getInitialY()
	{
		return initialY;
	}



	std::shared_ptr<Point> get_point(int coordX, int coordY)
	{
		int sizeLine = board.at(0).size();
		int sizeColumn = board.size();
		int maxValueX = board.at(0).at(sizeLine - 1)->getX();
		int maxValueY = board.at(sizeColumn - 1).at(0)->getY();
		int minValueX = board.at(0).at(0)->getX();
		int minValueY = board.at(0).at(0)->getY();

		if (coordX < minValueX || coordX > maxValueX || coordY < minValueY || coordY > maxValueY)
		{
			return nullptr;
		}

		return board.at(coordY - minValueY).at(coordX - minValueX);
	}
	

	std::list<std::shared_ptr<Point>> lstNeighborg(std::shared_ptr<Point> p)
	{
		std::list<std::shared_ptr<Point>> lstPoint;
		
		int x_coord = p.get()->getX();
		int y_coord = p.get()->getY();

		pairInt p1 = { x_coord-1, y_coord };
		pairInt p2 = { x_coord-1, y_coord - 1 };
		pairInt p3 = { x_coord, y_coord - 1 };
		pairInt p4 = { x_coord+1, y_coord - 1 };
		

		std::list<pairInt> lstPair = { p1, p2, p3, p4 };

		std::list<pairInt>::iterator pairIntIt;

		for(pairIntIt = lstPair.begin(); pairIntIt != lstPair.end(); ++pairIntIt)
		{
			std::shared_ptr<Point> ptr = get_point(pairIntIt->x, pairIntIt->y);
			if(ptr != nullptr)
			{
				lstPoint.push_back(ptr);
			}
		}


		return lstPoint;
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