#pragma once

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

	friend bool operator==(Point& p1, Point& p2)
	{
		if(p1.coordX == p2.coordX)
		{
			if(p1.coordY == p2.coordY)
			{
				return true;
			}
		}
		return false;
	}

	friend bool operator!=(Point& p1, Point& p2)
	{
		if(p1.coordX != p2.coordX)
		{
			return true;
		}
		else
		{
			return p1.coordY != p2.coordY;
		}
	}

	void setX(int x)
	{
		coordX = x;
	}
	void setY(int y)
	{
		coordY = y;
	}


	bool isEqualsTo(Point pointToCompare)
	{
		return coordX == pointToCompare.getX() && coordY == pointToCompare.getY();
	}

};

unsigned int weight(Point& p1, Point& p2)
{
	return 1;
}