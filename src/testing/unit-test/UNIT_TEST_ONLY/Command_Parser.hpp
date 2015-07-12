/**
 * @file    Command_Parser.hpp
 * @author  Marvin Smith
 * @date    7/12/2015
*/
#ifndef __CLI_CPP_TESTING_UNIT_TEST_COMMAND_PARSER_HPP__
#define __CLI_CPP_TESTING_UNIT_TEST_COMMAND_PARSER_HPP__

// C++ Libraries
#include <string>


/**
 * @brief Process Command-Line Arguments
*/
void Process_Command_Line( int argc, char* argv[] );


/**
 * @brief Print Usage Instructions
*/
void Usage( const std::string& application_name );


#endif
