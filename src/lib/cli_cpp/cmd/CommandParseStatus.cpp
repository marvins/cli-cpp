/**
 * @file    CommandParseStatus.cpp
 * @author  Marvin Smith
 * @date    5/19/2015
*/
#include "CommandParseStatus.hpp"

namespace CLI{
namespace CMD{

/********************************************************/
/*      Convert CLI Command Parse Status to String      */
/********************************************************/
std::string CommandParseStatusToString( CommandParseStatus const& status )
{

    // Valid
    if( status == CommandParseStatus::VALID ){
        return "VALID";
    }

    // Valid Shutdown
    if( status == CommandParseStatus::CLI_SHUTDOWN ){
        return "CLI_SHUTDOWN";
    }

    // Valid help
    if( status == CommandParseStatus::CLI_HELP ){
        return "CLI_HELP";
    }

    // Back help
    if( status == CommandParseStatus::CLI_BACK ){
        return "CLI_BACK";
    }

    // Log
    if( status == CommandParseStatus::CLI_LOG ){
        return "CLI_LOG";
    }

    // Add Alias
    if( status == CommandParseStatus::CLI_ALIAS_ADD ){
        return "CLI_ALIAS_ADD";
    }

    // Remove Alias
    if( status == CommandParseStatus::CLI_ALIAS_REMOVE ){
        return "CLI_ALIAS_REMOVE";
    }

    // List Aliases
    if( status == CommandParseStatus::CLI_ALIAS_LIST ){
        return "CLI_ALIAS_LIST";
    }

    // Sleep
    if( status == CommandParseStatus::CLI_SLEEP ){
        return "CLI_SLEEP";
    }

    // Pause
    if( status == CommandParseStatus::CLI_PAUSE ){
        return "CLI_PAUSE";
    }

    // Invalid arguments
    if( status == CommandParseStatus::INVALID_ARGUMENTS ){
        return "INVALID_ARGUMENTS";
    }

    // Excessive Arguments
    if( status == CommandParseStatus::EXCESSIVE_ARGUMENTS ){
        return "EXCESSIVE_ARGUMENTS";
    }

    // No Command Found
    if( status == CommandParseStatus::NO_COMMAND_FOUND ){
        return "NO_COMMAND_FOUND";
    }
    
    // CLI Clear
    if( status == CommandParseStatus::CLI_CLEAR ){
        return "CLI_CLEAR";
    }

    // Run SCript
    if( status == CommandParseStatus::CLI_RUN_SCRIPT ){
        return "CLI_RUN_SCRIPT";
    }

    // Resize CLI
    if( status == CommandParseStatus::CLI_RESIZE ){
        return "CLI_RESIZE";
    }

    // Add Command Variable
    if( status == CommandParseStatus::CLI_VARIABLE_ADD ){
        return "CLI_VARIABLE_ADD";
    }

    // Remove Command Variable
    if( status == CommandParseStatus::CLI_VARIABLE_RM ){
        return "CLI_VARIABLE_RM";
    }

    // Show Command Variables
    if( status == CommandParseStatus::CLI_VARIABLE_SHOW ){
        return "CLI_VARIABLE_SHOW";
    }

    // Show Async Command History
    if( status == CommandParseStatus::CLI_ASYNC_SHOW ){
        return "CLI_ASYNC_SHOW";
    }

    // UNKNOWN
    return "UNKNOWN";
}


/********************************************************/
/*      Convert CLI Command Parse Status to String      */
/********************************************************/
std::string CommandParseStatusToHistoryString( CommandParseStatus const& status )
{

    // Valid
    if( status == CommandParseStatus::VALID ){
        return "Valid Command";
    }

    // Valid Shutdown
    if( status == CommandParseStatus::CLI_SHUTDOWN ){
        return "CLI Shutdown Command";
    }

    // Valid help
    if( status == CommandParseStatus::CLI_HELP ){
        return "Success";
    }

    // Back help
    if( status == CommandParseStatus::CLI_BACK ){
        return "Success";
    }

    // Clear
    if( status == CommandParseStatus::CLI_CLEAR ){
        return "Success";
    }

    // Log
    if( status == CommandParseStatus::CLI_LOG ){
        return "Success";
    }

    // Add Alias
    if( status == CommandParseStatus::CLI_ALIAS_ADD ){
        return "Success";
    }

    // Remove Alias
    if( status == CommandParseStatus::CLI_ALIAS_REMOVE ){
        return "Success";
    }

    // List Alias
    if( status == CommandParseStatus::CLI_ALIAS_LIST ){
        return "Success";
    }

    // CLI Resize
    if( status == CommandParseStatus::CLI_RESIZE ){
        return "Success";
    }
    
    // CLI Variable Add
    if( status == CommandParseStatus::CLI_VARIABLE_ADD ){
        return "Success";
    }

    // CLI Variable RM
    if( status == CommandParseStatus::CLI_VARIABLE_RM ){
        return "Success";
    }

    // CLI Variable Show
    if( status == CommandParseStatus::CLI_VARIABLE_SHOW ){
        return "Success";
    }

    // CLI Run Script
    if( status == CommandParseStatus::CLI_RUN_SCRIPT ){
        return "Starting Script";
    }

    // CLI Sleep
    if( status == CommandParseStatus::CLI_SLEEP ){
        return "Starting Sleep";
    }

    // CLI Pause
    if( status == CommandParseStatus::CLI_PAUSE ){
        return "Press any key to continue.";
    }

    // CLI Async Show
    if( status == CommandParseStatus::CLI_ASYNC_SHOW ){
        return "Success";
    }

    // Invalid arguments
    if( status == CommandParseStatus::INVALID_ARGUMENTS ){
        return "Invalid arguments";
    }

    // Excessive Arguments
    if( status == CommandParseStatus::EXCESSIVE_ARGUMENTS ){
        return "Too many arguments";
    }

    // No Command Found
    if( status == CommandParseStatus::NO_COMMAND_FOUND ){
        return "No command found.";
    }

    // UNKNOWN
    return "Unknown";
}

/********************************************************/
/*    Convert CLI Command Parse Status to Color Code    */
/********************************************************/
int CommandParseStatusToColorCode( CommandParseStatus const& status )
{

    // Case
    switch( status ){
        
        // Color 0 - Default
        case CommandParseStatus::VALID:
        case CommandParseStatus::CLI_SHUTDOWN:
        case CommandParseStatus::CLI_HELP:
        case CommandParseStatus::CLI_BACK:
        case CommandParseStatus::CLI_LOG:
        case CommandParseStatus::CLI_CLEAR:
        case CommandParseStatus::CLI_ALIAS_LIST:
        case CommandParseStatus::CLI_ALIAS_ADD:
        case CommandParseStatus::CLI_ALIAS_REMOVE:
        case CommandParseStatus::CLI_RUN_SCRIPT:
        case CommandParseStatus::CLI_SLEEP:
        case CommandParseStatus::CLI_PAUSE:
        case CommandParseStatus::CLI_VARIABLE_ADD:
        case CommandParseStatus::CLI_VARIABLE_RM:
        case CommandParseStatus::CLI_VARIABLE_SHOW:
        case CommandParseStatus::CLI_RESIZE:
        case CommandParseStatus::CLI_ASYNC_SHOW:
            return 0;

        // Color 0 - ERROR
        case CommandParseStatus::INVALID_ARGUMENTS:
        case CommandParseStatus::EXCESSIVE_ARGUMENTS:
        case CommandParseStatus::NO_COMMAND_FOUND:
        case CommandParseStatus::UNKNOWN:
            return 1;
    }

    // UNKNOWN
    return 0;
}



/********************************************************/
/*      Convert String to CLI Command Parse Status      */
/********************************************************/
CommandParseStatus StringToCommandParseStatus( const std::string& status )
{
    // Valid Status
    if( status == "VALID" ){
        return CommandParseStatus::VALID;
    }

    // Valid Shutdown
    if( status == "CLI_SHUTDOWN" ){
        return CommandParseStatus::CLI_SHUTDOWN;
    }    

    // Valid help
    if( status == "CLI_HELP" ){
        return CommandParseStatus::CLI_HELP;
    }

    // CLI Clear
    if( status == "CLI_CLEAR" ){
        return CommandParseStatus::CLI_CLEAR;
    }

    // CLI Log
    if( status == "CLI_LOG" ){
        return CommandParseStatus::CLI_LOG;
    }
    
    // Add Alias
    if( status == "CLI_ALIAS_ADD" ){
        return CommandParseStatus::CLI_ALIAS_ADD;
    }

    // Remove Alias
    if( status == "CLI_ALIAS_REMOVE" ){
        return CommandParseStatus::CLI_ALIAS_REMOVE;
    }

    // Alias List
    if( status == "CLI_ALIAS_LIST" ){
        return CommandParseStatus::CLI_ALIAS_LIST;
    }

    // CLI Run Script
    if( status == "CLI_RUN_SCRIPT" ){
        return CommandParseStatus::CLI_RUN_SCRIPT;
    }

    // CLI Sleep
    if( status == "CLI_SLEEP" ){
        return CommandParseStatus::CLI_SLEEP;
    }

    // CLI Pause
    if( status == "CLI_PAUSE" ){
        return CommandParseStatus::CLI_PAUSE;
    }

    // CLI Resize
    if( status == "CLI_RESIZE" ){
        return CommandParseStatus::CLI_RESIZE;
    }
    
    // CLI Variable Add
    if( status == "CLI_VARIABLE_ADD" ){
        return CommandParseStatus::CLI_VARIABLE_ADD;
    }
    
    // CLI Variable RM
    if( status == "CLI_VARIABLE_RM" ){
        return CommandParseStatus::CLI_VARIABLE_RM;
    }
    
    // CLI Variable Show
    if( status == "CLI_VARIABLE_SHOW" ){
        return CommandParseStatus::CLI_VARIABLE_SHOW;
    }

    // CLI Async History
    if( status == "CLI_ASYNC_SHOW" ){
        return CommandParseStatus::CLI_ASYNC_SHOW;
    }

    // Invalid ARguments
    if( status == "INVALID_ARGUMENTS" ){
        return CommandParseStatus::INVALID_ARGUMENTS;
    }

    // Excessive Arguments
    if( status == "EXCESSIVE_ARGUMENTS" ){
        return CommandParseStatus::EXCESSIVE_ARGUMENTS;
    }

    // No Command Found
    if( status == "NO_COMMAND_FOUND" ){
        return CommandParseStatus::NO_COMMAND_FOUND;
    }

    // Back Command
    if( status == "CLI_BACK" ){
        return CommandParseStatus::CLI_BACK;
    }

    // Unknown
    return CommandParseStatus::UNKNOWN;
}


/************************************************************/
/*      Check CLI Command Status if Valid CLI Command       */
/************************************************************/
bool Is_Valid_CLI_Command( CommandParseStatus const& command ){

    // Check if Valid
    switch( command ){
        
        // Valid Commands
        case CommandParseStatus::CLI_BACK:
        case CommandParseStatus::CLI_HELP:
        case CommandParseStatus::CLI_SHUTDOWN:
        case CommandParseStatus::CLI_CLEAR:
        case CommandParseStatus::CLI_LOG:
        case CommandParseStatus::CLI_ALIAS_ADD:
        case CommandParseStatus::CLI_ALIAS_REMOVE:
        case CommandParseStatus::CLI_ALIAS_LIST:
        case CommandParseStatus::CLI_RUN_SCRIPT:
        case CommandParseStatus::CLI_PAUSE:
        case CommandParseStatus::CLI_SLEEP:
        case CommandParseStatus::CLI_VARIABLE_ADD:
        case CommandParseStatus::CLI_VARIABLE_RM:
        case CommandParseStatus::CLI_VARIABLE_SHOW:
        case CommandParseStatus::CLI_ASYNC_SHOW:
            return true;
        
        case CommandParseStatus::VALID:
        case CommandParseStatus::NO_COMMAND_FOUND:
        case CommandParseStatus::EXCESSIVE_ARGUMENTS:
        case CommandParseStatus::INVALID_ARGUMENTS:
        case CommandParseStatus::UNKNOWN:
        case CommandParseStatus::CLI_RESIZE: ///<  This is done to allow CLI Resize Commands to be pushed to the handlers
            return false;
    }
    return false;
}


/****************************************************/
/*         Map Command Parse Status to String       */
/****************************************************/
std::vector<std::tuple<std::string,CommandParseStatus>> Get_CLI_Mode_To_Parse_Status_List()
{
    // Create output list
    std::vector<std::tuple<std::string,CommandParseStatus>> output;


    // Add each cli command
    output.push_back( std::make_tuple("shutdown",     CommandParseStatus::CLI_SHUTDOWN)     );
    output.push_back( std::make_tuple("back",         CommandParseStatus::CLI_BACK)         );
    output.push_back( std::make_tuple("clear",        CommandParseStatus::CLI_CLEAR)        );
    output.push_back( std::make_tuple("log",          CommandParseStatus::CLI_LOG)          );
    output.push_back( std::make_tuple("alias-add",    CommandParseStatus::CLI_ALIAS_ADD)    );
    output.push_back( std::make_tuple("alias-remove", CommandParseStatus::CLI_ALIAS_REMOVE) );
    output.push_back( std::make_tuple("alias-list",   CommandParseStatus::CLI_ALIAS_LIST)   );
    output.push_back( std::make_tuple("run-script",   CommandParseStatus::CLI_RUN_SCRIPT)   );
    output.push_back( std::make_tuple("pause",        CommandParseStatus::CLI_PAUSE)        );
    output.push_back( std::make_tuple("sleep",        CommandParseStatus::CLI_SLEEP)        );
    output.push_back( std::make_tuple("var-add",      CommandParseStatus::CLI_VARIABLE_ADD) );
    output.push_back( std::make_tuple("var-rm",       CommandParseStatus::CLI_VARIABLE_RM)  );
    output.push_back( std::make_tuple("var-show",     CommandParseStatus::CLI_VARIABLE_SHOW));
    output.push_back( std::make_tuple("async-show",   CommandParseStatus::CLI_ASYNC_SHOW)   );
    output.push_back( std::make_tuple("help",         CommandParseStatus::VALID)            ); ///<  CLI Help Commands should be treated like normal commands.
    output.push_back( std::make_tuple("cli-resize",   CommandParseStatus::VALID)            ); ///<  CLI Resize Commands should be treated like normal commands.

    // return output
    return output;
}


} // End of CMD Namespace
} // End of CLI Namespace

