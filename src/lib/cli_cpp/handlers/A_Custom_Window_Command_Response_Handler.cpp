/**
 * @file    A_Custom_Window_Command_Response_Handler.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
 */
#include "A_Custom_Window_Command_Response_Handler.hpp"


// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace HANDLER{

/**********************************/
/*          Constructor           */
/**********************************/
A_Custom_Window_Command_Response_Handler::A_Custom_Window_Command_Response_Handler( RENDER::A_Render_Manager_Base::ptr_t render_manager )
  : CLI::A_Command_Response_Handler_Base(),
    m_class_name("A_Custom_Window_Command_Response_Handler"),
    m_render_manager(render_manager)
{
}


/****************************************/
/*         Check if Supported           */
/****************************************/
bool A_Custom_Window_Command_Response_Handler::Is_Supported( CLI::CMD::A_Command_Result const& result ) const
{
    // Check the name
    std::map<int,CMD::A_Command>::const_iterator it = m_trigger_commands.begin();
    for( ; it != m_trigger_commands.end(); it++ ){
        if( it->second == result.Get_Command() ){
            return true;
        }
    }


    // Return false
    return false;
}

/****************************************/
/*          Process the Command         */
/****************************************/
void A_Custom_Window_Command_Response_Handler::Process_Command( CLI::CMD::A_Command_Result::ptr_t response )
{
    
    // Check the name
    std::map<int,CMD::A_Command>::iterator it = m_trigger_commands.begin();
    for( ; it != m_trigger_commands.end(); it++ ){
        
        // Check if the commands match
        if( it->second == response->Get_Command() ){
            
            // If the commands match, then set the window
            m_render_manager->Set_Current_Window( it->first );
            
            // Done
            return;
        }
    }

}


/**************************************************/
/*          Register A Trigger Command            */
/**************************************************/
void A_Custom_Window_Command_Response_Handler::Register_Trigger_Command( CMD::A_Command const&  command,
                                                                         int const&             window_id )
{

    // Trigger commands
    m_trigger_commands[window_id] = command;

}



} // End of HANDLER Namespace
} // End of CLI     Namespace

