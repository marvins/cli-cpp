/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 *
 * @brief Simple demo showing how to use and expand on the CLI-CPP library.
 */

// C++ Standard Libraries
#include <iostream>
#include <signal.h>
#include <string>
#include <unistd.h>

// Demo Libraries
#include "cli/A_Netstat_Command_Response_Handler.hpp"
#include "cli/A_Ping_Command_Response_Handler.hpp"
#include "cli/A_System_Command_Response_Handler.hpp"
#include "core/State_Manager.hpp"

// CLI Libraries
#include <cli_cpp/cli/A_CLI_Manager_Factory.hpp>
#include <cli_cpp/utility/System_Utilities.hpp>

using namespace std;


/**
 * @brief Main Program
 */
int main( int argc, char* argv[] )
{

    try{
    
        // Check args
        if( argc < 2 ){
            std::cerr << "usage: " << argv[0] << " <config-path>" << std::endl;
            return 1;
        }

        // Define the configuration file path
        std::string config_pathname = argv[1];

        // Create a State Manager
        State_Manager state_manager;

        // Create the CLI Manager
        CLI::A_CLI_Manager::ptr_t manager = CLI::A_CLI_Manager_Factory::Initialize( config_pathname );

        // Make sure it is not null
        if( manager == nullptr ){
            std::cerr << "Error: Returned null." << std::endl;
            return 1;
        }

        // Register a Ping Command-Response Handler
        A_Ping_Command_Response_Handler::ptr_t  ping_handler = std::make_shared<A_Ping_Command_Response_Handler>();
        manager->Register_Command_Response_Handler( ping_handler );

        // Register a Netstat Command-Response Handler
        A_Netstat_Command_Response_Handler::ptr_t netstat_handler = std::make_shared<A_Netstat_Command_Response_Handler>();
        manager->Register_Command_Response_Handler( netstat_handler );

        // Register a System Response Handler
        A_System_Command_Response_Handler::ptr_t system_handler = std::make_shared<A_System_Command_Response_Handler>(state_manager);
        manager->Register_Command_Response_Handler( system_handler );

        // Initialize the CLI Manager
        manager->Connect();

        // Check the type of run and wait if necessary
        state_manager.Wait_On_System_Shutdown();

        // Disconnect the CLI Manager
        manager->Disconnect();

    } catch ( exception& e ){
        std::cerr << "exception caught What: " << e.what() << std::endl;
    } catch (...){
        std::cerr << "unknown exception detected." << std::endl;
    }


    // Exit Program
    return 0;
}

