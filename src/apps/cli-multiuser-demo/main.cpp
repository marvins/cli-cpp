/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    10/26/2016
*/

// C++ Libraries
#include <iostream>

// CLI Libraries
#include <cli_cpp/cli/A_CLI_Manager_Factory.hpp>


using namespace std;


/**
 * @brief Main Function
*/
int main( int argc, char* argv[] )
{

    // Parse the Command-Line Options



    // Create a CLI-Manager
    CLI::A_CLI_Manager::ptr_t cli_manager = CLI::A_CLI_Manager_Factory::Initialize( config_pathname );


    return 0;
}

