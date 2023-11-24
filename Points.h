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


	void setX(int x)
	{
		coordX = x;
	}
	void setY(int y)
	{
		coordY = y;
	}




};

unsigned int weight(Point& p1, Point& p2)
{
	return 1;
}