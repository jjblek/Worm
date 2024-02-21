#include "circleQ.hpp"

/**
 * @brief Default Constructor:
 *  Construct a new circleQ object
 *  Queue default constructor has already run and initialized size to 0
 *  Pre-allocate array and initialize front and back indices
 */
circleQ::circleQ() {
    array = new Cell[MAX_QSIZE]; // actually allocate the array
    // error & exit if nullptr
    if (array == nullptr) {
        std::cerr << "Couldn't allocate initial array\n";
        exit(1);
    }
    frontIndex = -1;
    backIndex = -1;
}

/**
 * @brief Parameterized Constructor:
 *  Construct a new circleQ object
 *  Queue default constructor has already run and initialized size to 0
 *  Pre-allocate array of specified size and initialize front and back indices
 * @param size - specified size of array to pre-allocate
 */
circleQ::circleQ(int size) {
    MAX_QSIZE = size;
    array = new Cell[size]; // actually allocate the array
    // error & exit if nullptr
    if (array == nullptr) {
        std::cerr << "Couldn't allocate initial array\n";
        exit(1);
    }
    // initialize front/back indicies to -1
    frontIndex = -1;
    backIndex = -1;
}


/**
 * @brief Copy Constructor:
 *  Construct a new circleQ object as copy of another object
 * @param other - circleQ to copy
 */
circleQ::circleQ(const circleQ& other) {
    size = other.size;              // copy size
    frontIndex = other.frontIndex;  // copy front index
    backIndex = other.backIndex;    // copy back index

    array = new Cell[MAX_QSIZE];    // allocate queue
    // error & exit if nullptr
    if (array == nullptr) { 
        std::cerr << "Couldn't allocate initial array\n";
        exit(1);
    }
    // traverse array, copy elements
    for (int i = 0; i < size; i++) {
        int current_index = (frontIndex + i) % MAX_QSIZE;
        array[current_index] = other.array[current_index];
    }
}


/**
 * @brief Destructor: Destroy the circleQ object
 *  Deallocate the dynamically allocated array
 */
circleQ::~circleQ() { 
    delete [] array; // delete the queue
}


/**
 * @brief Push Back:
 *  If queue is full, return false
 *  otherwise, add item to queue, 
 *  adjust front/back indices and size accordingly, and return true
 * @param c 
 * @return true 
 * @return false 
 */
bool circleQ::push_back(Cell c) {

    if (full()) return false; // default for now
    
    // if empty - initialize
    if (frontIndex == -1) frontIndex = backIndex = 0;
    // else if there's no space wrap around
    else if (backIndex == MAX_QSIZE-1) backIndex = 0;
    // else there is space, increment back
    else backIndex++;

    array[backIndex] = c;   // set back to cell
    size++;                 // cell added, increment size

    return true;

}


/**
 * @brief Pop Front:
 *  If queue is empty, exit with error
 *  otherwise, remove and return first element
 *  adjust front/back indices accordingly and decrement size
 * @return Cell - front of circular Queue
 */
Cell circleQ::pop_front() {

    exitIfEmpty(); // call parent function to exit w/ error from empty queue

    Cell front = array[frontIndex]; // save current front

    // if size == 1 deinitialize
    if (frontIndex == backIndex) frontIndex = backIndex = -1;

    // else if front is at the back, wrap around
    else if (frontIndex == MAX_QSIZE - 1) frontIndex = 0;

    else frontIndex++;  // else increment front

    size--;             // decrement size;

    return front;       // return popped element
}

// TODO: dont return OOB
/**
 * @brief Front: 
 *  If queue is empty, return OOB cell
 *  otherwise, return first element w/o removing and decrement size
 * @return Cell 
 */
Cell circleQ::front() {
    if (empty()) { // return OOB cell if empty
        Cell cell(-1, -1);
        return cell;
    } // else return element at front index
    return array[frontIndex];
}


/**
 * @brief Exists:
 *  Return true if value is in queue, false otherwise 
 * 
 * @param cell   - Cell to find
 * @return true  - Cell was found
 * @return false - Cell was not found
 */
bool circleQ::exists(Cell cell) {
    // if size == 1; return element at first index
    if (backIndex == 0 && frontIndex == 0) {
        return array[0].row() == cell.row() &&
            array[0].column() == cell.column();
    }

    // if back index has not wrapped around
    if (backIndex > frontIndex) {
        // simply search from front index to back index
        for (int i = frontIndex; i <= backIndex; ++i) {
            if (array[i].row() == cell.row() &&
            array[i].column() == cell.column())
                return true;
        }
    }

    // else if back index has wrapped around
    else if (backIndex < frontIndex) {
        // search from front index to last index
        for (int i = frontIndex; i < MAX_QSIZE; ++i) {
            if (array[i].row() == cell.row() &&
            array[i].column() == cell.column())
                return true;
        }
        // search from back index to first index
        for (int i = backIndex; i >= 0 ; --i) {
            if (array[i].row() == cell.row() &&
            array[i].column() == cell.column())
                return true;
        }
    }
    // else cell was not found
    return false; 
}

/**
 * @brief At:
 *  Access circleQ element of specified index
 * 
 * @param index - specified index
 * @return Cell - element at specified index
 */
Cell circleQ::at(const int &index) { 
    return array[index]; // return element @index
}

/**
 * @brief Get Back Index:
 *  Return the back index of the circular queue
 * @return int - back index
 */
int circleQ::getBackIndex() const {
    return backIndex; // return back index
}