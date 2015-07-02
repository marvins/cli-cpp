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
    m_description(""),
    m_command_argument_list(0)
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
    m_description(description),
    m_command_argument_list(0)
{
}



/************************************/
/*              Add Name            */
/************************************/
void A_CLI_Command::Add_Name( const std::string& name )
{
    m_names.push_back( name );
}


/***************************************************/
/*              Add Command Argument               */
/***************************************************/
void A_CLI_Command::Add_Argument( const A_Command_Argument& arg )
{
    m_command_argument_list.push_back(arg);
}

/****************************/
/*      Set formal Name     */
/****************************/
void A_CLI_Command::Set_Formal_Name( const std::string& formal_name )
{
    m_formal_name = formal_name;
}


/************************************/
/*         Check Arguments          */
/************************************/
bool A_CLI_Command::Check_Argument_Type( const int& argument_idx,
                                         const std::string& test_argument )const
{
    // Check the size
    if( argument_idx < 0 || argument_idx >= (int)m_command_argument_list.size() ){
        return false;
    }

    // Compare
    return m_command_argument_list[argument_idx].Is_Valid_Type( test_argument );
}


/****************************/
/*          Is Valid        */
/****************************/
bool A_CLI_Command::Is_Name_Match( const std::string& name )const
{
    // Iterate over all supported names
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


/********************************************/
/*      Check if Argument is a Match        */
/********************************************/
bool A_CLI_Command::Is_Argument_Substring( const int&         argument_index,
                                           const std::string& argument_name,
                                           std::string&  match_name )const
{
    // Don't go over bounds
    if( argument_index >= (int)m_command_argument_list.size() ){
        return false;
    }

    // Pass to argument
    return m_command_argument_list[argument_index].Is_Argument_Substring( argument_name,
                                                                          match_name );

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


/*****************************************/
/*          Write as a Command           */
/*****************************************/
A_Command A_CLI_Command::To_Command()const{

    return A_Command( m_names[0],
                      Get_Description(),
                      false,
                      m_command_argument_list );
}


/*************************************************/
/*          Write as a debugging string          */
/*************************************************/
std::string A_CLI_Command::To_Debug_String()const
{

    // Create the stream
    std::stringstream sin;
    sin << m_class_name << ":\n";
    sin << "    Formal Name: " << Get_Formal_Name() << std::endl;
    sin << "    Description: " << Get_Description() << std::endl;

    // Iterate over arguments
    sin << "    Arguments:\n";
    for( size_t i=0; i<m_command_argument_list.size(); i++ ){
        sin << m_command_argument_list[i].To_Debug_String(8) << std::endl;
    }

    // Return output
    return sin.str();
}


} // End of CMD Namespace
} // End of CLI Namespace


