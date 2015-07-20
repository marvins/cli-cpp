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
#include "core/State_Manager.hpp"
#include "cli/A_System_Command_Response_Handler.hpp"
#include "utils/Init_Utilities.hpp"


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
        CLI::A_CLI_Manager::ptr_t cli_manager = CLI::A_CLI_Manager_Factory::Initialize( config_pathname );

        // Make sure it is not null
        if( cli_manager == nullptr ){
            std::cerr << "Error: Returned null." << std::endl;
            return 1;
        }

        // Register the Command-Response Handlers
        Register_Command_Response_Handlers( cli_manager,
                                            state_manager );


        // Register the Custom Windows
        Register_Render_Windows( cli_manager,
                                 state_manager );

        
        // Initialize the CLI Manager
        cli_manager->Connect();
        
        // Wait for the system to be commanded to shut down.
        state_manager.Wait_On_System_Shutdown();


        // Disconnect the CLI Manager
        cli_manager->Disconnect();

        
        // Destroy the CLI Manager
        cli_manager.reset();


    } catch ( exception& e ){
        std::cerr << "exception caught What: " << e.what() << std::endl;
    } catch (...){
        std::cerr << "unknown exception detected." << std::endl;
    }


    // Exit Program
    return 0;
}

