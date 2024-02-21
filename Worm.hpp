#ifndef PROJECT2_315_WORM_HPP
#define PROJECT2_315_WORM_HPP
/**
 * @file Worm.hpp
 * @author Justin Blechel (blechelj@sonoma.edu)
 * @brief Data structure representing a worm
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 *  __      __                      
 * /  \    /  \___________  _____   
 * \   \/\/   /  _ \_  __ \/     \  
 *  \        (  <_> )  | \/  Y Y  \ 
 *   \__/\  / \____/|__|  |__|_|  / 
 *        \/                    */
#include <queue>
#include "circleQ.hpp"

class Worm {
public:
    // DEFAULT CONSTRUCTOR
    Worm();
    
    // PARAMETERIZED CONSTRUCTOR - SINGLE ARGUMENT
    explicit Worm(int capacity);
    
    // PARAMETERIZED CONSTRUCTOR - DOUBLE ARGUMENT
    Worm(Cell cell, int capacity);

    // PARAMETERIZED CONSTRUCTOR - TRIPLE ARGUMENT
    Worm(Cell, int capacity, int size);

    // WORM GETTER
    Queue *getWorm() const;
    void addHead(int row, int column); // Given a cell, make it the new head of the Worm
    void addHead(Cell cell);          // Given a cell, make it the new head of the Worm
    void removeTail();               // Remove the Worm’s tail from the queue
    Cell head();                    // Return cell representing position of the Worm’s head
    Cell tail();                   // Return cell representing position of the Worm’s tail
    int size();
    
private:
    Queue* _worm; // circular queue
    int _head{-1};
    int _tail{-1};
};

#endif // PROJECT2_315_WORM_HPP
