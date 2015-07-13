/**
 * @file    CommandArgumentType.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#include "CommandArgumentType.hpp"

namespace CLI{
namespace CMD{

/*********************************************/
/*        Convert Argtype to string          */
/*********************************************/
std::string CommandArgumentTypeToString( CommandArgumentType const& arg_type )
{
    // String
    if( arg_type == CommandArgumentType::STRING ){
        return "STRING";
    }


    // Integer
    if( arg_type == CommandArgumentType::INTEGER ){
        return "INTEGER";
    }


    // Float
    if( arg_type == CommandArgumentType::FLOAT ){
        return "FLOAT";
    }
    
    // File
    if( arg_type == CommandArgumentType::PATH ){
        return "PATH";
    }

    return "UNKNOWN";
}


/*********************************************/
/*        Convert String to Argtype          */
/*********************************************/
CommandArgumentType  StringToCommandArgumentType( const std::string& arg_type )
{

    // String Type
    if( arg_type == "string" ||
        arg_type == "STRING" )
    {
        return CommandArgumentType::STRING;
    }

    // Integer Type
    if( arg_type == "integer" ||
        arg_type == "INTEGER" )
    {
        return CommandArgumentType::INTEGER;
    }

    // Float Type
    if( arg_type == "float" || 
        arg_type == "FLOAT" )
    {
        return CommandArgumentType::FLOAT;
    }
    
    // Path
    if( arg_type == "path" ||
        arg_type == "PATH" )
    {
        return CommandArgumentType::PATH;
    }

    return CommandArgumentType::UNKNOWN;
}


} // End of CMD Namespace
} // End of CLI Namespace


