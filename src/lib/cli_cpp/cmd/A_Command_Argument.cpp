/**
 * @file    A_Command_Argument.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#include "A_Command_Argument.hpp"

// Boost Libraries
#include <boost/regex.hpp>

// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace CMD{


/**********************************/
/*          Constructor           */
/**********************************/
A_Command_Argument::A_Command_Argument()
  : m_class_name("A_Command_Argument"),
    m_name(""),
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
   : m_class_name("A_Command_Argument"),
     m_name(arg_name),
     m_type(arg_type),
     m_description(arg_description),
     m_default_value(arg_default_value),
     m_required(arg_required)
{
}


/**********************************/
/*          Constructor           */
/**********************************/
A_Command_Argument::A_Command_Argument( const std::string&             arg_name,
                                        const CommandArgumentType&     arg_type,
                                        const std::string&             arg_description,
                                        const bool&                    arg_required,
                                        const std::string&             arg_default_value,
                                        std::vector<std::string>const& arg_autocomplete_terms )
   : m_class_name("A_Command_Argument"),
     m_name(arg_name),
     m_type(arg_type),
     m_description(arg_description),
     m_default_value(arg_default_value),
     m_required(arg_required),
     m_autocomplete_terms(arg_autocomplete_terms)
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

/************************************************/
/*       Check if Argument is a Substring       */
/************************************************/
bool A_Command_Argument::Is_Argument_Substring( const std::string& argument_name,
                                                std::string& match_name )const
{
    // Iterate over autocomplete terms
    for( size_t i=0; i<m_autocomplete_terms.size(); i++ )
    {
        // Check the size
        if( argument_name.size() > m_autocomplete_terms[i].size() ){
            continue;
        }

        // Check if equal
        if( argument_name == m_autocomplete_terms[i] ){
            match_name = m_autocomplete_terms[i];
            return true;
        }

        // Check substring
        if( m_autocomplete_terms[i].substr(0, argument_name.size()) == argument_name )
        {
            match_name = m_autocomplete_terms[i];
            return true;
        }
    }

    match_name = "";
    return false;
}


} // End of CMD Namespace
} // End of CLI Namespace

