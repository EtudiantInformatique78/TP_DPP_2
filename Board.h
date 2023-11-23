#pragma once
#include <iostream>
#include <deque>
#include <fstream>

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

	friend std::ostream& operator<<(std::ostream& out, Point& p)
	{
		out << "(" << p.coordY << "," << p.coordX << ")";
		return out;
	}
};

class Board
{
private:
	std::deque<std::deque<std::shared_ptr<Point>>> board;

public:
	Board() {

		// file pointer 
		std::fstream fout;

		// opens an existing csv file or creates a new file. 
		fout.open("board.csv", std::ios::out | std::ios::app);

		const int initialY = -10;
		const int initialX = -10;
		const int sizeInit = 30;

		const int lastY = initialY + sizeInit;
		const int lastX = initialX + sizeInit;

		for (int i = initialY; i <= lastY; i++)
		{

			std::deque<std::shared_ptr<Point>> deck;
			for (int j = initialX; j <= lastX; j++)
			{
				std::shared_ptr<Point> ptr = std::shared_ptr<Point>(new Point(j, i));
				fout << (*ptr) << ";";
				deck.push_back(ptr);
			}
			fout << "\n";
			board.push_back(deck);

		}
	};
	virtual ~Board() {};



	/*
	void create()
	{
		// file pointer
		std::fstream fout ;

		// opens an existing csv file or creates a new file.
		fout.open("Board.csv", std::ios::out | std::ios::app);


		// Read the input
		for (i = 0; i < 5; i++) {

			cin >> roll
				>> name
				>> math
				>> phy
				>> chem
				>> bio;

			// Insert the data to file
			fout << roll << ", "
				<< name << ", "
				<< math << ", "
				<< phy << ", "
				<< chem << ", "
				<< bio
				<< "\n";
		}
	}

	*/

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
	

	void push_north_west()
	{
		push_north();
		push_west();
	}

	void push_north_est()
	{
		push_north();
		push_est();
	}

	void push_south_west()
	{
		push_south();
		push_west();
	}

	void push_south_est()
	{
		push_south();
		push_est();
	}

	void push_coordonne(int x, int y)
	{
		
	}


	/*
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