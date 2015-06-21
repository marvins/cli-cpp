/**
 * @file    TEST_A_Command_Alias.cpp
 * @author  Marvin Smith
 * @date    6/20/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/cmd/A_Command_Alias.hpp>

using namespace CLI;

/*******************************************/
/*        Test the CMD Constructor         */
/*******************************************/
TEST( A_Command_Alias, Constructors )
{
    // Default
    CMD::A_Command_Alias alias01;

    // Normal
    CMD::A_Command_Alias alias02("hello","world");

    // Check values
    ASSERT_EQ( alias01.Get_Alias_Name(), "" );
    ASSERT_EQ( alias01.Get_Command_Text(), "" );

    ASSERT_EQ( alias02.Get_Alias_Name(), "hello" );
    ASSERT_EQ( alias02.Get_Command_Text(), "world" );
}

