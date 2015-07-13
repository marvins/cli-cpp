/**
 * @file    unit_test_main.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/

// C++ Standard Libraries
#include <iostream>

// Google Test
#include <gtest/gtest.h>

// Unit Test Libraries
#include "UNIT_TEST_ONLY/Command_Parser.hpp"


/**
 * @brief Main Function
*/
int main( int argc, char* argv[] )
{
    // Parse Command Line
    Process_Command_Line( argc, argv );

    // Print Entry
    std::cout << "Running main() from " << __FILE__ << std::endl;

    // Initialize Google Test Framework
    testing::InitGoogleTest(&argc, argv);
  
    // Perform Tests
    return RUN_ALL_TESTS();
}

