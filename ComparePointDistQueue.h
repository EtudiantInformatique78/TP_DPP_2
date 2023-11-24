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

    void pop()
    {
        map.erase(map.begin());
    }

};