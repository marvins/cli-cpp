/**
 * @file    Init_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/4/2015
*/
#include "Init_Utilities.hpp"

// App Libraries
#include "../cli/A_Netstat_Command_Response_Handler.hpp"
#include "../cli/A_Network_Asset_Command_Response_Handler.hpp"
#include "../cli/A_Ping_Command_Response_Handler.hpp"
#include "../cli/A_System_Command_Response_Handler.hpp"
#include "../render/A_Network_Status_Render_Window.hpp"


/***************************************************/
/*       Register Command Response Handlers        */
/***************************************************/
void Register_Command_Response_Handlers( CLI::A_CLI_Manager::ptr_t  cli_manager,
                                         State_Manager&             state_manager )
{

    // Register a Ping Command-Response Handler
    A_Ping_Command_Response_Handler::ptr_t  ping_handler = std::make_shared<A_Ping_Command_Response_Handler>();
    cli_manager->Register_Command_Response_Handler( ping_handler );

    // Register a Netstat Command-Response Handler
    A_Netstat_Command_Response_Handler::ptr_t netstat_handler = std::make_shared<A_Netstat_Command_Response_Handler>();
    cli_manager->Register_Command_Response_Handler( netstat_handler );

    // Register a System Response Handler
    A_System_Command_Response_Handler::ptr_t system_handler = std::make_shared<A_System_Command_Response_Handler>(state_manager);
    cli_manager->Register_Command_Response_Handler( system_handler );
    
    // Register a Network Asset Response Handler
    Network_Scanner::ptr_t network_scanner = state_manager.Get_Network_Scanner();
    A_Network_Asset_Command_Response_Handler::ptr_t network_handler = std::make_shared<A_Network_Asset_Command_Response_Handler>(network_scanner);
    cli_manager->Register_Command_Response_Handler(network_handler);

}


/*************************************/
/*      Register Render Windows      */
/*************************************/
bool Register_Render_Windows( CLI::A_CLI_Manager::ptr_t   cli_manager,
                              State_Manager&              state_manager )
{
    // Create a render window
    A_Network_Status_Render_Window::ptr_t render_window = std::make_shared<A_Network_Status_Render_Window>( state_manager );
    
    // Create the accompanying command to trigger the window
    CLI::CMD::A_Command trigger_command( "network-status",
                                         "Print the network status window.",
                                         false );

    // Register the render window
    return cli_manager->Register_Custom_Render_Window( render_window, trigger_command );
}


