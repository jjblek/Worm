#ifndef PROJECT2_315_CELL_HPP
#define PROJECT2_315_CELL_HPP
/**
 * @file Cell.hpp
 * @author Justin Blechel
 * @brief Data structure representing a cell (row, column)
 *  coordinates within the playing field of a screen
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * _________        .__  .__    
 * \_   ___ \  ____ |  | |  |   
 * /    \  \/_/ __ \|  | |  |   
 * \     \___\  ___/|  |_|  |__ 
 *  \______  /\___  >____/____/ 
 *         \/     */
#include <iostream>

class Cell {
public:
    // DEFAULT CONSTRUCTOR
    Cell(): _row(-1), _column(-1) {}

    // PARAMETERIZED CONSTRUCTOR
    Cell(int r, int c): _row(r), _column(c) {}

    // GETTERS & SETTERS
    int row() const { return _row; }
    void row(int row) { _row = row; }

    int column() const { return _column; }
    void column(int column) { _column = column; }

    // OVERLOAD ASSIGNMENT OPERATOR
    Cell& operator=(const Cell &cell) {
        // copy row and column
        _row = cell.row(), _column = cell.column();
        // return the existing object so we can chain this operator
        return *this;
    }

    // OVERLOAD EQUALITY OPERATOR
    bool operator==(const Cell &cell) const {
        // compare cell row & column
        return _row == cell.row() && _column == cell.column();
    }

    // OVERLOAD INEQUALITY OPERATOR
    bool operator!=(const Cell &cell) const {
        // compare cell row & column
        return _row != cell.row() || _column != cell.column();
    }

    // OVERLOAD OSTREAM OPERATOR
    friend std::ostream& operator<<(std::ostream &out, const Cell &cell) {
        std::cout << "[" << cell.row() << ", " << cell.column() << "]";
        return out;
    }

private:
    int _row, _column;
};

#endif