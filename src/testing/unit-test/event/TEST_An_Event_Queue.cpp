/**
 * @file    TEST_An_Event_Queue.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/event/An_Event_Queue.hpp>

/*******************************************/
/*          Test the Constructor           */
/*******************************************/
TEST( An_Event_Queue, Constructor )
{
    // Expected Queue Size
    const int exp_queue_size = 100;

    // Create an event queue
    CLI::EVT::An_Event_Queue test_queue( exp_queue_size );

    // Check the current size
    ASSERT_EQ( test_queue.Get_Current_Size(), 0 );
    ASSERT_EQ( test_queue.Get_Max_Size(), exp_queue_size );

}


