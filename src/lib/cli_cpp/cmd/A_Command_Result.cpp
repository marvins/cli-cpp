/**
 * @file    A_Command_Result.cpp
 * @author  Marvin Smith
 * @date    5/19/2015
*/
#include "A_Command_Result.hpp"

// C++ Standard Libraries
#include <sstream>
#include <string>

// CLI Libraries
#include "../utility/Log_Utilities.hpp"

namespace CLI{
namespace CMD{


/*************************************/
/*            Constructor            */
/*************************************/
A_Command_Result::A_Command_Result()
  : m_parse_status( CommandParseStatus::UNKNOWN ),
    m_system_response_set(false),
    m_system_response_value("")
{
}


/*************************************/
/*            Constructor            */
/*************************************/
A_Command_Result::A_Command_Result( CommandParseStatus const&  parse_status,
                                            A_Command const&          command)
  : m_parse_status(parse_status),
    m_command(command)
{
}


/*************************************/
/*            Constructor            */
/*************************************/
A_Command_Result::A_Command_Result( CommandParseStatus const&     parse_status,
                                            A_Command const&             command,
                                            std::vector<std::string> const&  argument_values )
  : m_parse_status(parse_status),
    m_command(command),
    m_argument_values(argument_values)
{
}


/*****************************************/
/*      Get the parse status string      */
/*****************************************/
std::string A_Command_Result::Get_Parse_Status_String()const
{
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ << ", Response Expected: " << std::boolalpha << m_command.Response_Expected() << ", Status: " << Check_System_Response();

    // Check if we are waiting on a response
    if( m_command.Response_Expected() == true &&
        Check_System_Response() == false &&
        m_parse_status == CommandParseStatus::VALID )
    {
        return "Waiting on system response.";
    }
    if( m_command.Response_Expected() == true &&
        Check_System_Response() == true )
    {
        return m_system_response_value;
    }

    // otherwise, return the default
    return CMD::CommandParseStatusToHistoryString( m_parse_status );

}


/*************************************/
/*      Set the system response      */
/*************************************/
void A_Command_Result::Set_System_Response( const std::string& system_response ){
    m_system_response_value = system_response;
    m_system_response_set = true;
}


/**********************************************/
/*          Process Command Arguments         */
/**********************************************/
A_Command_Result  A_Command_Result::Process_Arguments( const A_Command& command,    
                                                               const std::vector<std::string>&  arguments )
{
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "Start of Method. File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ ;
    
    // Check for no arguments
    if( arguments.size() <= 0 ){
        
        // If we have no arguments passed in, yet the first argument
        // in the comparison command has a required argument, then throw an error.
        if( command.Get_Argument_List().size() > 0 &&
            command.Get_Command_Argument(0).Is_Required() == true )
        {
            return A_Command_Result( CommandParseStatus::INVALID_ARGUMENTS,
                                     command,
                                     arguments );
        }

        // Otherwise, we are fine.
        else{
            return A_Command_Result( CommandParseStatus::VALID,
                                     command,
                                     arguments );
        }
    }
    
    // Check for enough arguments
    for( int i=(int)arguments.size(); i<(int)command.Get_Argument_List().size(); i++ ){
        
        // Validate missing argument is not required
        if( command.Get_Command_Argument(i).Is_Required() == true ){
            return A_Command_Result( CommandParseStatus::INVALID_ARGUMENTS,
                                     command,
                                     arguments );
        }
    }

    //  Iterate over arguments
    for( size_t arg=0; arg < arguments.size(); arg++ )
    {
        // Check the types
        if( command.Check_Argument_Type( arg, arguments[arg] ) == false ){
            return A_Command_Result( CommandParseStatus::INVALID_ARGUMENTS,
                                     command,
                                     arguments );
        }
    }


    // Check the excess arguments
    if( arguments.size() > command.Get_Argument_List().size() ){
        return A_Command_Result( CommandParseStatus::EXCESSIVE_ARGUMENTS,
                                 command,
                                 arguments );
    }
    
    // Return success
    return A_Command_Result( CommandParseStatus::VALID,
                             command,
                             arguments );


}


/************************************/
/*      Print to Debug String       */
/************************************/
std::string A_Command_Result::To_Debug_String( const int& offset )const
{
    // create the gap
    std::string gap = "";
    for( int i=0; i<offset; i++ ){
        gap += ' ';
    }

    // Print the output
    std::stringstream sin;
    sin << gap << "A_Command_Result:\n";
    sin << gap << "    Command Name: " << m_command.Get_Name() << "\n";
    sin << gap << "    Command Desc: " << m_command.Get_Description() << "\n";
    sin << gap << "    Command Resp: " << std::boolalpha << m_command.Response_Expected() << "\n";
    sin << gap << "    Parse Status: " << CommandParseStatusToString( m_parse_status ) << std::endl;
    sin << gap << "    Command Args:\n"; 
    for( size_t i=0; i<m_command.Get_Argument_List().size(); i++ ){
        sin << gap << "       Argument " << i << " : Name   : " << m_command.Get_Argument_List()[i].Get_Name() << "\n";
        sin << gap << "                              Type   : " << CommandArgumentTypeToString(m_command.Get_Argument_List()[i].Get_Type()) << "\n";
        sin << gap << "                              Desc   : " << m_command.Get_Argument_List()[i].Get_Description() << "\n";
        sin << gap << "                              Req    : " << std::boolalpha << m_command.Get_Argument_List()[i].Is_Required() << std::endl;
        sin << gap << "                              Value  : ";
        if( m_argument_values.size() > i ){ sin << m_argument_values[i]; }
        sin << "\n";
        sin << gap << "                              Default: " << m_command.Get_Argument_List()[i].Get_Default_Value() << std::endl;
    }

    return sin.str();
}


} // End of CMD Namespace
} // End of CLI Namespace

