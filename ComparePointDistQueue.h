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
        //return below.second.second >= above.second.second;
        if(&below == &above)
        {
            return false;
        }

        if (below.second.second > above.second.second)
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
        
        std::shared_ptr<PPU> ptr = nullptr;
        for (auto it = this->c.begin(); it != this->c.end(); ++it)
        {
            PairPPU pair = static_cast<PairPPU>(*it);
            std::shared_ptr<Point> p = pair.first;
        
            //std::shared_ptr<PPU> returnValue = std::shared_ptr<PPU>(&pair.second);

            if ((*p.get()) == (*key.get()))
            {
                ptr = std::make_shared<PPU>(pair.second);
                //ptr = returnValue;
                //return returnValue;
            }

        }

        return ptr;
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
    std::set<unsigned int> set;

    custom_priority_queue cpq;

    std::set<unsigned int> inQueue;

    std::map<unsigned int, unsigned int> mapPointAndPred;

    int initialX = 0;
    int initialY = 0;



public:
    PQueue() {
        //map = {};
    };

    PQueue(int x_init, int y_init) {
        initialX = x_init;
        initialY = y_init;
        //map = {};
    };

    ~PQueue() {};

    void insertMap(unsigned int p, unsigned int pred)
    {
        this->mapPointAndPred.insert({ p, pred });
    }

    bool isInQueue(std::shared_ptr<Point> p)
    {
        unsigned int z = getIdOfPoint(p, initialX, initialY);
        return inQueue.find(z) != inQueue.end();
    }
    
    void insertQueue(std::shared_ptr<Point> vertice, std::shared_ptr<Point> predecesor, unsigned int dist)
    {
        PPU pair1 = { predecesor, dist };
        std::pair<std::shared_ptr<Point>, PPU> pair2 = {vertice, pair1};
        cpq.push(pair2);

        unsigned int idVertice = getIdOfPoint(vertice, initialX, initialY);

        inQueue.insert(idVertice);
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
        if(ptr != nullptr)
        {
            return *ptr.get();
        }
        else
        {
            return { nullptr, UINT_MAX };
        }
        
        //return *ptr.get();
    }
    
    void pop()
    {
        std::shared_ptr<Point> p = cpq.top().first;
        std::shared_ptr<Point> pred = cpq.top().second.first;
        
        unsigned int idPointP = getIdOfPoint(p, initialX, initialY);
        // UINT_MAX for null value
        unsigned int idPointPred = UINT32_MAX;
        if(pred != nullptr)
        {
            idPointPred = getIdOfPoint(pred, initialX, initialY);
        }



        set.insert(idPointP);
        mapPointAndPred.insert({ idPointP, idPointPred });
//        setPointAndPred.insert(pred);
        
        cpq.pop();

        //unsigned int idP = getIdOfPoint(p, initialX, initialY);


        auto it = inQueue.find(idPointP);
        if(it != inQueue.end())
        {
            inQueue.erase(it);
        }
        
    }
    
    std::list<std::shared_ptr<Point>> trueNeighborg(std::list<std::shared_ptr<Point>> list)
    {
        std::list<std::shared_ptr<Point>> returnList;
        std::list<std::shared_ptr<Point>>::iterator it;
        for(it = list.begin(); it != list.end(); ++it)
        {
            //std::cout << "In for loop" << std::endl;
            //if((*it).get()->getX() == -7 && (*it).get()->getY() == 5)
            //{
            //    //__debugbreak();
            //}
            unsigned int z = getIdOfPoint((*it), initialX, initialY);
            if(set.find(z) == set.end())
            {
                returnList.push_back(*it);
            }
        }

        return returnList;

    }

    void printPath(std::shared_ptr<Point> source, std::shared_ptr<Point> dest, std::shared_ptr<Board> bptr)
    {
        /*
        
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

        */
        
        unsigned int idSource = getIdOfPoint(source, bptr);
        unsigned int idDest = getIdOfPoint(dest, bptr);

        std::deque<unsigned int> reversePath;

        reversePath.push_back(idDest);

        unsigned int nextPoint = mapPointAndPred[idDest];

        while (nextPoint != idSource)
        {
            reversePath.push_back(nextPoint);
            nextPoint = mapPointAndPred[nextPoint];
        }

        reversePath.push_back(idSource);


        std::deque<unsigned int>::reverse_iterator it;

        for (it = reversePath.rbegin(); it != reversePath.rend(); ++it)
        {
            unsigned int z = *it;
            unsigned ind_x;
            unsigned ind_y;
            compute_x_y_from_z(z, ind_x, ind_y);

            pairInt pair = indToCoord(ind_x, ind_y, initialX, initialY);

            std::cout << "(" << pair.x << "," << pair.y << ")" << std::endl;
        }


    }


};