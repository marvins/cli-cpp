/**
 * @file    TEST_A_CLI_Command.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/cmd/A_CLI_Command.hpp>

using namespace CLI;

/************************************************/
/*        Test the A_CLI_Command Constructors   */
/************************************************/
TEST( A_CLI_Command, Parameterized_Constructor_Mode )
{
    // Use the Default Constructor
    CMD::A_CLI_Command command01( CMD::CommandParseStatus::VALID );
    CMD::A_CLI_Command command02( CMD::CommandParseStatus::UNKNOWN );
    CMD::A_CLI_Command command03( CMD::CommandParseStatus::INVALID_ARGUMENTS );
    CMD::A_CLI_Command command04( CMD::CommandParseStatus::INVALID_ARGUMENTS );
    
    // Test the Getters
    ASSERT_EQ( command01.Get_Formal_Name(), "");
    ASSERT_EQ( command02.Get_Formal_Name(), "");
    ASSERT_EQ( command03.Get_Formal_Name(), "");
    ASSERT_EQ( command04.Get_Formal_Name(), "");

    ASSERT_EQ( command01.Get_Description(), "");
    ASSERT_EQ( command02.Get_Description(), "");
    ASSERT_EQ( command03.Get_Description(), "");
    ASSERT_EQ( command04.Get_Description(), "");
    
    ASSERT_EQ( (int)command01.Get_Command_Name_List().size(), 0);
    ASSERT_EQ( (int)command02.Get_Command_Name_List().size(), 0);
    ASSERT_EQ( (int)command03.Get_Command_Name_List().size(), 0);
    ASSERT_EQ( (int)command04.Get_Command_Name_List().size(), 0);

    // Check the name list
    command01.Add_Name("Hello");
    ASSERT_EQ( (int)command01.Get_Command_Name_List().size(), 1);
    ASSERT_EQ( command01.Get_Command_Name_List()[0], "Hello");

    // Test == Operators
    ASSERT_TRUE(  command01 == command01 ); 
    ASSERT_FALSE( command01 == command02 ); 
    ASSERT_FALSE( command01 == command03 ); 
    ASSERT_FALSE( command01 == command04 ); 

    ASSERT_FALSE( command02 == command01 ); 
    ASSERT_TRUE(  command02 == command02 ); 
    ASSERT_FALSE( command02 == command03 ); 
    ASSERT_FALSE( command02 == command04 ); 
    
    ASSERT_FALSE( command03 == command01 ); 
    ASSERT_FALSE( command03 == command02 ); 
    ASSERT_TRUE(  command03 == command03 ); 
    ASSERT_TRUE(  command03 == command04 ); 
    
    ASSERT_FALSE( command04 == command01 ); 
    ASSERT_FALSE( command04 == command02 ); 
    ASSERT_TRUE(  command04 == command03 ); 
    ASSERT_TRUE(  command04 == command04 ); 
    

}

/*******************************************************/
/*        Test the Parameterized Constructors          */
/*******************************************************/
TEST( A_CLI_Command, Parameterized_Constructor_Full )
{
    // Define our modes
    const CMD::CommandParseStatus mode01 = CMD::CommandParseStatus::VALID;
    const CMD::CommandParseStatus mode02 = CMD::CommandParseStatus::VALID;
    const CMD::CommandParseStatus mode03 = CMD::CommandParseStatus::VALID;
    const CMD::CommandParseStatus mode04 = CMD::CommandParseStatus::INVALID_ARGUMENTS;


    // Define our name list
    std::vector<std::string> names01, names02, names03, names04;
    names01.push_back("hello"); 
    names02.push_back("hello"); 
    names03.push_back("Hello"); 
    names04.push_back("Hello");

    
    // Define our formal names
    const std::string formal_name01 = "Help";
    const std::string formal_name02 = "Help";
    const std::string formal_name03 = "Help";
    const std::string formal_name04 = "Help!";


    // Define the descriptions
    const std::string description01 = "1234";
    const std::string description02 = "12345";
    const std::string description03 = "123456";
    const std::string description04 = "1234567";


    // Create the CLI Commands
    CMD::A_CLI_Command cli_command01( mode01,
                                      names01,
                                      formal_name01,
                                      description01 );

    CMD::A_CLI_Command cli_command02( mode02,
                                      names02,
                                      formal_name02,
                                      description02 );

    CMD::A_CLI_Command cli_command03( mode03,
                                      names03,
                                      formal_name03,
                                      description03 );
    
    CMD::A_CLI_Command cli_command04( mode04,
                                      names04,
                                      formal_name04,
                                      description04 );


    // Add the name
    cli_command04.Add_Name("test");

    // Check Assignment Operators
    ASSERT_TRUE(  cli_command01 == cli_command01 );
    ASSERT_TRUE(  cli_command01 == cli_command02 );
    ASSERT_FALSE( cli_command01 == cli_command03 );
    ASSERT_FALSE( cli_command01 == cli_command04 );
    
    ASSERT_TRUE(  cli_command02 == cli_command01 );
    ASSERT_TRUE(  cli_command02 == cli_command02 );
    ASSERT_FALSE( cli_command02 == cli_command03 );
    ASSERT_FALSE( cli_command02 == cli_command04 );
    
    ASSERT_FALSE( cli_command03 == cli_command01 );
    ASSERT_FALSE( cli_command03 == cli_command02 );
    ASSERT_TRUE(  cli_command03 == cli_command03 );
    ASSERT_FALSE( cli_command03 == cli_command04 );
    
    ASSERT_FALSE( cli_command04 == cli_command01 );
    ASSERT_FALSE( cli_command04 == cli_command02 );
    ASSERT_FALSE( cli_command04 == cli_command03 );
    ASSERT_TRUE(  cli_command04 == cli_command04 );
    
    // Check the mode
    ASSERT_EQ( cli_command01.Get_Mode(), mode01 );
    ASSERT_EQ( cli_command02.Get_Mode(), mode02 );
    ASSERT_EQ( cli_command03.Get_Mode(), mode03 );
    ASSERT_EQ( cli_command04.Get_Mode(), mode04 );

    // Check the formal name
    ASSERT_EQ( cli_command01.Get_Formal_Name(), formal_name01 );
    ASSERT_EQ( cli_command02.Get_Formal_Name(), formal_name02 );
    ASSERT_EQ( cli_command03.Get_Formal_Name(), formal_name03 );
    ASSERT_EQ( cli_command04.Get_Formal_Name(), formal_name04 );

    // Check the description
    ASSERT_EQ( cli_command01.Get_Description(), description01 );
    ASSERT_EQ( cli_command02.Get_Description(), description02 );
    ASSERT_EQ( cli_command03.Get_Description(), description03 );
    ASSERT_EQ( cli_command04.Get_Description(), description04 );

    // Check the command list
    ASSERT_EQ( (int)cli_command01.Get_Command_Name_List().size(), 1 );
    ASSERT_EQ( (int)cli_command02.Get_Command_Name_List().size(), 1 );
    ASSERT_EQ( (int)cli_command03.Get_Command_Name_List().size(), 1 );
    ASSERT_EQ( (int)cli_command04.Get_Command_Name_List().size(), 2 );

    // Check the command list values
    ASSERT_EQ( cli_command01.Get_Command_Name_List()[0], "hello");
    ASSERT_EQ( cli_command02.Get_Command_Name_List()[0], "hello");
    ASSERT_EQ( cli_command03.Get_Command_Name_List()[0], "Hello");
    ASSERT_EQ( cli_command04.Get_Command_Name_List()[0], "Hello");
    ASSERT_EQ( cli_command04.Get_Command_Name_List()[1], "test" );

    // Test the IsName Substr function
    std::string act_match_result;
    
    // Since two entries will start with H, just H should come back
    cli_command04.Add_Name("HELLO");
    ASSERT_TRUE( cli_command04.Is_Name_Substring("H", act_match_result) );
    ASSERT_EQ( act_match_result, "H");

    // Since only HELLO has HE, the whole thing should work.
    ASSERT_TRUE( cli_command04.Is_Name_Substring("HE", act_match_result) );
    ASSERT_EQ( act_match_result, "HELLO");

}

