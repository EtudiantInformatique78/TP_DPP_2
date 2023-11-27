#pragma once
#include "structCoord.h"

pairInt coordToInd(int x, int y, int initialX, int initialY)
{
	pairInt pair = {};
	pair.x = x - initialX;
	pair.y = y - initialY;
	return pair;
}

pairInt indToCoord(int x_ind, int y_ind, int initialX, int initialY)
{
	pairInt pair = {};
	pair.x = x_ind + initialX;
	pair.y = y_ind + initialY;
	return pair;
}

// Cantor pairing function
/*
It's a simple bijection between NxN and N
*/
unsigned int coordinateToNumber(unsigned int x, unsigned int y)
{
	unsigned int sum1 = x + y;
	unsigned int sum2 = x + y + 1;
	unsigned int result = static_cast<unsigned int>((sum1 * sum2) / 2 + y);
	return result;
}
// The inverse function of Cantor pairing function
void compute_x_y_from_z(unsigned int z, unsigned int& x, unsigned int& y)
{

	double numerator = std::sqrt(8 * z + 1) - 1;
	unsigned int w = static_cast<unsigned int>(std::floor(numerator / 2));

	unsigned int t = static_cast<unsigned int>((w * w + w) / 2);

	y = z - t;
	x = w - y;

}


unsigned int getIdOfPoint(std::shared_ptr<Point> p, std::shared_ptr<Board> bptr)
{
	int x_coord = p.get()->getX();
	int y_coord = p.get()->getY();

	int initX = bptr.get()->getInitialX();
	int initY = bptr.get()->getInitialY();

	pairInt pairSource = coordToInd(x_coord, y_coord, initX, initY);

	unsigned int z = coordinateToNumber(pairSource.x, pairSource.y);
	return z;
}

unsigned int getIdOfPoint(std::shared_ptr<Point> p, int initX, int initY)
{

	int x_coord = p.get()->getX();
	int y_coord = p.get()->getY();

	pairInt pairSource = coordToInd(x_coord, y_coord, initX, initY);

	unsigned int z = coordinateToNumber(pairSource.x, pairSource.y);
	return z;
}

bool pointsAreEquivalent(std::shared_ptr<Point> p, std::shared_ptr<Point> q, std::shared_ptr<Board> bptr)
{
	unsigned int ip = getIdOfPoint(p, bptr);
	unsigned int iq = getIdOfPoint(q, bptr);

	return ip == iq;

}