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

    // Valid
    if( status == CommandParseStatus::VALID ){
        return 0;
    }

    // Valid Shutdown
    if( status == CommandParseStatus::CLI_SHUTDOWN ){
        return 0;
    }

    // Valid help
    if( status == CommandParseStatus::CLI_HELP ){
        return 0;
    }

    // Back help
    if( status == CommandParseStatus::CLI_BACK ){
        return 0;
    }

    // Invalid arguments
    if( status == CommandParseStatus::INVALID_ARGUMENTS ){
        return 1;
    }

    // Excessive Arguments
    if( status == CommandParseStatus::EXCESSIVE_ARGUMENTS ){
        return 1;
    }

    // No Command Found
    if( status == CommandParseStatus::NO_COMMAND_FOUND ){
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
            return true;
        
        case CommandParseStatus::VALID:
        case CommandParseStatus::NO_COMMAND_FOUND:
            return false;
    }
    return false;
}

} // End of CMD Namespace
} // End of CLI Namespace

