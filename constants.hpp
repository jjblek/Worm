#ifndef PROJECT2_315_CONSTANTS_HPP
#define PROJECT2_315_CONSTANTS_HPP
/**
 * @file constants.hpp
 * @author Justin Blechel (blechelj@sonoma.edu)
 * @brief CONSTANTS, HELPER FUNCTIONS, ETC.
 *  FOR WORM PROJECT
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 */

/** Default row and column sizes */
const unsigned int DEFAULT_ROWS = 23;
const unsigned int DEFAULT_COLUMNS = 62;

/** Allowable sizes of playing field */
const unsigned int MIN_ROWS = 9;
const unsigned int MAX_ROWS = 25;
const unsigned int MIN_COLS = 9;
const unsigned int MAX_COLS = 80;

/** Size of initial worm */
const size_t wormSize = 8;

/** Enumerated type for the different input directions */
enum Direction {UP, LEFT, DOWN, RIGHT, STOP, INVALID};

#endif