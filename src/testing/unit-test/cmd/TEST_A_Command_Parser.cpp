/**
 * @file    TEST_A_Command_Parser.cpp
 * @author  Marvin Smith
 * @date    6/8/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/cmd/A_Command_Parser.hpp>

using namespace CLI;

/*******************************************************/
/*        Test the A_Command_Parser Constructors       */
/*******************************************************/
TEST( A_Command_Parser, Constructors )
{
    // Create a Command
    CMD::A_Command command01( "hello", "Say hi", false );

    // CLI Command names
    std::vector<std::string> cli_cmd_names01;
    cli_cmd_names01.push_back("HELLO");
    cli_cmd_names01.push_back("Hello");


    // Alias List
    std::vector<CMD::A_Command_Alias> alias_list;


    // Create a CLI Command
    CMD::A_CLI_Command cli_command01( CMD::CommandParseStatus::CLI_HELP, 
                                      cli_cmd_names01,
                                      "Hello",
                                      "Yo.");

    // Create the parser
    std::vector<CMD::A_Command> commands;
    commands.push_back(command01);
    std::vector<CMD::A_CLI_Command> cli_commands;
    cli_commands.push_back(cli_command01);

    CMD::A_Command_Parser parser(" ", cli_commands, commands, alias_list, "", false);

    // Check the command list
    std::vector<CMD::A_Command> cmd_out = parser.Get_Command_List();
    ASSERT_EQ( cmd_out.size(), commands.size() );
    for( size_t i=0; i<commands.size(); i++ ){
        ASSERT_EQ( cmd_out[i].Get_Name(), commands[i].Get_Name() );
    }

}

/************************************************************/
/*        Test the A_Command_Parser Test Autocomplete       */
/************************************************************/
TEST( A_Command_Parser, Update_Autocomplete_String )
{
    // Create a Command
    CMD::A_Command command01( "hello", "Say hi", false );
    CMD::A_Command command02( "HellO", "Say hi", false );

    // CLI Command names
    std::vector<std::string> cli_cmd_names01;
    cli_cmd_names01.push_back("HELLO");
    cli_cmd_names01.push_back("Hello");

    
    // Alias List
    std::vector<CMD::A_Command_Alias> alias_list;


    // Create a CLI Command
    CMD::A_CLI_Command cli_command01( CMD::CommandParseStatus::CLI_HELP, 
                                      cli_cmd_names01,
                                      "Hello",
                                      "Yo.");

    // Create the parser
    std::vector<CMD::A_Command> commands;
    commands.push_back(command01);
    commands.push_back(command02);
    
    std::vector<CMD::A_CLI_Command> cli_commands;
    cli_commands.push_back(cli_command01);

    CMD::A_Command_Parser parser(" ", cli_commands, commands, alias_list, "", false);

    
    // Test the update
    std::vector<std::string> match_list;

    // Test 01
    parser.Update_Autocomplete_String( "H", match_list );
    ASSERT_EQ( (int)match_list.size(), 2 );
    ASSERT_EQ( match_list[0], "HellO");
    ASSERT_EQ( match_list[1], "HELLO");

}
