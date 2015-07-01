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
#include <sstream>


// CLI Libraries
#include "../utility/Filesystem_Utilities.hpp"
#include "../utility/String_Utilities.hpp"


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
    m_required(true),
    m_autocomplete_path(false)
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
     m_required(arg_required),
     m_autocomplete_path(false)
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
                                        const bool&                    arg_autocomplete_path,
                                        std::vector<std::string>const& arg_autocomplete_terms )
   : m_class_name("A_Command_Argument"),
     m_name(arg_name),
     m_type(arg_type),
     m_description(arg_description),
     m_default_value(arg_default_value),
     m_required(arg_required),
     m_autocomplete_path(arg_autocomplete_path),
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

    // Compare Path Types
    if( m_type == CommandArgumentType::PATH ){
        return true;
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
    // List of potential matches
    std::vector<std::string> match_list;

    // Iterate over autocomplete terms
    for( size_t i=0; i<m_autocomplete_terms.size(); i++ )
    {
        // Check the size
        if( argument_name.size() > m_autocomplete_terms[i].size() ){
            continue;
        }

        // Check if equal
        if( argument_name == m_autocomplete_terms[i] ){
            match_list.push_back(m_autocomplete_terms[i]); 
            continue;
        }

        // Check substring
        if( m_autocomplete_terms[i].substr(0, argument_name.size()) == argument_name )
        {
            match_list.push_back(m_autocomplete_terms[i]); 
            continue;
        }
    }

    // If the type if a filesystem type, get a list of files
    if( m_type == CommandArgumentType::PATH ){
        
        // Get a list of paths
        std::vector<std::string> pathname_list = FS::Get_Contents( argument_name );

        // iterate over the list, checking the names
        for( size_t i=0; i<pathname_list.size(); i++ ){
            
            // If the pathname is shorter, it cannot be valid
            if( pathname_list[i].size() < argument_name.size() ){
                continue;
            }

            // Otherwise, do a substring check
            std::string temp_path = pathname_list[i].substr(0, argument_name.size());
            if( temp_path == argument_name ){
                match_list.push_back( pathname_list[i] );
            }
        }
    }

    // Check if we found any matches
    if( match_list.size() <= 0 ){
        match_name = "";
        return false;
    }

    // Find the minimum spanning substring
    match_name = match_list[0];
    for( size_t i=1; i<match_list.size(); i++ ){
        match_name = UTILS::String_Substring_Match( match_name, match_list[i]);
    }
    return true;
}


/*********************************************/
/*          Print as a Debug String          */
/*********************************************/
std::string A_Command_Argument::To_Debug_String( int const& offset )const
{
    // Create output stream
    std::stringstream sin;
    std::string gap( offset, ' ');

    // Start adding info
    sin << gap << m_class_name << ":\n";
    sin << gap << "    Name        : " << m_name << std::endl;
    sin << gap << "    Arg Type    : " << CommandArgumentTypeToString(m_type) << std::endl; 
    sin << gap << "    Description : " << m_description << std::endl;
    sin << gap << "    Default     : " << m_default_value << std::endl;
    sin << gap << "    Required    : " << std::boolalpha << m_required << std::endl;
    sin << gap << "    Autocomplete Terms: " << std::endl;
    for( size_t i=0; i<m_autocomplete_terms.size(); i++ ){
        sin << gap << "       " << i << " : " << m_autocomplete_terms[i] << std::endl;
    }

    // return output
    return sin.str();
}


} // End of CMD Namespace
} // End of CLI Namespace

