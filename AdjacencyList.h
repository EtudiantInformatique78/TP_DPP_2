#pragma once
#include <iostream>
#include <list>
#include <vector>

#include <iterator>
#include <cmath>

#include "Board.h"


struct pairInt
{
	int x;
	int y;
};

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


unsigned int coordinateToNumber(unsigned int x, unsigned int y)
{
	unsigned int sum1 = x + y;
	unsigned int sum2 = x + y + 1;
	unsigned int result = static_cast<unsigned int>( (sum1 * sum2) / 2 + y);
	return result;
}

void compute_x_y_from_z(unsigned int z, unsigned int& x, unsigned int& y)
{
	
	double numerator = std::sqrt(8 * z + 1) - 1;
	unsigned int w = std::floor(numerator/2);

	unsigned int t = static_cast<unsigned int>((w * w + w) / 2);

	y = z - t;
	x = w - y;

}

void displayAdjList(std::list<std::shared_ptr<Point>> adj_list[], int v)
{
	for (int i = 0; i < v; i++)
	{
		std::cout << i << "-->";
		std::list<std::shared_ptr<Point>>::iterator it;
		for(it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
		{
			std::cout << "k" << *it << "k ";
		}
		std::cout << std::endl;
	}
}


template<typename T>
void add_edge(std::list<T> adj_list[], T u, T v)
{
	
//	adj_list[u].push_back(v);
//	adj_list[v].push_back(u);
}

void test()
{
	int v = 6; // 6 vertices in the graph
	std::list<std::shared_ptr<Point>> adj_list(v);

	std::shared_ptr<Point> ptr1 = std::shared_ptr<Point>(new Point(0, 0, true));
	std::shared_ptr<Point> ptr2 = std::shared_ptr<Point>(new Point(1, 0, true));
	std::shared_ptr<Point> ptr3 = std::shared_ptr<Point>(new Point(2, 0, true));

	std::shared_ptr<Point> ptr4 = std::shared_ptr<Point>(new Point(0, 1, true));
	std::shared_ptr<Point> ptr5 = std::shared_ptr<Point>(new Point(1, 1, true));
	std::shared_ptr<Point> ptr6 = std::shared_ptr<Point>(new Point(2, 1, true));

	add_edge(&adj_list, ptr1, ptr2);
	add_edge(&adj_list, ptr1, ptr4);
	add_edge(&adj_list, ptr1, ptr5);


	add_edge(&adj_list, ptr2, ptr4);
	add_edge(&adj_list, ptr2, ptr5);
	add_edge(&adj_list, ptr2, ptr6);
	add_edge(&adj_list, ptr2, ptr3);

	add_edge(&adj_list, ptr3, ptr5);
	add_edge(&adj_list, ptr3, ptr6);
	add_edge(&adj_list, ptr4, ptr5);
	add_edge(&adj_list, ptr5, ptr6);


	displayAdjList(&adj_list, v);
}