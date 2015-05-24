/**
 * @file    NCurses_Utilities.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __THRIRDPARTY_NCURSES_NCURSES_UTILITIES_HPP__
#define __THRIRDPARTY_NCURSES_NCURSES_UTILITIES_HPP__

// NCurses Libraries
#include <ncurses.h>

// C++ Standard Libraries
#include <memory>
#include <string>

namespace CLI{
namespace NCURSES{


/**
 * @brief Create NCurses Window
 */
void Initialize();


/**
 * @brief Finalize NCurses Windows
 */
void Finalize();


/**
 * @brief Abort
 */
void Abort();


} // End of NCURSES Namspace
} // End of CLI     Namespace

#endif
