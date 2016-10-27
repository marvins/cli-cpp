/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    10/26/2016
*/

// C++ Libraries
#include <iostream>
#include <string>

// Project Libraries
#include "core/State_Manager.hpp"
#include "utils/Init_Utilities.hpp"

// CLI Libraries
#include <cli_cpp/cli/A_CLI_Manager_Factory.hpp>


using namespace std;


/**
 * @brief Main Function
*/
int main( int argc, char* argv[] )
{

    try
    {

        // Parse the Command-Line Options
        std::string config_pathname = argv[1];
        bool response = false;

        
        // Create a State Manager
        State_Manager state_manager;


        // Create a CLI-Manager
        CLI::A_CLI_Manager::ptr_t cli_manager = CLI::A_CLI_Manager_Factory::Initialize( config_pathname );
    
    
        // Make sure the cli-manager is not null
        if( cli_manager == nullptr )
        {
            std::cerr << "error: CLI-Manager Factory returned null instance." << std::endl;
            return 1;
        }

        // Register the Command-Response Handlers
        Register_Command_Response_Handlers( cli_manager,
                                            state_manager );

        
        // Initialize the CLI Manager
        cli_manager->Connect();


        // Register the Custom Windows
        response = Register_Render_Windows( cli_manager,
                                            state_manager );

        if( !response )
        {
            std::cerr << "CLI-Manager unable to register custom window." << std::endl;
            std::exit(-1);
        }

        
        
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



    return 0;
}

