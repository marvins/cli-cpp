/**
 * @file    A_System_Command_Response_Handler.cpp
 * @author  Marvin Smith
 * @date    6/2/2015
 */
#include "A_System_Command_Response_Handler.hpp"

// C++ Standard Libraries
#include <iostream>

/**********************************/
/*          Constructor           */
/**********************************/
A_System_Command_Response_Handler::A_System_Command_Response_Handler( State_Manager& state_manager )
  : CLI::A_Command_Response_Handler_Base(),
    m_state_manager(state_manager)
{
}


/****************************************/
/*         Check if Supported           */
/****************************************/
bool A_System_Command_Response_Handler::Is_Supported( CLI::CMD::A_Command_Result const& result ) const
{
    // Make sure the command name matches
    if( result.Get_Command().Get_Name() == "system-shutdown" ){
        return true;
    }

    // Otherwise, return false
    return false;
}

/****************************************/
/*          Process the Command         */
/****************************************/
void A_System_Command_Response_Handler::Process_Command( CLI::CMD::A_Command_Result::ptr_t response ){

    // Check for system shutdown
    if( response->Get_Command().Get_Name() == "system-shutdown" ){
        m_state_manager.Signal_System_Shutdown();
        response->Set_System_Response("Shutting down system now!");
    }
}


