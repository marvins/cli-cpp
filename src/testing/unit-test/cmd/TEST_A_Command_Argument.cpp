/**
 * @file    TEST_A_Command_Argument.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/cmd/A_Command_Argument.hpp>

using namespace CLI;

/******************************************************/
/*      Test the A_Command_Argument  Constructor      */
/******************************************************/
TEST( A_Command_Argument, Default_Constructor )
{
    // Create a Command Argument
    CMD::A_Command_Argument command_argument01;
    CMD::A_Command_Argument command_argument02;

    // Test the getters
    ASSERT_EQ( command_argument01.Get_Name(), "" );
    ASSERT_EQ( command_argument01.Get_Type(), CMD::CommandArgumentType::UNKNOWN );
    ASSERT_EQ( command_argument01.Get_Description(), "" );
    ASSERT_EQ( command_argument01.Get_Default_Value(), "" );

    // Test the type
    ASSERT_FALSE( command_argument01.Is_Valid_Type("") );
    ASSERT_FALSE( command_argument01.Is_Valid_Type("value") );
    ASSERT_FALSE( command_argument01.Is_Valid_Type("  ") );
    ASSERT_FALSE( command_argument01.Is_Valid_Type("1") );
    ASSERT_FALSE( command_argument01.Is_Valid_Type("-1.5") );
    
    // Test if required
    ASSERT_TRUE( command_argument01.Is_Required() );

    // Test the == operator
    ASSERT_TRUE( command_argument01 == command_argument02 );

}


/******************************************************/
/*      Test the A_Command_Argument  Constructor      */
/******************************************************/
TEST( A_Command_Argument, Parameterized_Constructor )
{
    // Set the values
    const std::string arg_name01 = "Port";
    const std::string arg_name02 = "Port";
    const std::string arg_name03;

    // Set the type2
    const CMD::CommandArgumentType arg_type01 = CMD::CommandArgumentType::INTEGER;
    const CMD::CommandArgumentType arg_type02 = CMD::CommandArgumentType::INTEGER;
    const CMD::CommandArgumentType arg_type03 = CMD::CommandArgumentType::STRING;

    // Set the description
    const std::string arg_description01 = "port value.";
    const std::string arg_description02 = "Port value";
    const std::string arg_description03 = "port";

    // Set the Required Value
    const bool arg_required01 = true;
    const bool arg_required02 = true;
    const bool arg_required03 = false;

    // Set the default value
    const std::string arg_default01 = "123";
    const std::string arg_default02 = "123";
    const std::string arg_default03 = "123.3";

    // Create Command Arguments
    CMD::A_Command_Argument command_argument01( arg_name01, 
                                                arg_type01, 
                                                arg_description01, 
                                                arg_required01, 
                                                arg_default01 );

    CMD::A_Command_Argument command_argument02( arg_name02, 
                                                arg_type02, 
                                                arg_description02, 
                                                arg_required02, 
                                                arg_default02 );
    
    CMD::A_Command_Argument command_argument03( arg_name03, 
                                                arg_type03, 
                                                arg_description03, 
                                                arg_required03, 
                                                arg_default03 );

    // Test the getters
    ASSERT_EQ( command_argument01.Get_Name(), arg_name01 );
    ASSERT_EQ( command_argument02.Get_Name(), arg_name02 );
    ASSERT_EQ( command_argument03.Get_Name(), arg_name03 );

    ASSERT_EQ( command_argument01.Get_Type(), arg_type01 );
    ASSERT_EQ( command_argument02.Get_Type(), arg_type02 );
    ASSERT_EQ( command_argument03.Get_Type(), arg_type03 );
    
    ASSERT_EQ( command_argument01.Get_Description(), arg_description01 );
    ASSERT_EQ( command_argument02.Get_Description(), arg_description02 );
    ASSERT_EQ( command_argument03.Get_Description(), arg_description03 );
    
    ASSERT_EQ( command_argument01.Get_Default_Value(), arg_default01 );
    ASSERT_EQ( command_argument02.Get_Default_Value(), arg_default02 );
    ASSERT_EQ( command_argument03.Get_Default_Value(), arg_default03 );

    // Test the type
    ASSERT_FALSE( command_argument01.Is_Valid_Type("") );
    ASSERT_FALSE( command_argument01.Is_Valid_Type("value") );
    ASSERT_FALSE( command_argument01.Is_Valid_Type("  ") );
    ASSERT_TRUE(  command_argument01.Is_Valid_Type("1") );
    ASSERT_TRUE(  command_argument01.Is_Valid_Type("-1.5") );
    ASSERT_TRUE(  command_argument01.Is_Valid_Type("123") );
    ASSERT_TRUE(  command_argument01.Is_Valid_Type("-123") );
    
    // Test the type
    ASSERT_FALSE( command_argument02.Is_Valid_Type("") );
    ASSERT_FALSE( command_argument02.Is_Valid_Type("value") );
    ASSERT_FALSE( command_argument02.Is_Valid_Type("  ") );
    ASSERT_TRUE(  command_argument02.Is_Valid_Type("1") );
    ASSERT_TRUE(  command_argument02.Is_Valid_Type("-1.5") );
    ASSERT_TRUE(  command_argument02.Is_Valid_Type("123") );
    ASSERT_TRUE(  command_argument02.Is_Valid_Type("-123") );
    
    // Test the type
    ASSERT_TRUE( command_argument03.Is_Valid_Type("") );
    ASSERT_TRUE( command_argument03.Is_Valid_Type("value") );
    ASSERT_TRUE( command_argument03.Is_Valid_Type("  ") );
    ASSERT_TRUE( command_argument03.Is_Valid_Type("1") );
    ASSERT_TRUE( command_argument03.Is_Valid_Type("-1.5") );
    ASSERT_TRUE( command_argument03.Is_Valid_Type("123") );
    ASSERT_TRUE( command_argument03.Is_Valid_Type("-123") );

    // Test if required
    ASSERT_TRUE(  command_argument01.Is_Required() );
    ASSERT_TRUE(  command_argument02.Is_Required() );
    ASSERT_FALSE( command_argument03.Is_Required() );

    // Test the == operator
    ASSERT_TRUE(  command_argument01 == command_argument01 );
    ASSERT_TRUE(  command_argument01 == command_argument02 );
    ASSERT_FALSE( command_argument01 == command_argument03 );
    ASSERT_TRUE(  command_argument02 == command_argument01 );
    ASSERT_TRUE(  command_argument02 == command_argument02 );
    ASSERT_FALSE( command_argument02 == command_argument03 );
    ASSERT_FALSE( command_argument03 == command_argument01 );
    ASSERT_FALSE( command_argument03 == command_argument02 );
    ASSERT_TRUE(  command_argument03 == command_argument03 );

}


