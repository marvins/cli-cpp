/**
 * @file    TEST_A_Command_Variable.cpp
 * @author  Marvin Smith
 * @date    7/19/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/cmd/A_Command_Variable.hpp>

using namespace CLI;

/***********************************/
/*      Check the Constructor      */
/***********************************/
TEST( A_Command_Variable, Constructors )
{

    // Check the parameterized Constructor
    CMD::A_Command_Variable variable("hello","world");

    ASSERT_EQ( variable.Get_Name(), "hello");
    ASSERT_EQ( variable.Get_Value(), "world");

}


/****************************************************/
/*          Check the Equivalent Operator           */
/****************************************************/
TEST( A_Command_Variable, Equivalent_Operator )
{
    // Create a list of variables
    CMD::A_Command_Variable variable01( "Hello", "World");
    CMD::A_Command_Variable variable02( "Hello", "World");
    CMD::A_Command_Variable variable03( "Hello", "WORLD");
    CMD::A_Command_Variable variable04( "HELLO", "World");
   
    // Check the == operator
    ASSERT_TRUE( variable01 == variable01 );
    ASSERT_TRUE( variable01 == variable02 );
    ASSERT_FALSE( variable01 == variable03 );
    ASSERT_FALSE( variable01 == variable04 );

    ASSERT_TRUE( variable02 == variable01 );
    ASSERT_TRUE( variable02 == variable02 );
    ASSERT_FALSE( variable02 == variable03 );
    ASSERT_FALSE( variable02 == variable04 );
    
    ASSERT_FALSE( variable03 == variable01 );
    ASSERT_FALSE( variable03 == variable02 );
    ASSERT_TRUE( variable03 == variable03 );
    ASSERT_FALSE( variable03 == variable04 );
    
    ASSERT_FALSE( variable04 == variable01 );
    ASSERT_FALSE( variable04 == variable02 );
    ASSERT_FALSE( variable04 == variable03 );
    ASSERT_TRUE( variable04 == variable04 );
}


/************************************************/
/*      Check the Is Valid Candidate Method     */
/************************************************/
TEST( A_Command_Variable, Is_Valid_Candidate )
{
    // Check valid conditions
    ASSERT_TRUE( CMD::A_Command_Variable::Is_Valid_Candidate("$Hello") );
    ASSERT_TRUE( CMD::A_Command_Variable::Is_Valid_Candidate("$o") );
    ASSERT_TRUE( CMD::A_Command_Variable::Is_Valid_Candidate("$World") );

    // Check invalid conditions
    ASSERT_FALSE( CMD::A_Command_Variable::Is_Valid_Candidate("") );
    ASSERT_FALSE( CMD::A_Command_Variable::Is_Valid_Candidate("Hello") );
    ASSERT_FALSE( CMD::A_Command_Variable::Is_Valid_Candidate("12") );
    ASSERT_FALSE( CMD::A_Command_Variable::Is_Valid_Candidate("$") );
    ASSERT_FALSE( CMD::A_Command_Variable::Is_Valid_Candidate("$1") );
    ASSERT_FALSE( CMD::A_Command_Variable::Is_Valid_Candidate("$$") );

}


/*********************************************************/
/*          Check the Process Variables Method           */
/*********************************************************/
TEST( A_Command_Variable, Process_Variables )
{

    ///////////////////////////////////////////////////
    // Test 01 (Empty Variable and Component List)
    std::vector<CMD::A_Command_Variable> variable_list01;
    std::vector<std::string>             component_list01;

    CMD::A_Command_Variable::Process_Variables( variable_list01, component_list01);

    ASSERT_EQ( (int)variable_list01.size(), 0 );
    ASSERT_EQ( (int)component_list01.size(), 0 );

    ////////////////////////////////////////////////////////////
    // Test 02 (Empty Variable List, Valid Component List)
    std::vector<CMD::A_Command_Variable> variable_list02;
    std::vector<std::string>             component_list02;
    component_list02.push_back("Hello");
    component_list02.push_back("World");

    CMD::A_Command_Variable::Process_Variables( variable_list02, component_list02);

    ASSERT_EQ( (int)variable_list02.size(), 0 );
    ASSERT_EQ( (int)component_list02.size(), 2 );
    ASSERT_EQ( component_list02[0], "Hello" );
    ASSERT_EQ( component_list02[1], "World" );

    ////////////////////////////////////////////////////////////
    // Test 03 (Valid Variable List, Empty Component List)
    std::vector<CMD::A_Command_Variable> variable_list03;
    std::vector<std::string>             component_list03;
    variable_list03.push_back(CMD::A_Command_Variable("Hello","World"));

    CMD::A_Command_Variable::Process_Variables( variable_list03, component_list03);

    ASSERT_EQ( (int)variable_list03.size(), 1 );
    ASSERT_EQ( (int)component_list03.size(), 0 );
    ASSERT_EQ( variable_list03[0], CMD::A_Command_Variable("Hello","World") );
    
    
    ////////////////////////////////////////////////////////////
    // Test 04 (Valid Variable List, Valid Component List)
    std::vector<CMD::A_Command_Variable> variable_list04;
    std::vector<std::string>             component_list04;
    variable_list04.push_back(CMD::A_Command_Variable("Hello","World"));
    variable_list04.push_back(CMD::A_Command_Variable("Foo","Bar"));
    
    component_list04.push_back("foo");
    component_list04.push_back("Foo");
    component_list04.push_back("hello");
    component_list04.push_back("Hello");
    component_list04.push_back("#foo");
    component_list04.push_back("$Foo");
    component_list04.push_back("$hello");
    component_list04.push_back("$Hello");

    CMD::A_Command_Variable::Process_Variables( variable_list04, component_list04);

    ASSERT_EQ( (int)variable_list04.size(), 2 );
    ASSERT_EQ( (int)component_list04.size(), 8 );
    ASSERT_EQ( variable_list04[0], CMD::A_Command_Variable("Hello","World") );
    ASSERT_EQ( variable_list04[1], CMD::A_Command_Variable("Foo","Bar"));

    ASSERT_EQ( component_list04[0], "foo" );
    ASSERT_EQ( component_list04[1], "Foo" );
    ASSERT_EQ( component_list04[2], "hello" );
    ASSERT_EQ( component_list04[3], "Hello" );
    ASSERT_EQ( component_list04[4], "#foo" );
    ASSERT_EQ( component_list04[5], "Bar" );
    ASSERT_EQ( component_list04[6], "$hello" );
    ASSERT_EQ( component_list04[7], "World" );

}


/********************************************************/
/*      Test the Load Variable Config File Command      */
/********************************************************/
TEST( A_Command_Variable, Load_Variable_Configuration_File )
{




}


