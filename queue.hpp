#ifndef PROJECT2_315_QUEUE_HPP
#define PROJECT2_315_QUEUE_HPP
/**
 * @file queue.hpp
 * @author Justin Blechel (blechelj@sonoma.edu)
 * @brief Queue base class - Lab 06
 * @version 0.1
 * @date 2022-10-22
 *   ________ __  ____  __ __  ____   
 *  / ____/  |  \/ __ \|  |  \/ __ \  
 * < <_|  |  |  |  ___/|  |  |  ___/  
 *  \__   |____/ \___  >____/ \___  > 
 *     |__|          \/           */
#include <iostream>
#include "Cell.hpp"

class Queue {
public:
    // CONSTRUCTOR
    Queue(): size(0) {}

    // DESTRUCTOR
    ~Queue() = default; // empty - no dynamically allocated memory

    // Insert the specified int at back of queue unless it's full
    virtual bool push_back(Cell) = 0; // pure virtual function

    // Delete and return the first element, exit with error if empty
    virtual Cell pop_front() = 0;

    // Return the first element without popping it, exit w/ error if empty
    virtual Cell front() = 0;

    // Return true if value is in queue, else false
    virtual bool exists(Cell c) = 0;

    // Reference the element present at the position given
    virtual Cell at(const int &) = 0;

    // Return back index of queue
    virtual int getBackIndex() const = 0;

    // Return the number of elements
    int NumElements() { return size; }

    // Return true if and only if queue is empty
    bool empty() const { return (size == 0); }

    // Return true if and only if queue is full
    bool full() const { return (size == MAX_QSIZE); }

    // Return max size of queue
    long long int getMaxQsize() const { return MAX_QSIZE; }

protected:
    // helper function to exit with error when queue is empty
    void exitIfEmpty() const {
        if (empty()) {
            std::cerr << "Can't do this operation on an empty queue\n";
            exit(1);
        }
    }

    int size;
    long long MAX_QSIZE; // maximum size of a queue
};

#endif // PROJECT2_315_QUEUE_HPP