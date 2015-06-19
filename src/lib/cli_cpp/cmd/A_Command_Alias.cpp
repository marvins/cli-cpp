/**
 * @file    A_Command_Alias.cpp
 * @author  Marvin Smith
 * @date    6/19/2015
 */
#include "A_Command_Alias.hpp"

// CLI Libraries
#include "../utility/String_Utilities.hpp"


namespace CLI{
namespace CMD{


/*********************************/
/*          Constructor          */
/*********************************/
A_Command_Alias::A_Command_Alias()
  : m_class_name("A_Command_Alias"),
    m_alias_name(""),
    m_command_text("")
{
}

/********************************/
/*         Constructor          */
/********************************/
A_Command_Alias::A_Command_Alias( const std::string& alias_name,
                                  const std::string& command_text )
  : m_class_name("A_Command_Alias"),
    m_alias_name(UTILS::Format_Command_String(alias_name)),
    m_command_text(command_text)
{
}


/*************************************/
/*        Is Alias Name Match        */
/*************************************/
bool A_Command_Alias::Is_Alias_Name_Match( const std::string&  test_input,
                                           const bool&         match_whole,
                                           std::string&        formatted_output ) const
{
    // Clear the output
    formatted_output = "";
   
    // Format the string
    std::string formatted_input = UTILS::Format_Command_String( test_input );

    // If we are matching the whole, just do a compare
    if( match_whole == true ){
        if( formatted_input == m_alias_name ){
            formatted_output = m_command_text;
            return true;
        } else {
            return false;
        }
    }

    // If the alias is larger than the formatted input, then we
    // know it is false
    if( m_alias_name.size() > formatted_input.size() ){
        return false;
    }

    // If the alias is the same size, do a compare
    if( m_alias_name.size() == formatted_input.size() ){
        if( m_alias_name == formatted_input ){
            formatted_output = m_command_text;
            return true;
        }
        else{
            return false;
        }
    }

    // Lastly, do a substring if smaller
    if( formatted_input.substr(0, m_alias_name.size()) == m_alias_name ){
        
        // Append the output
        formatted_output = m_command_text + formatted_input.substr(m_alias_name.size());
        return true;
    }

    // Otherwise, it failed
    return false;
}


/*****************************************************/
/*         Load an Alias Configuration File          */
/*****************************************************/
std::vector<A_Command_Alias> A_Command_Alias::Load_Alias_Configuration_File( const std::string& pathname )
{



}


} // End of CMD Namespace
} // End of CLI Namespace

