/**
 * @file    A_Render_Driver_Context_Base.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Driver_Context_Base.hpp"

// CLI Libraries
#include "../utility/Log_Utilities.hpp"

// C++ Libraries
#include <iostream>


namespace CLI{
namespace RENDER{

/********************************/
/*          Constructor         */
/********************************/
A_Render_Driver_Context_Base::A_Render_Driver_Context_Base( const std::string& cli_title,
                                                            const bool&        redirect_stdout,
                                                            const bool&        redirect_stderr )
  : m_cli_title(cli_title),
    m_class_name("A_Render_Driver_Context_Base"),
    m_redirect_stdout(redirect_stdout),
    m_redirect_stderr(redirect_stderr),
    m_waiting_command_response(false)
{
}


/**********************************/
/*          Destructor            */
/**********************************/
A_Render_Driver_Context_Base::~A_Render_Driver_Context_Base()
{
}


/****************************************************/
/*      Set the Command Waiting Response Values     */
/****************************************************/
void A_Render_Driver_Context_Base::Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response )
{
    m_waiting_command_response_value = response;
    m_waiting_command_response = true;
}


/**************************************************/
/*      Check the waiting response flag value     */
/**************************************************/
bool A_Render_Driver_Context_Base::Check_Waiting_Command_Response(){
    
    // Log
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << ". Status: " << std::boolalpha << m_waiting_command_response;
    
    // Avoid null
    if( m_waiting_command_response_value == nullptr ){ 
        return false; 
    }

    // Avoid if not waiting
    if( m_waiting_command_response == false ){
        return false;
    }

    // Check if still waiting
    if( m_waiting_command_response_value->Check_System_Response() == false &&
        m_waiting_command_response == true )
    {
        return true;
    }

    // Check if recieved
    if( m_waiting_command_response_value->Check_System_Response() &&
        m_waiting_command_response == true )
    {
        m_waiting_command_response = false;
        return true;
    }

    else{
        return false;
    }
}


} // End of RENDER Namespace
} // End of CLI    Namespace

