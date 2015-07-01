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
const std::string ANSI_CURSORINVIS = "\033[?25l";
const std::string ANSI_CURSORVIS   = "\033[?25h";

/// ANSI Newlines
const std::string ANSI_NEWLINE = "\n\r";

/// ANSI Color Codes
const std::string ANSI_RESET   = "\033[m";
const std::string ANSI_BLACK   = "\033[30m";
const std::string ANSI_RED     = "\033[31m";
const std::string ANSI_GREEN   = "\033[32m";
const std::string ANSI_YELLOW  = "\033[33m";
const std::string ANSI_BLUE    = "\033[34m";
const std::string ANSI_MAGENTA = "\033[35m";
const std::string ANSI_CYAN    = "\033[36m";
const std::string ANSI_WHITE   = "\033[37m";

/// ANSI Background Colors
const std::string ANSI_BACK_BLACK   = "\033[40m";
const std::string ANSI_BACK_RED     = "\033[41m";
const std::string ANSI_BACK_GREEN   = "\033[42m";
const std::string ANSI_BACK_YELLOW  = "\033[43m";
const std::string ANSI_BACK_BLUE    = "\033[44m";
const std::string ANSI_BACK_MAGENTA = "\033[45m";
const std::string ANSI_BACK_CYAN    = "\033[46m";
const std::string ANSI_BACK_WHITE   = "\033[47m";


} // End of UTILS Namespace
} // End of CLI   Namespace

#endif
