#ifndef PROJECT2_315_CIRCLEQ_HPP
#define PROJECT2_315_CIRCLEQ_HPP
/**
 * @file circleQ.hpp
 * @author Justin Blechel (blechelj@sonoma.edu)
 * @brief Circlular queue implementation - Lab 06
 *  derived from queue.hpp
 * @version 0.1
 * @date 2022-10-22
 *        .__              .__         ________    
 *   ____ |__|______  ____ |  |   ____ \_____  \   
 * _/ ___\|  \_  __ \/ ___\|  | _/ __ \ /  / \  \  
 * \  \___|  ||  | \|  \___|  |_\  ___//   \_/.  \ 
 *  \___  >__||__|   \___  >____/\___  >_____\ \_/ 
 *      \/               \/          \/       \*/
#include "queue.hpp"

class circleQ: public Queue {
public:
    // DEFAULT CONSTRUCTOR
    circleQ();

    // PARAMETERIZED CONSTRUCTOR - SINGLE ARGUMENT
    explicit circleQ(int size);

    // COPY CONSTRUCTOR
    circleQ(const circleQ& other);

    // DESTRUCTOR
    ~circleQ();

    // ~~~~~ INHERITED VIRTUAL FUNCTIONS ~~~~~
    // Insert the specified int at back of queue unless it's full
    virtual bool push_back(Cell); // pure virtual function

    // Delete and return the first element, exit with error if empty
    virtual Cell pop_front();

    // Return the first element without popping it, exit w/ error if empty
    virtual Cell front();

    // Return true if value is in queue, else false
    virtual bool exists(Cell);

    // Reference the element present at the position given 
    virtual Cell at(const int &);

    // Return the back index of the circular queue
    virtual int getBackIndex() const;
private:
    Cell* array;               // pointer for the array itself
    int frontIndex, backIndex; // indices for the front and back elements of queue
};

#endif // PROJECT2_315_CIRCLEQ_HPP