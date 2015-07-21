/**
 * @file    TEST_String_Utilities.cpp
 * @author  Marvin Smith
 * @date    5/25/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/utility/String_Utilities.hpp>

using namespace CLI;

/**************************************************/
/*      Test the Number to String Function        */
/**************************************************/
TEST( String_Utilities, str2num )
{

    // Check conversion to integers
    ASSERT_EQ( UTILS::str2num<int>("123"), 123 );
    ASSERT_EQ( UTILS::str2num<int>("123.3"), 123 );
    ASSERT_EQ( UTILS::str2num<int>("-123"), -123 );
    ASSERT_EQ( UTILS::str2num<int>("-123.3"), -123 );

    // Check conversion to float
    ASSERT_NEAR( UTILS::str2num<float>("123"), 123, 0.0001 );
    ASSERT_NEAR( UTILS::str2num<float>("-123"), -123, 0.0001 );
    ASSERT_NEAR( UTILS::str2num<float>("123.1"), 123.1, 0.0001 );
    ASSERT_NEAR( UTILS::str2num<float>("-123.1"), -123.1, 0.0001 );

}


/************************************************/
/*      Test the String to Number Function      */
/************************************************/
TEST( String_Utilities, num2str )
{

    // Check conversion to string from integer
    ASSERT_EQ( UTILS::num2str(1234), "1234");
    ASSERT_EQ( UTILS::num2str(1234.5), "1234.5");
    ASSERT_EQ( UTILS::num2str(-1234), "-1234");
    ASSERT_EQ( UTILS::num2str(-1234.5), "-1234.5");

}


/************************************************/
/*      Test the String Alignment Values        */
/************************************************/
TEST( String_Utilities, StringAlignment_value )
{
    ASSERT_EQ( (int)UTILS::StringAlignment::CENTER, 1 );
    ASSERT_EQ( (int)UTILS::StringAlignment::LEFT, 2 );
    ASSERT_EQ( (int)UTILS::StringAlignment::RIGHT, 3 );
}

/************************************************/
/*      Test the String Direction Values        */
/************************************************/
TEST( String_Utilities, StringDirection_value )
{
    ASSERT_EQ( (int)UTILS::StringDirection::LEFT, 1 );
    ASSERT_EQ( (int)UTILS::StringDirection::RIGHT, 2 );
    ASSERT_EQ( (int)UTILS::StringDirection::BOTH, 3 );
}


/*****************************************/
/*      Test the String Trim Method      */
/*****************************************/
TEST( String_Utilities, String_Trim )
{

    // Test String Trim with default arguments on empty string
    ASSERT_EQ( UTILS::String_Trim(""), "");
    
    // Test String Trim with default arguments on normal strings
    ASSERT_EQ( UTILS::String_Trim("hello"), "hello");
    ASSERT_EQ( UTILS::String_Trim(" hello "), "hello");
    ASSERT_EQ( UTILS::String_Trim(" \nHello\0"), "Hello");
    ASSERT_EQ( UTILS::String_Trim("\nHell0"), "Hell0");
    ASSERT_EQ( UTILS::String_Trim("\n \0 \n \0"), "");
    
    // Test String Trim with left direction on normal strings
    ASSERT_EQ( UTILS::String_Trim("hello",   UTILS::StringDirection::LEFT), "hello");
    ASSERT_EQ( UTILS::String_Trim(" hello ", UTILS::StringDirection::LEFT), "hello ");
    
    // Test String Trim with right direction on normal strings
    ASSERT_EQ( UTILS::String_Trim("hello",   UTILS::StringDirection::RIGHT), "hello");
    ASSERT_EQ( UTILS::String_Trim(" hello ", UTILS::StringDirection::RIGHT), " hello");

    // Test String Trim with different patterns
    ASSERT_EQ( UTILS::String_Trim("hello1234!@#$", "h$", UTILS::StringDirection::BOTH ), "ello1234!@#");
}


/********************************************/
/*       Test the String Fill Method        */
/********************************************/
TEST( String_Utilities, String_Fill )
{
    
    ASSERT_EQ( UTILS::String_Fill( "Hello", ' ', 10 ), "Hello          "); 
    ASSERT_EQ( UTILS::String_Fill( "Hello", '*', 10 ), "Hello**********"); 
    ASSERT_EQ( UTILS::String_Fill( "Hello", ' ', 5, UTILS::StringDirection::BOTH), "     Hello     ");

}


/************************************/
/*          Format String           */
/************************************/
TEST( String_Utilities, Format_String )
{
    ASSERT_EQ( UTILS::Format_String( "ABCDEF", 
                                     10,
                                     UTILS::StringAlignment::RIGHT,
                                     '*' ),
               "****ABCDEF" );
    
    ASSERT_EQ( UTILS::Format_String( "ABCDEF", 
                                     10,
                                     UTILS::StringAlignment::LEFT,
                                     '*' ),
               "ABCDEF****" );

    ASSERT_EQ( UTILS::Format_String( "ABCDEF", 
                                     10,
                                     UTILS::StringAlignment::CENTER,
                                     '*' ),
               "**ABCDEF**" );


}


/********************************************/
/*      Test the String Split Method        */
/********************************************/
TEST( String_Utilities, String_Split ){

    // Create array with many spaces
    const std::string test_input_01 = " hello there          world ";

    // Test output
    std::vector<std::string> output_01 = UTILS::String_Split( test_input_01 );

    ASSERT_EQ( (int)output_01.size(), 3 );
    ASSERT_EQ( output_01[0], "hello" );
    ASSERT_EQ( output_01[1], "there" );
    ASSERT_EQ( output_01[2], "world" );

}


