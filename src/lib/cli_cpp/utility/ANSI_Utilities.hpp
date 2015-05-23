/**
 * @file    ANSI_Utilities.hpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#ifndef __CLI_CPP_UTILITY_ANSI_UTILITIES_HPP__
#define __CLI_CPP_UTILITY_ANSI_UTILITIES_HPP__

// C++ Standard Libraries
#include <string>


namespace CLI{
namespace UTILS{

/// ANSI Escape Codes
const std::string ANSI_CLEARSCREEN = "\033[2J";
const std::string ANSI_RESETCURSOR = "\033[;H";

/// ANSI Color Codes
const std::string ANSI_RESET = "\033[m";
const std::string ANSI_BLACK = "\033[30m";
const std::string ANSI_RED   = "\033[31m";
const std::string ANSI_GREEN = "\033[32m";

/// ANSI Background Colors
const std::string ANSI_BACK_BLACK = "\033[40m";
const std::string ANSI_BACK_RED   = "\033[41m";
const std::string ANSI_BACK_GREEN = "\033[42m";


} // End of UTILS Namespace
} // End of CLI   Namespace

#endif
