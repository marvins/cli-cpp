/**
 * @file    A_Command_Argument.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#include "A_Command_Argument.hpp"

// Boost Libraries
#include <boost/regex.hpp>

namespace CLI{
namespace CMD{


/**********************************/
/*          Constructor           */
/**********************************/
A_Command_Argument::A_Command_Argument()
  : m_name(""),
    m_type(CommandArgumentType::UNKNOWN),
    m_description(""),
    m_default_value(""),
    m_required(true)
{
}


/**********************************/
/*          Constructor           */
/**********************************/
A_Command_Argument::A_Command_Argument( const std::string&             arg_name,
                                        const CommandArgumentType&  arg_type,
                                        const std::string&             arg_description,
                                        const bool&                    arg_required,
                                        const std::string&             arg_default_value )
   : m_name(arg_name),
     m_type(arg_type),
     m_description(arg_description),
     m_default_value(arg_default_value),
     m_required(arg_required)
{
}


/*****************************************/
/*          Check String Type            */
/*****************************************/
bool A_Command_Argument::Is_Valid_Type( const std::string& test_str )const
{
    // String Match
    boost::smatch what;

    // Compare Integer Types
    if( m_type == CommandArgumentType::INTEGER ){
        return boost::regex_match( test_str, what, boost::regex("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?")); 
    }

    // Compare Float Types
    if( m_type == CommandArgumentType::FLOAT ){
        return boost::regex_match( test_str, what, boost::regex("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?")); 
    }

    // Compare String Types
    if( m_type == CommandArgumentType::STRING ){
        return true;
    }

    // Otherwise, there is a problem
    return false;
}

/*****************************************/
/*          Equivalent Operator          */
/*****************************************/
bool A_Command_Argument::operator == ( A_Command_Argument const& other )const
{
    // Check the name
    if( m_name != other.m_name ){
        return false;
    }

    // Check the type
    if( m_type != other.m_type ){
        return false;
    }
    
    // Skip the description


    // Check the default value
    if( m_default_value != other.m_default_value ){
        return false;
    }

    // Check if required
    if( m_required != other.m_required ){
        return false;
    }

    // Otherwise, true
    return true;
}

} // End of CMD Namespace
} // End of CLI Namespace

