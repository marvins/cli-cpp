/**
 * @file    NCurses_Utilities.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "NCurses_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace NCURSES{

/*************************************/
/*      Create NCurses Context       */
/*************************************/
void Initialize()
{
    // Initialize
    initscr();

    // Clear the window
    clear();
    noecho();

    // Set the keyboard
    keypad( stdscr, TRUE );

    // Prevent blocking
    nodelay( stdscr, true);
    
    // Initialize Color
    start_color();

    // Initialize Color Pairs
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
}


/****************************************/
/*      Finalize NCurses Context        */
/****************************************/
void Finalize()
{
    // End the window
    endwin();
}


/*****************************/
/*      Abort NCurses        */
/*****************************/
void Abort()
{
    // Shutdown
    endwin();
}



} // End of NCURSES Namespace
} // End of CLI     Namespace

