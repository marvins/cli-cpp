/**
 * @file    CommandArgumentType.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CMD_CLICOMMANDARGUMENT_HPP__
#define __CLI_CMD_CLICOMMANDARGUMENT_HPP__

// C++ Standard Libraries
#include <cinttypes>
#include <string>

namespace CLI{
namespace CMD{

/**
 * @enum CommandArgument
*/
enum class CommandArgumentType : uint8_t {
    UNKNOWN = 0,
    STRING  = 1,
    INTEGER = 2,
    FLOAT   = 3,
    PATH    = 4 /**<  Command Argument is a Pathname.*/,
}; // End of CommandArgument Enumeration


/**
 * @brief Convert a CommandArgumentType to String
*/
std::string CommandArgumentTypeToString( const CommandArgumentType& arg_type );


/**
 * @brief Convert a String to CommandArgumentType
 */
CommandArgumentType  StringToCommandArgumentType( const std::string& arg_type );


} // End of CMD Namespace
} // End of CLI Namespace

#endif
