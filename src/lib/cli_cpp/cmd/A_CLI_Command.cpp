/**
 * @file    A_CLI_Command.cpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#include "A_CLI_Command.hpp"


// C++ Standard Libraries
#include <iostream>


// CLI Libraries
#include "../utility/String_Utilities.hpp"

namespace CLI{
namespace CMD{


/***********************************/
/*          Constructor            */
/***********************************/
A_CLI_Command::A_CLI_Command( const CommandParseStatus& mode )
  : m_class_name("A_CLI_Command"),
    m_mode(mode),
    m_names(0),
    m_formal_name(""),
    m_description("")
{
}


/***********************************/
/*          Constructor            */
/***********************************/
A_CLI_Command::A_CLI_Command( const CommandParseStatus&        mode,
                              const std::vector<std::string>&  names,
                              const std::string&               formal_name,
                              const std::string&               description )
  : m_class_name("A_CLI_Command"),
    m_mode(mode),
    m_names(names),
    m_formal_name(formal_name),
    m_description(description)
{
}



/************************************/
/*              Add Name            */
/************************************/
void A_CLI_Command::Add_Name( const std::string& name )
{
    m_names.push_back( name );
}


/****************************/
/*      Set formal Name     */
/****************************/
void A_CLI_Command::Set_Formal_Name( const std::string& formal_name )
{
    m_formal_name = formal_name;
}


/****************************/
/*          Is Valid        */
/****************************/
bool A_CLI_Command::Is_Match( const std::string& name )const
{
    for( size_t i=0; i<m_names.size(); i++ ){
        if( m_names[i] == name ){
            return true;
        }
    }
    return false;
}


/*******************************************/
/*       Check Name Substring Match        */
/*******************************************/
bool A_CLI_Command::Is_Name_Substring( const std::string& input_string,
                                       std::string&       match_result )const
{
    // Match list
    std::vector<std::string> match_list;

    // Iterate over the name list
    for( size_t i=0; i<m_names.size(); i++ )
    {

        // If the name is less than the input, it cannot match
        if( m_names[i].size() < input_string.size() ){
            continue;
        }

        // If the sizes are the same, do a string compare
        else if( m_names[i].size() == input_string.size() ){
            if( m_names[i] == input_string ){
                match_list.push_back(m_names[i]);
            }
            else{
                continue;
            }
        }

        // Otherwise, the name is greater than the input, so check the substring match
        else{

            // Look for a perfect substring match
            if( m_names[i].substr(0, input_string.size()) == input_string ){
                match_list.push_back(m_names[i]);
            }
        }
    }

    // Check if we found any matches
    if( (int)match_list.size() <= 0 ){
        match_result = "";
        return false;
    }

    // Find the minimum spanning substring
    match_result = match_list[0];
    for( size_t i=1; i<match_list.size(); i++ ){
        match_result = UTILS::String_Substring_Match( match_result, match_list[i]);
    }
    
    // success
    return true;
}


/********************************/
/*      Equivalent Operator     */
/********************************/
bool A_CLI_Command::operator ==( A_CLI_Command const& other )const
{
    // Check the name
    if( m_formal_name != other.m_formal_name ){
        return false;
    }

    // Check the mode
    if( m_mode != other.m_mode ){
        return false;
    }

    // Check the name list
    if( m_names.size() != other.m_names.size() ){
        return false;
    }
    for( int i=0; i<(int)m_names.size(); i++ ){
        if( m_names[i] != other.m_names[i] ){
            return false;
        }
    }

    // return success
    return true;
}


} // End of CMD Namespace
} // End of CLI Namespace


