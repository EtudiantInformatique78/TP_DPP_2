#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include "Points.h"

#define PPU std::pair<std::shared_ptr<Point>, unsigned int>
#define PairPPU std::pair<std::shared_ptr<Point>,PPU>

class ComparePPU {

public:
    bool operator()(PairPPU below, PairPPU above)
    {
        
        if (below.second.second >= above.second.second)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
};

/*

template<typename T, class Container=std::vector<T>, class Compare=std::less<typename Container::value_type>>
class custom_priority_queue : public std::priority_queue<T, Container, Compare>

*/


class custom_priority_queue : public std::priority_queue<PairPPU, std::vector<PairPPU>, ComparePPU>
{
public:
    bool remove(std::shared_ptr<Point> value)
    {
        for(auto it = this->c.begin(); it != this->c.end(); ++it)
        {
            PairPPU pair = static_cast<PairPPU>(*it);
            std::shared_ptr<Point> p = pair.first;

            if(  (*p.get()) == (*value.get())  )
            {
                this->c.erase(it);
                std::make_heap(this->c.begin(), this->c.end(), this->comp);
                return true;
            }   
        }

        return false;
    }

    std::shared_ptr<PPU> getValue(std::shared_ptr<Point> key)
    {
        for (auto it = this->c.begin(); it != this->c.end(); ++it)
        {
            PairPPU pair = static_cast<PairPPU>(*it);
            std::shared_ptr<Point> p = pair.first;
        
            std::shared_ptr<PPU> returnValue = std::shared_ptr<PPU>(&pair.second);

            if ((*p.get()) == (*key.get()))
            {
                return returnValue;
            }

        }
        return nullptr;
    }

};

/*
template<typename T, class Container = std::vector<T>, class Compare= ComparePPU<T> >
class custom_priority_queue : public std::priority_queue<T, Container, Compare>
{
typedef typename T::second_type::second_type value_type;
public:

    bool remove(const T& value) {


        auto it = std::find(this->c.begin(), this->c.end(), value);

        if (it == this->c.end()) {
            return false;
        }
        if (it == this->c.begin()) {
            // deque the top element
            this->pop();
        }
        else {
            // remove element and re-heap
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }
        return true;
    }
};

*/



class PQueue
{
private:
    
    //std::map<std::shared_ptr<Point>, PPU, ComparePPU> map;
    //std::map<PPU, PPU, ComparePPU> map;
    std::set<std::shared_ptr<Point>> set;

    custom_priority_queue cpq;

    std::set<std::shared_ptr<Point>> inQueue;

    std::map<std::shared_ptr<Point>, std::shared_ptr<Point>> mapPointAndPred;


public:
    PQueue() {
        //map = {};
    };
    ~PQueue() {};

    

    bool isInQueue(std::shared_ptr<Point> p)
    {
        return inQueue.find(p) != inQueue.end();
    }
    
    void insertQueue(std::shared_ptr<Point> vertice, std::shared_ptr<Point> predecesor, unsigned int dist)
    {
        PPU pair1 = { predecesor, dist };
        std::pair<std::shared_ptr<Point>, PPU> pair2 = {vertice, pair1};
        cpq.push(pair2);
        inQueue.insert(vertice);
        //map.insert({vertice, std::pair<std::shared_ptr<Point>, unsigned int>(predecesor, dist)});
    }
    
    void updateQueue(std::shared_ptr<Point> vertice, std::shared_ptr<Point> predecesor, unsigned int dist)
    {
        
        if(isInQueue(vertice))
        {
            // remove then add a new value
            cpq.remove(vertice);
        }
        
        insertQueue(vertice, predecesor, dist);
        /*
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
        */
    }

    PPU top()
    {
        std::shared_ptr<Point> vertice = cpq.top().first;
        unsigned int dist = cpq.top().second.second;

        return { vertice, dist };
        
    }
    
    PPU getValue(std::shared_ptr<Point> key)
    {
        std::shared_ptr<PPU> ptr = cpq.getValue(key);
        return *ptr.get();
    }
    
    void pop()
    {
        std::shared_ptr<Point> p = cpq.top().first;
        std::shared_ptr<Point> pred = cpq.top().second.first;
        
        set.insert(p);
        mapPointAndPred.insert({ pred, p });
//        setPointAndPred.insert(pred);
        
        cpq.pop();
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

        std::shared_ptr<Point> nextPoint = mapPointAndPred[dest];
        while(!pointsAreEquivalent(nextPoint, source, bptr))
        {
            reversePath.push_back(nextPoint);
            nextPoint = mapPointAndPred[nextPoint];
        }
        reversePath.push_back(source);

        std::deque<std::shared_ptr<Point>>::reverse_iterator it;

        for(it = reversePath.rbegin(); it != reversePath.rend(); ++it)
        {
            std::cout << "(" << (*it).get()->getX() << "," << (*it).get()->getY() << ")" << std::endl;
        }


    }


};