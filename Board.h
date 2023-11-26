#pragma once
#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <sstream>

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
		return out;
	}
	
	bool isEqualsTo(Point pointToCompare)
	{
		return coordX == pointToCompare.getX() && coordY == pointToCompare.getY();
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

struct Node
{
	std::shared_ptr<Point> point;
	double cost;
	double heuristic;
};

class Board
{
private:
	std::deque<std::deque<std::shared_ptr<Point>>> board;

public:
	Board() {

		// file pointer 
		std::fstream fread;

		// opens an existing csv file or creates a new file. 
		fread.open("board.csv", std::ios::in);

		const int initialY = -10;
		const int initialX = -10;
		const int sizeInit = 30;

		const int lastY = initialY + sizeInit;
		const int lastX = initialX + sizeInit;

		std::string temp;
		std::string line;
		std::string word;

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

				//while ((pos = word.find(delimiter)) != std::string::npos) {
				while (true) {
					pos = word.find(delimiter);
					token = word.substr(0, pos);

					if(i == 0)
					{
						token.erase(0, 1);
						x = std::stoi(token);
					}
					else if(i == 1)
					{
						y = std::stoi(token);
					}
					else if(i == 2)
					{
						if(token == "true)")
						{
							passable = true;
						}
						else if(token == "false)")
						{
							passable = false;
						}
					}
					//std::cout << token << std::endl;
					//i = (i + 1) % 3;
					i += 1;
					if(i == 3)
					{
						break;
					}
					word.erase(0, pos + delimiter.length());


				} 

				std::shared_ptr<Point> ptr = std::shared_ptr<Point>(new Point(y, x, passable));
				deck.push_back(ptr);

			}
			board.push_back(deck);
		}
	};
	virtual ~Board() {};

	void printBoardWithAstarAlgorithm(std::vector<Node> astarResult)
	{
		std::deque<std::deque<std::shared_ptr<Point>>>::iterator it1;
		std::deque<std::shared_ptr<Point>>::iterator it2;

		std::cout << "----------------------------------" << std::endl;

		for (it1 = board.begin(); it1 != board.end(); it1++)
		{
			for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
			{
				bool isInAstarResult = false;
				for (Node node : astarResult)
				{
					if (node.point->isEqualsTo(*(*it2).get()))
					{
						isInAstarResult = true;
						break;
					}
				}
				if(isInAstarResult)
				{
					std::cout << "0";
				}
				else if ((*(*it2).get()).isPassabe())
				{
					std::cout << " ";
				}
				else
				{
					std::cout << "x";
				}
			}
			std::cout << std::endl;
		}

		std::cout << "----------------------------------" << std::endl;
	}
	
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

	std::shared_ptr<Point> get_point(int coordX, int coordY)
	{
		size_t sizeLine = board.at(0).size();
		size_t sizeColumn = board.size();
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
	
	//push a point in the map
	void push_point(int coordX, int coordY)
	{
		//init values needed to check where to extend the map
		size_t sizeLine = board.at(0).size();
		size_t sizeColumn = board.size();
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
		size_t sizeLine = board.at(0).size();
		size_t sizeColumn = board.size();
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
		size_t sizeLine = board.at(0).size();
		size_t sizeColumn = board.size();
		int maxIndexLine = board.at(0).at(sizeLine - 1)->getX() + 1;
		int minIndexColumn = board.at(0).at(0)->getY();
		for (int i = board.at(0).at(0)->getX(); i < maxIndexLine; i++)
		{
			newRow.push_back(std::shared_ptr<Point>(new Point(i, minIndexColumn - 1)));
		}
		board.push_front(newRow);
	}
};