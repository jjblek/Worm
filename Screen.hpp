#ifndef PROJECT2_315_SCREEN_HPP
#define PROJECT2_315_SCREEN_HPP
/**
 * @file Screen.hpp
 * @author Justin Blechel (blechelj@sonoma.edu)
 * @brief Data structure representing a screen
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 *   _________                                  
 *  /   _____/ ___________  ____  ____   ____   
 *  \_____  \_/ ___\_  __ \/ __ \/ __ \ /    \  
 *  /        \  \___|  | \|  ___|  ___/|   |  \ 
 * /_______  /\___  >__|   \___  >___  >___|  / 
 *        \/     \/           \/    \/     \*/
#include "Cell.hpp"
#include <vector>

class Screen {
public:
    explicit Screen(int rows, int columns); // constructor
    void makeFree(Cell cell);               // make c a free (empty) cell
    void wormOccupy(Cell cell);             // make c occupied by the worm
    bool isFree(Cell cell);                 // return true if c is free, false if it’s occupied            
    Cell getRandomFreeCell();               // randomly select and return a free cell to place the snack in
private:
    std::vector<std::vector<int>> _screen;  // screen matrix
    std::vector<Cell> _free;                // list of free cells
    unsigned long long _freeIndex;          // most recently freed cell
};

#endif // PROJECT2_315_SCREEN_HPP