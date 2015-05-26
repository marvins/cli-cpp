/**
 * @file    TEST_An_ASCII_Print_Table.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/utility/An_ASCII_Print_Table.hpp>

using namespace CLI;

void Check_Table_Output( const std::vector<std::string>& test_output, 
                         const int& test_number )
{
    
    ASSERT_EQ( test_output[0], "" );
    ASSERT_EQ( test_output[1], "" );
    ASSERT_EQ( test_output[2], "    +----------+----------+--------+\n\r" );
    ASSERT_EQ( test_output[3], "    | Title1   | Title2   | Title3 |\n\r" );
    ASSERT_EQ( test_output[4], "    +----------+----------+--------+\n\r" );

    if( test_number == 1 ){
        ASSERT_EQ( test_output[5], "    | Hello    |          |        |\n\r" );
        ASSERT_EQ( test_output[6], "    |          |          |        |\n\r" );
        ASSERT_EQ( test_output[7], "    |          | World    |        |\n\r" );
    } else {
        ASSERT_EQ( test_output[5], "    |          |          |        |\n\r" );
        ASSERT_EQ( test_output[6], "    |          |          |        |\n\r" );
        ASSERT_EQ( test_output[7], "    |          |          |        |\n\r" );
    }
    ASSERT_EQ( test_output[8], "    |          |          |        |\n\r" );
    ASSERT_EQ( test_output[9], "    +----------+----------+--------+\n\r" );
}


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


/*****************************************************/
/*             Test the ASCII Print Table            */
/*****************************************************/
TEST( An_ASCII_Print_Table, Construction_Test_01_Invalid )
{
    // Define our expected titles
    std::vector<std::string> exp_titles;
    exp_titles.push_back("Title1");
    exp_titles.push_back("Title2");
    exp_titles.push_back("Title3");
    
    // Define our expected table widths
    std::vector<int> exp_widths;
    exp_widths.push_back(20);
    exp_widths.push_back(25);

    // Define our expected configuration
    UTILS::An_ASCII_Print_Table_Config exp_config(false,true);
    
    // Create a Table
    UTILS::An_ASCII_Print_Table print_table( exp_titles, exp_widths, exp_config ); 
    
    // Validate its valid
    ASSERT_FALSE( print_table.Is_Valid() );


}


/*****************************************************/
/*             Test the ASCII Print Table            */
/*****************************************************/
TEST( An_ASCII_Print_Table, Construction_Test_02 )
{
    // Define our expected titles
    std::vector<std::string> exp_titles;
    exp_titles.push_back("Title1");
    exp_titles.push_back("Title2");
    exp_titles.push_back("Title3");
    
    // Define our expected table widths
    std::vector<int> exp_widths;
    exp_widths.push_back(10);
    exp_widths.push_back(10);
    exp_widths.push_back(8);

    // Define our expected configuration
    UTILS::An_ASCII_Print_Table_Config exp_config(false,true);
    
    // Create a Table
    UTILS::An_ASCII_Print_Table print_table( exp_titles, exp_widths, exp_config ); 
    
    // Validate its valid
    ASSERT_TRUE( print_table.Is_Valid() );
    
    // Check the output
    std::vector<std::string> test_output(10);
    ASSERT_TRUE( print_table.Print_Table( test_output, 2, 9, 4 ));
    
    Check_Table_Output( test_output, 0 );

    // Add some entries
    print_table.Add_Entry(0, 0, " Hello");
    print_table.Add_Entry(1, 1, " World");
    ASSERT_TRUE( print_table.Print_Table( test_output, 2, 9, 4 ));
    Check_Table_Output( test_output, 1 );

}


