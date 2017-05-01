/**
 * @file    Command_Parser.cpp
 * @author  Marvin Smith
 * @date    7/11/2015
*/
#include "Command_Parser.hpp"

// C++ Standard Libraries
#include <deque>
#include <string>

// CLI Libraries
#include <cli_cpp/utility/Log_Utilities.hpp>


/*********************************************/
/*      Process Command-Line Arguments       */
/*********************************************/
void Process_Command_Line( int argc, char* argv[] )
{
    // Get the app name
    std::string app_name = argv[0];


    // Check the arg list
    std::deque<std::string> args;
    for( int i=1; i<argc; i++ ){
        args.push_back(argv[i]);
    }

    // Default log level
    std::string log_level = "info";

    // Parse arguments
    while( args.size() > 0 ){
        
        // Get the next argument
        std::string arg = args[0];
        args.pop_front();

        // Check if help
        if( arg == "-h" || arg == "--help" ){
            Usage( app_name );
        }

        // Check if verbose
        else if( arg == "-v" ){
            log_level = "debug";
        }

        // Check if trace
        else if( arg == "--v" ){
            log_level = "trace";
        }

    }
            
    // Init Logger        
    CLI::UTILS::Initialize_Logger( log_level, "", false);

}


/**************************************/
/*      Print Usage Instructions      */
/**************************************/
void Usage( const std::string& application_name )
{
    // Print
    std::cout << "usage: " << application_name << " [options]" << std::endl;
    std::cout << std::endl;

    // Print log options
    std::cout << "  Log Options:  (default : INFO) " << std::endl;
    std::cout << "  -v  : Print with debug output." << std::endl;
    std::cout << "  -vv : Print with trace output." << std::endl;
    std::cout << std::endl;

    std::exit(0);

}

