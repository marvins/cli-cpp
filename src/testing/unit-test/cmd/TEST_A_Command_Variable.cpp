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

