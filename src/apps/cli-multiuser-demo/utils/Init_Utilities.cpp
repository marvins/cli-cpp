/**
 * @file    Init_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/4/2015
*/
#include "Init_Utilities.hpp"

// App Libraries
#include "../handlers/A_System_Command_Response_Handler.hpp"
#include "../handlers/A_User_Session_Event_Handler.hpp"
#include "../render/A_User_Status_Render_Window.hpp"


/***************************************************/
/*       Register Command Response Handlers        */
/***************************************************/
void Register_Command_Response_Handlers( CLI::A_CLI_Manager::ptr_t  cli_manager,
                                         State_Manager&             state_manager )
{
    // Register a System Response Handler
    A_System_Command_Response_Handler::ptr_t system_handler = std::make_shared<A_System_Command_Response_Handler>(state_manager);
    cli_manager->Register_Command_Response_Handler( system_handler );
}


/************************************************/
/*      Register Session Response Handlers      */
/************************************************/
void Register_Session_Response_Handlers( CLI::A_CLI_Manager::ptr_t cli_manager,
                                         State_Manager&            state_manager )
{



}


/*************************************/
/*      Register Render Windows      */
/*************************************/
bool Register_Render_Windows( CLI::A_CLI_Manager::ptr_t   cli_manager,
                              State_Manager&              state_manager )
{
    // Create a render window
    A_User_Status_Render_Window::ptr_t render_window = std::make_shared<A_User_Status_Render_Window>( state_manager );
    
    // Create the accompanying command to trigger the window
    CLI::CMD::A_Command trigger_command( "user-status",
                                         "Print the user status window.",
                                         false );

    // Register the render window
    return cli_manager->Register_Custom_Render_Window( render_window, trigger_command );
}


