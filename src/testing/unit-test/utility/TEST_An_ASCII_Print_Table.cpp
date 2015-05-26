/**
 * @file    TEST_An_ASCII_Print_Table.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/utility/An_ASCII_Print_Table.hpp>

using namespace CLI;

/********************************************************/
/*      Test the ASCII Print Table Configuration        */
/********************************************************/
TEST( An_ASCII_Print_Table_Config, Constructors )
{
    // Create a default configuration
    UTILS::An_ASCII_Print_Table_Config config01;
    ASSERT_TRUE( config01.Has_Blank_Line_Before_Entry() ); 
    ASSERT_TRUE( config01.Has_Blank_Line_After_Entry() ); 
    
    
    UTILS::An_ASCII_Print_Table_Config config02(false,false);
    ASSERT_FALSE( config02.Has_Blank_Line_Before_Entry() ); 
    ASSERT_FALSE( config02.Has_Blank_Line_After_Entry() ); 


}

