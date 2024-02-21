#include "Screen.hpp"

/**
 * @brief Construct a new Screen object
 * 
 * @param rows 
 * @param columns 
 */
Screen::Screen(int rows, int columns) {
    _screen.resize(rows);
    int fieldIndex = 1;
    for (int row = 1; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            // if border invalid cell
            if (row == 1 ||
                row == rows - 1 ||
                col == 0 ||    
                col == columns - 1) 
                _screen[row].push_back(-1);
            // else valid cell
            else {
                Cell free(row, col);
                _screen[row].push_back(fieldIndex);
                _free.push_back(free);
                fieldIndex++;
            }
        }
    }
    _freeIndex = _free.size();
}

/**
 * @brief make a cell free
 * 
 * @param cell 
 */
void Screen::makeFree(Cell cell) {
    if (!isFree(cell)) {
        _screen[cell.row()][cell.column()] = _freeIndex;
        _free.push_back(cell);
        _freeIndex++;
    }
}

/**
 * @brief occupy a cell with the worm
 * 
 * @param cell 
 */
void Screen::wormOccupy(Cell cell) {
    if (isFree(cell)) {
        _screen[cell.row()][cell.column()] = -1;
        _free.pop_back();
        _freeIndex--;
    }
}

/**
 * @brief return whether or not cell on the is free
 * 
 * @param cell 
 * @return true  - cell is free
 * @return false - cell is not free
 */
bool Screen::isFree(Cell cell) {
    // a cell on the screen is free if it does not equal -1 
    return _screen[cell.row()][cell.column()] != -1; 
}

/**
 * @brief return a random free cell
 * 
 * @return Cell - random free cell
 */
Cell Screen::getRandomFreeCell() {
    srand(time(NULL));
    int randomIndex;
    do {
        randomIndex = rand() % (_free.size() - 1);
    } while (_screen[_free[randomIndex].row()][_free[randomIndex].column()] == -1);
    Cell cell(_free[randomIndex]);
    return cell;
}