/**
 * @file    A_Render_Manager_Base.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Render_Manager_Base.hpp"

// C++ Standard Libraries
#include <iostream>
#include <sstream>

// CLI Libraries
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"

namespace CLI{
namespace RENDER{

/****************************/
/*      Constructor         */
/****************************/
A_Render_Manager_Base::A_Render_Manager_Base()
  : m_command_history(std::make_shared<CMD::A_Command_History>()),
    m_command_counter(0),
    m_waiting_command_response(false),
    m_waiting_command_response_value(nullptr),
    m_class_name("A_Render_Manager_Base")
{
}


/*************************************/
/*      Update the Command List      */
/*************************************/
void A_Render_Manager_Base::Update_Command_List( const std::vector<CMD::A_Command>& command_list )
{
    m_command_list = command_list;
}


/*************************************/
/*      Update the Command List      */
/*************************************/
void A_Render_Manager_Base::Update_CLI_Command_List( const std::vector<CMD::A_CLI_Command>& cli_command_list )
{
    m_cli_command_list = cli_command_list;
}


/****************************************************/
/*      Set the Command Waiting Response Values     */
/****************************************************/
void A_Render_Manager_Base::Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response )
{
    m_waiting_command_response_value = response;
    m_waiting_command_response = true;
}


/**************************************************/
/*      Check the waiting response flag value     */
/**************************************************/
bool A_Render_Manager_Base::Check_Waiting_Command_Response(){
    
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

