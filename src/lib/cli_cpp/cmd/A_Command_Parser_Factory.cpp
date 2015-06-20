/**
 * @file    A_Command_Parser_Factory.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#include "A_Command_Parser_Factory.hpp"

// C++ Standard Libraries
#include <iostream>
#include <sstream>
#include <stdexcept>

// PUGI Xml
#include "../thirdparty/pugixml.hpp"

// CLI Libraries
#include "../utility/Log_Utilities.hpp"

namespace CLI{
namespace CMD{


/*******************************************************/
/*        Parse the Argument Autocomplete Node         */
/*******************************************************/
std::vector<std::string> Parse_Argument_Autocomplete( pugi::xml_node const& arg_auto_node )
{
    // check the node
    if( arg_auto_node == pugi::xml_node() ){
        return std::vector<std::string>();
    }

    // List of terms
    std::vector<std::string> output;

    // Get the internal nodes
    for( pugi::xml_node_iterator oit = arg_auto_node.begin(); oit != arg_auto_node.end(); oit++ )
    {
        // Check the name
        if( std::string(oit->name()) != "option" ){
            continue;
        }

        // Get the node
        pugi::xml_node option_node = (*oit);

        // Get the value
        std::string value = option_node.attribute("value").as_string();

        if( value.size() > 0 ){
            output.push_back(value);
        }

    }

    // return the list
    return output;

}


/*******************************************/
/*        Parse the CLI Commands           */
/*******************************************/
std::vector<A_CLI_Command> Parse_CLI_Commands( pugi::xml_node& cli_cmd_node )
{
    // Create list
    std::vector<A_CLI_Command> cli_list;
    
    // Iterate over each command
    CMD::A_CLI_Command cli_command( CMD::CommandParseStatus::UNKNOWN );
    for( pugi::xml_node_iterator pit = cli_cmd_node.begin(); pit != cli_cmd_node.end(); pit++ )
    {

        // Get the node
        pugi::xml_node cli_node = (*pit);

        // Get the mode
        std::string mode_str = cli_node.attribute("mode").as_string();

        // set the mode
        if( mode_str == "shutdown" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_SHUTDOWN );
            cli_command.Set_Formal_Name("Shutdown");
        }
        else if( mode_str == "help" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_HELP );
            cli_command.Set_Formal_Name("Help");
        }
        else if( mode_str == "back" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_BACK );
            cli_command.Set_Formal_Name("Back");
        }
        else if( mode_str == "clear" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_CLEAR );
            cli_command.Set_Formal_Name("Clear");
        }
        else if( mode_str == "log" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_LOG );
            cli_command.Set_Formal_Name("Log");
        }
        else if( mode_str == "alias-add" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_ALIAS_ADD );
            cli_command.Set_Formal_Name("Add Alias");
        }
        else if( mode_str == "alias-remove" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_ALIAS_REMOVE );
            cli_command.Set_Formal_Name("Remove Alias");
        } 
        else if( mode_str == "alias-list" ){
            cli_command = CMD::A_CLI_Command( CMD::CommandParseStatus::CLI_ALIAS_LIST );
            cli_command.Set_Formal_Name("List Aliases");
        }
        else{
            throw std::runtime_error("error: Unknown CLI command mode (" + mode_str + ")");
        }

        // Iterate over names
        for( pugi::xml_node_iterator ait = cli_node.begin(); ait != cli_node.end(); ait++ )
        {
            if( std::string((*ait).name()) == "name" ){
                cli_command.Add_Name( (*ait).attribute("value").as_string());
            }
            if( std::string((*ait).name()) == "description") {
                cli_command.Set_Description( (*ait).attribute("value").as_string());
            }
        }

        // Add CLI command
        cli_list.push_back(cli_command);

    }



    // Return list
    return cli_list;
}


/**************************************************/
/*          Parse the Standard Commands           */
/**************************************************/
std::vector<A_Command> Parse_Standard_Commands( pugi::xml_node& commands_node )
{
    // Output list
    std::vector<A_Command> command_list;

    // List of arguments
    std::vector<A_Command_Argument> argument_list;

    std::string arg_name, arg_description, arg_default_value;
    bool arg_required;
    CommandArgumentType arg_type;
    std::vector<std::string> arg_auto_complete;

    // Parse the Commands Node
    for( pugi::xml_node_iterator it = commands_node.begin(); it != commands_node.end(); it++ )
    {

        // Clear the argument list
        argument_list.clear();

        // Convert to node
        pugi::xml_node command_node = (*it);

        // Get the command name
        std::string command_name  = command_node.child("name").attribute("value").as_string();

        // Get the command description
        std::string command_description = command_node.child("description").attribute("value").as_string();

        // Check the required response
        bool command_response = command_node.child("expect_response").attribute("value").as_bool(false);

        // Get the arguments node
        pugi::xml_node arguments_node = command_node.child("arguments");
        for( pugi::xml_node_iterator ait = arguments_node.begin(); ait != arguments_node.end(); ait++ )
        {
            // Get the node
            pugi::xml_node arg_node = (*ait);

            // Get the name
            arg_name = arg_node.attribute("name").as_string();

            // Get the description
            arg_description = arg_node.attribute("description").as_string();

            // Get the type
            arg_type = StringToCommandArgumentType(arg_node.attribute("type").as_string());

            // Get the required flag
            arg_required = arg_node.attribute("required").as_bool(true);

            // Get the default flag
            arg_default_value = arg_node.attribute("default").as_string("");

            // Get any auto-complete terms
            arg_auto_complete = Parse_Argument_Autocomplete( arg_node.child("auto-complete") );


            // Add the next argument
            argument_list.push_back( A_Command_Argument( arg_name,
                                                         arg_type,
                                                         arg_description,
                                                         arg_required,
                                                         arg_default_value,
                                                         arg_auto_complete ));

        }

        // Add the command
        command_list.push_back(A_Command( command_name, command_description, command_response, argument_list ));

    }

    // return the command list
    return command_list;
}


/*********************************************/
/*          Create a Command Parser          */
/*********************************************/
A_Command_Parser::ptr_t  A_Command_Parser_Factory::Initialize( const std::string& config_path,
                                                               const bool&        alias_support,
                                                               const std::string& alias_path )
{
    // Create XML Document
    pugi::xml_document xmldoc;
    pugi::xml_parse_result result = xmldoc.load_file( config_path.c_str() );

    if( result == false ){
        std::stringstream sin;
        sin << "error: " << __FILE__ << ", Line: " << __LINE__ << ". CLI Command Configuration File parsed with errors. Details: " << result.description();
        BOOST_LOG_TRIVIAL(error) << sin.str();
        return nullptr;
    }

    // Lists
    std::vector<A_CLI_Command> cli_command_list;
    std::vector<A_Command> command_list;
    std::string regex_split_pattern;

    // Catch any exceptions
    try{

        // Get the root node
        pugi::xml_node root_node = xmldoc.child("command-configuration");

        // Check the node
        if( root_node == pugi::xml_node() ){ return nullptr; }


        // Get the regex split pattern
        regex_split_pattern = root_node.child("regex-split-pattern").attribute("value").as_string();


        // Get the Parser Command Nodes
        pugi::xml_node cli_commands_node = root_node.child("cli-commands");
        cli_command_list = Parse_CLI_Commands( cli_commands_node );


        // Get the Commands Node
        pugi::xml_node commands_node = root_node.child("commands");
        command_list = Parse_Standard_Commands( commands_node );

        // Command List
        std::vector<A_Command_Argument> argument_list;


        // Make sure the command lists have values
        if( cli_command_list.size() <= 0 ){
            throw std::runtime_error("CLI Command-List is currently empty.");
        }

        if( command_list.size() <= 0 ){
            throw std::runtime_error("Command-list is currently empty.");
        }


    } catch ( std::exception& e ) {
        BOOST_LOG_TRIVIAL(error) << "Exception caught in CLI Parser Factory. Details: " << e.what();
        return nullptr;
    }


    // If alias support is enabled, load the alias list path
    std::vector<A_Command_Alias> alias_list;
    if( alias_support == true ){
       alias_list = A_Command_Alias::Load_Alias_Configuration_File( alias_path );
    }

    // Create the parser
    A_Command_Parser::ptr_t parser = std::make_shared<A_Command_Parser>( regex_split_pattern, 
            cli_command_list, 
            command_list,
            alias_list );

    // Return new parser
    return parser;
}



} // End of CMD Namespace
} // End of CLI Namespace

