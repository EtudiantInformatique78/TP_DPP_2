#pragma once

#include <iostream>
#include <queue>
#include "Points.h"

#define PPU std::pair<std::shared_ptr<Point>, unsigned int>

class Compare {
public:
    bool operator()(PPU below, PPU above)
    {
        if (below.second >= above.second)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
};

class PQueue
{
private:
    
    std::map<std::shared_ptr<Point>, PPU, Compare> map;
    std::set<std::shared_ptr<Point>> set;


public:
    PQueue() {
        map = {};
    };
    ~PQueue() {};

    bool isInQueue(std::shared_ptr<Point> p)
    {
        return map.find(p) != map.end();
    }

    void insertQueue(std::shared_ptr<Point> vertice, std::shared_ptr<Point> predecesor, unsigned int dist)
    {
        map.insert({vertice, std::pair<std::shared_ptr<Point>, unsigned int>(predecesor, dist)});
    }

    void updateQueue(std::shared_ptr<Point> vertice, std::shared_ptr<Point> predecesor, unsigned int dist)
    {
        std::map<std::shared_ptr<Point>, PPU>::iterator it;
        it = map.find(vertice);

        if(it != map.end())
        {
            it->second.first = predecesor;
            it->second.second = dist;
        }
        else
        {
            insertQueue(vertice, predecesor, dist);
        }

    }

    PPU top()
    {
        std::shared_ptr<Point> vertice = map.begin()->first;
        unsigned int dist = map.begin()->second.second;

        return { vertice, dist };
    }

    PPU getValue(std::shared_ptr<Point> key)
    {
        return map[key];
    }

    void pop()
    {
        set.insert(map.begin()->first);
        map.erase(map.begin());
    }

    std::list<std::shared_ptr<Point>> trueNeighborg(std::list<std::shared_ptr<Point>> list)
    {
        std::list<std::shared_ptr<Point>> returnList;
        std::list<std::shared_ptr<Point>>::iterator it;
        for(it = list.begin(); it != list.end(); ++it)
        {
            if(set.find(*it) == set.end())
            {
                returnList.push_back(*it);
            }
        }

        return returnList;

    }

    void printPath(std::shared_ptr<Point> source, std::shared_ptr<Point> dest, std::shared_ptr<Board> bptr)
    {
        std::deque<std::shared_ptr<Point>> reversePath;
        
        reversePath.push_back(dest);

        std::shared_ptr<Point> nextPoint = map[dest].first;
        while(!pointsAreEquivalent(nextPoint, source, bptr))
        {
            reversePath.push_back(nextPoint);
            nextPoint = map[nextPoint].first;
        }
        reversePath.push_back(source);

        std::deque<std::shared_ptr<Point>>::reverse_iterator it;

        for(it = reversePath.rbegin(); it != reversePath.rend(); ++it)
        {
            std::cout << "(" << (*it).get()->getX() << "," << (*it).get()->getY() << ")" << std::endl;
        }


    }

};