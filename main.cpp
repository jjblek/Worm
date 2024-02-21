/**
 * @file main.cpp
 * @author Justin Blechel
 * @brief Main - designated start of the program
 *  Validate command line input - Screen and worm controller
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <cassert>
#include <curses.h>
#include <tuple>
#include <time.h>

#include "constants.hpp"
#include "Screen.hpp"
#include "Worm.hpp"
#include "getInput.hpp"

void startup(void);
void terminate(int);

void functionalityTest(Worm worm);
std::pair<Cell, int> generateSnack(Screen &screen);

/**
 * @param argc - number of arguments
 * @param argv - arguments
 * @return int 
 */
int main(int argc, char *argv[]) {

     // Worm testWorm; // functionality test
     
     int rows, columns;       // row and column sizes of screen
     
     if (argc == 1) {         // zero program arguments
          rows = DEFAULT_ROWS, 
          columns = DEFAULT_COLUMNS;
     } 

     else if (argc == 3) {    // three program arguments
          rows = std::stoi(argv[1])+3, 
          columns = std::stoi(argv[2])+2;
     } 

     else {                   // invalid program arguments
          std::cout << "Error: This program expects [0] or [2] arguments (row, column). [" << 
               argc-1 << "] arguments were provided." << std::endl;
          exit(1);
     }

     // row size validation
     if (rows-3 < MIN_ROWS || rows-3 > MAX_ROWS) {
          std::cout << "Error: Invalid row range [" << 
               rows-3 << "]. Valid row range is [9-25]" << std::endl;
          exit(1);
     }
     // column size validation
     else if (columns-2 < MIN_COLS || columns-2 > MAX_COLS) {
          std::cout << "Error: Invalid column range [" << 
               columns-2 << "]. Valid column range is [9-80]" << std::endl;
          exit(1);
     }

     int n = rows*columns; // n positions

     // testWorm = Worm(n);   // functionality test
     // test circular queue functionality of worm
     // functionalityTest(testWorm);

     int score = 0; // initialize score

     startup();
     
     move(0, 0);         // move the curser to the top left-most block
     addstr("Worm");    // write worm title

     int scoreColumn = columns == 11 ? columns-6 : columns-7; // column to write score
     move(0, scoreColumn);    // move to score column
     addstr("Score 0");      // write initial score
     
     // traverse rows
     for (int row = 1; row < rows; ++row) { 
          // traverse columns
          for (int column = 0; column < columns; ++column) {
               move(row, column); // move to position (row, column)
               // if border condition is true
               if (row == 1 || row == rows - 1 || 
                    column == 0 || column == columns - 1)
                    addch('*'); // write border
          }    // else next position
     }
     
     Screen screen(rows, columns);                         // construct screen    
     
     Cell position(rows/2, (columns/2)-(wormSize/2));    // starting position to place worm head
     
     Worm worm(position, n);                           // initialize worm
     
     screen.wormOccupy(worm.head());                 // position occupied by worm
     
     for (size_t i = 0; i < wormSize; i++) {       // add worm segments
          mvaddch(position.row(), position.column(), 'o');
          position.column(position.column()+1);
          worm.addHead(position);
          screen.wormOccupy(position);
     }

     mvaddch(position.row(), position.column(), '@');        // add worm head to screen

     std::pair<Cell, int> snack = generateSnack(screen);   // generate a snack
     
     refresh();  // this function call forces the screen to be updated. 
     
     int growing = 0;                // growth value, representing segments to grow
     bool moving = false;           // moving flag
     Cell startingCell = position; // worm head starting cell
     do {  // while the current position is free
          // if the worm is moving
          
          if (moving) {
               mvaddch(worm.head().row(), worm.head().column(), 'o');  // make the old head a segment of the worm
               mvaddch(position.row(), position.column(), '@');       // make the new position the head of the worm
               worm.addHead(position);        // add a head to the worm at the cell position
               screen.wormOccupy(position);  // occupy the screen with the worm's head
          }
          
          // if the snack has not been eaten by the worm
          if (position != snack.first) {
               if (moving && growing <= 0) {         // if the worm is moving and has 0 segments to add
                    // remove tail from the screen
                    mvaddch(worm.tail().row(), worm.tail().column(), ' '); 
                    screen.makeFree(worm.tail()); // make the screen free at the tail location
                    worm.removeTail();           // remove the worm's tail
               }
               else if (moving && growing > 0) growing--; // else decrement segments to add
          }
          
          // else if a snack has been eaten by the worm
          else if (position == snack.first) { 
               growing += snack.second;           // add the snack's value to the segments to add
               score += snack.second;            // add the snack's value to the score
               move(0, scoreColumn+6);          // move to location of score on screen
               for (auto &c : std::to_string(score)) addch(c);   // write score to screen
               snack = generateSnack(screen); // generate a new snack
          }
          

          refresh(); // refresh the screen

          switch (get_input()) { 
               case UP: position.row(position.row()-1);          // UP    - W
                    break;
               case LEFT: position.column(position.column()-1);  // LEFT  - A
                    break;
               case DOWN: position.row(position.row()+1);        // DOWN  - S
                    break;     
               case RIGHT: position.column(position.column()+1); // RIGHT - D
                    break; 
               case STOP: moving = false;                        // STOP  - Space
                    startingCell = position; 
                    break;                                       // ELSE
               case INVALID: terminate(score);                   // INVALID                                             
          }

          // if the worm is not moving and is at the starting cell
          if (!moving && position == startingCell) 
               screen.makeFree(position);    // make the position free
          else moving = true;               // else the worm is moving

     } while(screen.isFree(position));    // while the position on screen is free

     terminate(score);
}

/**
 * @brief curses startup
 */
void startup(void) {
     initscr();     /* activate the curses */
     curs_set(0);   /* do not display the cursor */
     clear();       /* clear the screen that curses provides */
     noecho();	     /* prevent the input chars to be echoed to the screen */
     cbreak();	     /* change the stty so that characters are delivered to the program as they are typed--no need to hit the return key!*/
}

/**
 * @brief curses termination
 * 
 * @param score
 */
void terminate(int score) {
     mvcur(0, COLS - 1, LINES - 1, 0);
     clear();
     refresh();
     endwin();
     std::cout << "Game Over!\nYou scored: " << score << " points\n";
}

/**
 * @brief return a randomly generated a snack
 * 
 * @param screen 
 * @return std::pair<Cell, int> snack
 */
std::pair<Cell, int> generateSnack(Screen &screen) {
     Cell snackCell = screen.getRandomFreeCell(); // get a random free cell
     srand(time(NULL));
     int randomValue = rand() % 9 + 1;            // get a random value between 1-9
     mvaddch(snackCell.row(), snackCell.column(), std::to_string(randomValue)[0]);
     return std::make_pair(snackCell, randomValue);
}

/**
 * @brief worm functionality test
 * 
 * @param worm 
 */
void functionalityTest(Worm worm) {

     /* First test: add and remove 1 element consistently */
     for (int i = 0; i < 10; i++) {
          Cell c(0, i);
          assert(worm.getWorm()->empty());
          assert(worm.getWorm()->push_back(c));
          assert(worm.getWorm()->NumElements() == 1);
          assert(worm.getWorm()->exists(c));
          assert(worm.getWorm()->front() == c);
          assert(worm.getWorm()->pop_front() == c);
     }
     /* Second test: repeat to make sure the worm wraps around */
     for (int i = 0; i < worm.getWorm()->getMaxQsize(); i++) {
          Cell c(0, -1 * i);
          assert(worm.getWorm()->empty());
          assert(worm.getWorm()->push_back(c));
          assert(worm.getWorm()->NumElements() == 1);
          assert(worm.getWorm()->exists(c));
          assert(worm.getWorm()->front() == c);
          assert(worm.getWorm()->pop_front() == c);
     }

     /* Then: fill worm and make sure it can't take any more elements */
     for (int i = 0; i < worm.getWorm()->getMaxQsize(); i++) {
          Cell c(0, i);
          assert(worm.getWorm()->push_back(c));
     }

     /* Make sure the worm is full and can't push any more elements*/
     assert(worm.getWorm()->full());

     while (!worm.getWorm()->empty()) {
          worm.getWorm()->pop_front();
     }
     assert(worm.getWorm()->empty());

}
