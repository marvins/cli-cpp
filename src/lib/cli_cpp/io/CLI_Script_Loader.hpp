/**
 * @file    CLI_Script_Loader.hpp
 * @author  Marvin Smith
 * @date    6/30/2015
*/
#ifndef __CLI_CPP_LIB_IO_CLI_SCRIPT_LOADER_HPP__
#define __CLI_CPP_LIB_IO_CLI_SCRIPT_LOADER_HPP__

// C++ Standard Libraries
#include <deque>
#include <string>


namespace CLI{
namespace IO{


/**
 * @brief Load CLI Script and return a list of commands to run.
 *
 * @return List of CLI Commands.
*/
std::deque<std::string> Load_CLI_Script( const std::string& script_path );

} // End of IO  Namespace
} // End of CLI Namespace

#endif
