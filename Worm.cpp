#include "Worm.hpp"

/**
 * @brief Construct a new Worm object
 *  default constructor
 */
Worm::Worm(): 
    _worm{new circleQ()} 
{}


/**
 * @brief Construct a new Worm object
 *  single argument constructor
 * @param size - Pre-allocate size
 */
Worm::Worm(int capacity) { 
    _worm = new circleQ(capacity); 
}


/**
 * @brief Construct a new Worm object
 *  double argument constructor
 * @param cell      - Worm head position
 * @param capacity  - Pre-allocate capacity
 */
Worm::Worm(Cell cell, int capacity) {
    _worm = new circleQ(capacity);
    _worm->push_back(cell);
}

/**
 * @brief Construct a new Worm object
 *  triple argument constructor
 * @param cell      - Worm head position
 * @param capacity  - Pre-allocate max size
 * @param size      - Size of worm to construct
 */
Worm::Worm(Cell cell, int capacity, int size) {
    _worm = new circleQ(size);  // pre allocate worm
    for (int i = 0; i < size; i++) { // push n(size) cells    
        Cell newCell(cell.row(), cell.column()+i);
        _worm->push_back(newCell);
    }
    
}

/**
 * @brief Get the worm
 * 
 * @return Queue* - circular queue (worm)
 */
Queue *Worm::getWorm() const {
    return _worm; // return the worm as a circular queue
}

/**
 * @brief return size of worm
 * 
 * @return int - size
 */
int Worm::size() {
    return _worm->NumElements();
}

/**
 * @brief Given a cell, make it the new head of the Worm
 * 
 * @param cell - New head
 */
void Worm::addHead(Cell cell) {
    _worm->push_back(cell); // add a head to the worm
}

/**
 * @brief Given a cell, make it the new head of the Worm
 * 
 * @param row       - Cell row
 * @param column    - Cell column
 */
void Worm::addHead(int row, int column) {
    Cell cell(row, column); // initialize cell with row & column
    _worm->push_back(cell); // add the cell to the worm
}


/**
 * @brief Remove the Worm’s tail from the queue
 */
void Worm::removeTail() {
    _worm->pop_front(); // pop the front of the worm (circular queue)
}


/**
 * @brief Get the cell representing the position of the Worm’s head
 * 
 * @return Cell - worm's head
 */
Cell Worm::head() { // the head of the worm is the back index of the queue
    return _worm->at(_worm->getBackIndex()); 
} 


/**
 * @brief Get the cell representing the position of the Worm’s tail
 * 
 * @return Cell - worm's tail
 */
Cell Worm::tail() { // the tail of the worm is the front of the queue
    return _worm->front(); 
}