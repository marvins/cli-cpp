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

/***********************************************************/
/*          Test the Simple Push and Pop options           */
/***********************************************************/
TEST( An_Event_Queue, Simple_Push_Pop_Tests )
{
    // Expected Queue Size
    const int exp_queue_size = 100;

    // Create an event queue
    CLI::EVT::An_Event_Queue test_queue( exp_queue_size );

    // Check the current size
    ASSERT_EQ( test_queue.Get_Current_Size(), 0 );
    ASSERT_EQ( test_queue.Get_Max_Size(), exp_queue_size );

    // Start adding items
    for( int i=0; i<exp_queue_size; i++ ){
        test_queue.Push_Event( i );
    }

    // Test popping items
    for( int i=0; i<exp_queue_size; i++ ){
        ASSERT_EQ( test_queue.Pop_Event(), i );
        ASSERT_EQ( test_queue.Get_Current_Size(), exp_queue_size - i - 1);
        ASSERT_EQ( test_queue.Get_Max_Size(),  exp_queue_size);
    }

}
