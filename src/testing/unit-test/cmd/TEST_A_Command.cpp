/**
 * @file    TEST_A_Command.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/cmd/A_Command.hpp>

using namespace CLI;

/************************************************/
/*        Test the A_Command Constructors       */
/************************************************/
TEST( A_Command, Default_Constructor )
{
    // Use the Default Constructor
    CMD::A_Command command01;

    // Test the Getters
    ASSERT_EQ( command01.Get_Name(), "");
    ASSERT_EQ( command01.Get_Description(), "");
    ASSERT_EQ( command01.Response_Expected(), false );
    ASSERT_EQ( (int)command01.Get_Argument_List().size(), 0);
    
    // Test the Check Argument
    ASSERT_FALSE( command01.Check_Argument_Type(-1, "hello") );
    ASSERT_FALSE( command01.Check_Argument_Type(0, "there") );
    ASSERT_FALSE( command01.Check_Argument_Type(0, "") );
    ASSERT_FALSE( command01.Check_Argument_Type(1, "world") );

    // Test the name match
    ASSERT_TRUE( command01.Is_Name_Match("") );
    ASSERT_FALSE( command01.Is_Name_Match("arg") );

}

/*******************************************************/
/*        Test the Parameterized Constructors          */
/*******************************************************/
TEST( A_Command, Parameterized_Constructor_No_Arguments )
{
    // Define the expected values
    const std::string command_name = "pingSystem";
    const std::string command_desc = "test_ping";
    const bool response_expected = true;

    // Use the Constructor
    CMD::A_Command command01( command_name,
                              command_desc,
                              response_expected );

    // Test the Getters
    ASSERT_EQ( command01.Get_Name(), command_name);
    ASSERT_EQ( command01.Get_Description(), command_desc);
    ASSERT_EQ( command01.Response_Expected(), response_expected );
    ASSERT_EQ( (int)command01.Get_Argument_List().size(), 0);
    
    // Test the Check Argument
    ASSERT_FALSE( command01.Check_Argument_Type(-1, "hello") );
    ASSERT_FALSE( command01.Check_Argument_Type(0, "there") );
    ASSERT_FALSE( command01.Check_Argument_Type(0, "") );
    ASSERT_FALSE( command01.Check_Argument_Type(1, "world") );

    // Test the name match
    ASSERT_TRUE( command01.Is_Name_Match( command_name ) );
    ASSERT_FALSE(command01.Is_Name_Match( "hello" ));
    ASSERT_FALSE(command01.Is_Name_Match( "" ));

}

/*******************************************************/
/*        Test the Parameterized Constructors          */
/*******************************************************/
TEST( A_Command, Parameterized_Constructor_With_Arguments )
{
    
    // Define the expected values
    const std::string command_name = "pingSystem";
    const std::string command_desc = "test_ping";
    const bool response_expected = false;
    std::vector<CMD::A_Command_Argument> command_arguments;

    // Create the command arguments
    command_arguments.push_back( CMD::A_Command_Argument("system_name",
                                                         CMD::CommandArgumentType::STRING,
                                                         "Hostname of system",
                                                         true,
                                                         "localhost"));
    command_arguments.push_back( CMD::A_Command_Argument("max-attempts",
                                                         CMD::CommandArgumentType::INTEGER,
                                                         "max number of tries.",
                                                         false,
                                                         "2"));

    // Use the Constructor
    CMD::A_Command command01( command_name,
                              command_desc,
                              response_expected,
                              command_arguments );

    // Test the Getters
    ASSERT_EQ( command01.Get_Name(), command_name);
    ASSERT_EQ( command01.Get_Description(), command_desc);
    ASSERT_EQ( command01.Response_Expected(), response_expected );
    ASSERT_EQ( (int)command01.Get_Argument_List().size(), 2);
    
    ASSERT_EQ( command01.Get_Command_Argument(0), command_arguments[0] );
    ASSERT_EQ( command01.Get_Command_Argument(1), command_arguments[1] );
    ASSERT_EQ( command01.Get_Argument_List()[0], command_arguments[0] );
    ASSERT_EQ( command01.Get_Argument_List()[1], command_arguments[1] );

    // Test the Check Argument against out-of-bound indices
    ASSERT_FALSE( command01.Check_Argument_Type(-1, "hello") );
    ASSERT_FALSE( command01.Check_Argument_Type(2, "0") );
    ASSERT_FALSE( command01.Check_Argument_Type(2, "localhost") );

    // Check STRING type for valid argument (All should pass).
    ASSERT_TRUE( command01.Check_Argument_Type(0, "localhost") );
    ASSERT_TRUE(  command01.Check_Argument_Type(0, "system_name") );
    ASSERT_TRUE( command01.Check_Argument_Type(0, "") );

    // Check INTEGER type for valid argument (Non-Ints should fail).
    ASSERT_FALSE( command01.Check_Argument_Type(1, "world") );
    ASSERT_FALSE( command01.Check_Argument_Type(1, "max-attempts") );
    ASSERT_TRUE(  command01.Check_Argument_Type(1, "1") );
    ASSERT_TRUE(  command01.Check_Argument_Type(1, "2.2") );
    ASSERT_TRUE(  command01.Check_Argument_Type(1, "-3.4") );

    // Test the name match
    ASSERT_TRUE( command01.Is_Name_Match( command_name ) );
    ASSERT_FALSE(command01.Is_Name_Match( "hello" ));
    ASSERT_FALSE(command01.Is_Name_Match( "" ));

}


/*******************************************/
/*       Test the Is Name Substring        */
/*******************************************/
TEST( A_Command, Is_Name_Substring ){

    // Define the expected values
    const std::string command_name = "pingSystem";
    const std::string command_desc = "test_ping";
    const bool response_expected = false;
    std::vector<CMD::A_Command_Argument> command_arguments;

    // Create the command arguments
    command_arguments.push_back( CMD::A_Command_Argument("system_name",
                                                         CMD::CommandArgumentType::STRING,
                                                         "Hostname of system",
                                                         true,
                                                         "localhost"));
    command_arguments.push_back( CMD::A_Command_Argument("max-attempts",
                                                         CMD::CommandArgumentType::INTEGER,
                                                         "max number of tries.",
                                                         false,
                                                         "2"));

    // Use the Constructor
    CMD::A_Command command01( command_name,
                              command_desc,
                              response_expected,
                              command_arguments );

    // Check the substring match
    ASSERT_TRUE( command01.Is_Name_Substring( "p" ) );
    ASSERT_TRUE( command01.Is_Name_Substring( "ping" ) );
    ASSERT_FALSE( command01.Is_Name_Substring( "Ping" ) );


}


