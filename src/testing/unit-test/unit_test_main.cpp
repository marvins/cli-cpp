/**
 * @file    unit_test_main.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/

// C++ Standard Libraries
#include <iostream>

// Google Test
#include <gtest/gtest.h>

/**
 * @brief Main Function
*/
int main( int argc, char* argv[] )
{
    // Print Entry
    std::cout << "Running main() from " << __FILE__ << std::endl;

    // Initialize Google Test Framework
    testing::InitGoogleTest(&argc, argv);
  
    // Perform Tests
    return RUN_ALL_TESTS();
}

