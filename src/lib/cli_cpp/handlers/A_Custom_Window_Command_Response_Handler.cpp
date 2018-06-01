/**
 * @file    A_Custom_Window_Command_Response_Handler.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
 */
#include "A_Custom_Window_Command_Response_Handler.hpp"

// CLI Libraries
#include "../render/A_Render_Manager_Factory.hpp"
#include "../utility/Log_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace HANDLER{

/**********************************/
/*          Constructor           */
/**********************************/
A_Custom_Window_Command_Response_Handler::A_Custom_Window_Command_Response_Handler()
  : CLI::A_Command_Response_Handler_Base(),
    m_class_name("A_Custom_Window_Command_Response_Handler")
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
void A_Custom_Window_Command_Response_Handler::Process_Command( CLI::CMD::A_Command_Result::ptr_t response,
                                                                const bool&                       wait_on_response )
{
    // Log Entry
    CLI_LOG_CLASS_ENTRY();

    // Get the instance ID
    int instance = response->Get_Instance_ID();

    // Get the render manager
    auto render_manager = RENDER::A_Render_Manager_Factory::Instance_Of( instance,
                                                                         CORE::SessionType::UNKNOWN );

    // Make sure the render manager is valid
    if( render_manager == nullptr ){
        LOG_ERROR( "Render-Manager returned for instance " << instance << " is null.");
    }

    // If so, then finish
    else
    {
        // Check the name
        bool exit_loop = false;
        std::map<int,CMD::A_Command>::iterator it = m_trigger_commands.begin();
        for( ; it != m_trigger_commands.end() && !exit_loop; it++ ){
        
            // Check if the commands match
            if( it->second == response->Get_Command() )
            {
                
                // Get the window id
                int old_win_id = it->first;
                int new_win_id = it->first;

                // If the window-ID is less than 0, we need to find it or throw an error
                if( it->first < 0 )
                {
                    new_win_id = render_manager->Find_Window_ID_By_Trigger_Command( response->Get_Command() );
                }

                if( old_win_id < 0 && new_win_id >= 0 )
                {
                    m_trigger_commands[new_win_id] = m_trigger_commands[old_win_id];
                    m_trigger_commands.erase(old_win_id);
                }

                LOG_TRACE( "Setting Render-Manager to ID: " + std::to_string(new_win_id));

                // If the commands match, then set the window
                render_manager->Set_Current_Window( new_win_id );
            
                // Done
                exit_loop = true;
            }
        }
    }


    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/**************************************************/
/*          Register A Trigger Command            */
/**************************************************/
void A_Custom_Window_Command_Response_Handler::Register_Trigger_Command( CMD::A_Command const&  command,
                                                                         int const&             window_id )
{
    
    // Log Error if ID is negative
    if( window_id < 0 )
    {
        LOG_ERROR( "Window-ID must be greater than zero. Actual: " + std::to_string(window_id));
    }

    // Trigger commands
    m_trigger_commands[window_id] = command;

}



} // End of HANDLER Namespace
} // End of CLI     Namespace

