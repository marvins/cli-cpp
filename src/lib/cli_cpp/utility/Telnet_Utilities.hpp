/**
 * @file    Telnet_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/1/2015
*/
#ifndef __CLI_CPP_LIB_UTILITY_TELNET_UTILITIES_HPP__
#define __CLI_CPP_LIB_UTILITY_TELNET_UTILITIES_HPP__

// C++ Standard Libraries
#include <string>


namespace CLI{
namespace UTILS{
namespace TELNET{

// Telnet Codes
const char echo      = 1;
const char supp_ga   = 3;
const char cols      = 8;
const char lines     = 9;
const char term_type = 24;
const char term_size = 31;
const char linemode  = 34; // \042 (oct)
const char SE   = 240;
const char SB   = 250;
const char WILL = 251; // -5 (char), \373 Oct
const char WONT = 252; // -4 (char), \374
const char DO   = 253; // -3 (char), \375 Oct
const char DONT = 254; // -2
const char IAC  = 255; // -1 (char), \377 Oct

/**
 * @brief Convert input characters into Telnet Command
 */
std::string Telnet_To_Pretty_String( const std::string& substr );

/**
 * @brief Create terminal size command
*/
void Telnet_Get_Window_Size( const int& fd );


} // End of TELNET Namespace
} // End of UTILS  Namespace 
} // End of CLI    Namespace

#endif
