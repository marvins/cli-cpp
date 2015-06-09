/**
 * @file    A_Command.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#include "A_Command.hpp"

// C++ Standard Libraries
#include <sstream>

namespace CLI{
namespace CMD{

/**********************************/
/*          Constructor           */
/**********************************/
A_Command::A_Command()
 :  m_class_name("A_Command"),
    m_command_name(""),
    m_command_description(""),
    m_expect_response(false),
    m_command_argument_list(0)
{
}


/**********************************/
/*          Constructor           */
/**********************************/
A_Command::A_Command( const std::string&         command_name,
                              const std::string& command_description,
                              const bool&        command_expect_response )
  : m_class_name("A_Command"),
    m_command_name(command_name),
    m_command_description(command_description),
    m_expect_response(command_expect_response),
    m_command_argument_list(0)
{
}


/**********************************/
/*          Constructor           */
/**********************************/
A_Command::A_Command( const std::string&                      command_name,
                      const std::string&                      command_description,
                      const bool&                             command_expect_response,
                      const std::vector<A_Command_Argument>&  command_arguments )
  : m_class_name("A_Command"),
    m_command_name(command_name),
    m_command_description(command_description),
    m_expect_response(command_expect_response),
    m_command_argument_list(command_arguments)
{
}


/**************************************/
/*        Check if Name Match         */
/**************************************/
bool A_Command::Is_Name_Match( const std::string& command_name )const
{
    if( m_command_name == command_name ){
        return true;
    }
    return false;
}


/************************************************/
/*        Check if Name Substring Match         */
/************************************************/
bool A_Command::Is_Name_Substring( const std::string& command_name )const
{
    // Check if command name is less than or equal
    if( command_name.size() > m_command_name.size() ){
        return false;
    }

    // Check if the sizes are equal
    if( command_name.size() == m_command_name.size() ){
        return Is_Name_Match( command_name );
    }

    // Otherwise, check the substring
    return (m_command_name.substr(0, command_name.size()) == command_name );
}


/********************************************/
/*      Check if Argument is a Match        */
/********************************************/
bool A_Command::Is_Argument_Substring( const int&         argument_index,
                                       const std::string& argument_name,
                                       std::string&  match_name )const
{
    // Don't go over bounds
    if( argument_index >= m_command_argument_list.size() ){
        return false;
    }

    // Pass to argument
    return m_command_argument_list[argument_index].Is_Argument_Substring( argument_name,
                                                                          match_name );

}

/************************************/
/*         Check Arguments          */
/************************************/
bool A_Command::Check_Argument_Type( const int& argument_idx,
                                     const std::string& test_argument )const
{
    // Check the size
    if( argument_idx < 0 || argument_idx >= (int)m_command_argument_list.size() ){
        return false;
    }

    // Compare
    return m_command_argument_list[argument_idx].Is_Valid_Type( test_argument );
}


/************************************/
/*      Write as a debug string     */
/************************************/
std::string A_Command::To_Debug_String()const
{
    // Create stream
    std::stringstream sin;
    sin << "A_Command:\n";
    sin << "   Name: " << Get_Name() << "\n";
    sin << "   Desc: " << Get_Description() << "\n";
    
    return sin.str();
}


} // End of CMD
} // End of CLI

