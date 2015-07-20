/**
 * @file    CommandParseStatus.hpp
 * @author  Marvin Smith
 * @date    5/19/2015
*/
#ifndef __CLI_CMD_CLI_COMMAND_PARSE_STATUS_HPP__
#define __CLI_CMD_CLI_COMMAND_PARSE_STATUS_HPP__

// C++ Standard Libraries
#include <cinttypes>
#include <string>
#include <tuple>
#include <vector>


namespace CLI{
namespace CMD{

/**
 * @enum CommandParseStatus
 */
enum class CommandParseStatus : uint8_t {
    UNKNOWN             = 0 /**< Unknown problem. Avoid this setting.*/,
    VALID               = 1 /**< Valid command with valid arguments.*/,
    NO_COMMAND_FOUND    = 2 /**< No command with a matching name found.*/,
    CLI_SHUTDOWN        = 3 /**< The user set the parser's expected shutdown command.*/,
    CLI_HELP            = 4 /**< The user requested help */,
    INVALID_ARGUMENTS   = 5 /**< Problem parsing arguments.*/,
    EXCESSIVE_ARGUMENTS = 6 /**< Too many arguments compared to matching command.*/,
    CLI_BACK            = 7 /**< Back command entered.*/,
    CLI_CLEAR           = 8 /**< Clear History Command Entered.*/,
    CLI_LOG             = 9 /**< Show the log information.*/,
    CLI_ALIAS_ADD       = 10 /**< Add an alias.*/,
    CLI_ALIAS_REMOVE    = 11 /**< Remove an alias.*/,
    CLI_ALIAS_LIST      = 12 /**< List all aliases.*/,
    CLI_RUN_SCRIPT      = 13 /**< Run a script on the CLI.*/,
    CLI_PAUSE           = 14 /**< Pause the CLI until user input provided.*/,
    CLI_SLEEP           = 15 /**< Sleep for a specified number of seconds.*/,
    CLI_RESIZE          = 16 /**< Resize the CLI Window.*/,
    CLI_VARIABLE_ADD    = 17 /**< Add a Variable to the Command-Parser.*/,
    CLI_VARIABLE_RM     = 18 /**< Remove a variable from the Command-Parser.*/,
    CLI_VARIABLE_SHOW   = 19 /**< Show the Command-Parser variable list.*/,
}; // End of CommandParseStatus Enumeration


/**
 * @brief Convert a CommandParseStatus to Color Code.
 *
 * @param[in] status Command parsing status to evaluate.
 *
 * @return Color code value.
 */
int CommandParseStatusToColorCode( const CommandParseStatus& status );

/**
 * @brief Convert a CommandParseStatus to String
 */
std::string CommandParseStatusToString( const CommandParseStatus& status );


/**
 * @brief Convert a CommandParseStatus to History Mode String
 */
std::string CommandParseStatusToHistoryString( const CommandParseStatus& status );


/**
 * @brief Convert a string to CommandParseStatus
 */
CommandParseStatus StringToCommandParseStatus( std::string const& status );


/**
 * @brief Check if CLI Command Status is a Valid CLI Command
 *
 * @param[in] command Command to test.
 *
 * @return True if a valid command, false otherwise.
*/
bool Is_Valid_CLI_Command( CommandParseStatus const& command );


/**
 * @brief Create a list which maps the CommandParseStatus items to their expected names.
 *
 * @return List of mappings between the CommandParseStatus and its name.
 */
std::vector<std::tuple<std::string,CommandParseStatus>> Get_CLI_Mode_To_Parse_Status_List();

} // End of CMD Namespace
} // End of CLI Namespace

#endif
