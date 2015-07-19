/**
 * @file    TEST_An_Event_Queue.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/event/An_Event_Queue.hpp>

// C++ Standard Libraries
#include <thread>


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
    const int instance_id = 1;

    // Result values
    int act_event, act_id;

    // Create an event queue
    CLI::EVT::An_Event_Queue test_queue( exp_queue_size );

    // Check the current size
    ASSERT_EQ( test_queue.Get_Current_Size(), 0 );
    ASSERT_EQ( test_queue.Get_Max_Size(), exp_queue_size );

    // Start adding items
    for( int i=0; i<exp_queue_size; i++ ){
        test_queue.Push_Event( instance_id, i );
    }

    // Test popping items
    for( int i=0; i<exp_queue_size; i++ ){
        test_queue.Pop_Event( act_id, act_event );
        ASSERT_EQ( act_id, instance_id );
        ASSERT_EQ( act_event, i );
        ASSERT_EQ( test_queue.Get_Current_Size(), exp_queue_size - i - 1);
        ASSERT_EQ( test_queue.Get_Max_Size(),  exp_queue_size);
    }

}

/************************************************************************/
/*            Given the timeout, add the events to the list             */
/************************************************************************/
void Push_Event_Queue_After_Timeout( CLI::EVT::An_Event_Queue& event_queue,
                                     const std::vector<int>&   event_list,
                                     const int&                timeout_usec )
{
    // Instance
    const int instance = 1;

    // Start sleep
    usleep( timeout_usec );

    // Add each event
    for( size_t i=0; i<event_list.size(); i++ ){
        event_queue.Push_Event( instance, event_list[i] );
    }


}

/***********************************************************/
/*             Test the some blocking tests.               */
/***********************************************************/
TEST( An_Event_Queue, Pop_Empty_Queue_Blocking_Tests )
{
    // Expected Queue Size
    const int exp_queue_size = 100;
    const int instance_id = 1;

    // Create an event queue
    CLI::EVT::An_Event_Queue test_queue( exp_queue_size );

    // Check the current size
    ASSERT_EQ( test_queue.Get_Current_Size(), 0 );
    ASSERT_EQ( test_queue.Get_Max_Size(), exp_queue_size );

    // Create a list of events
    std::vector<int> event_list;
    for( int i=0; i<10; i++ ){
        event_list.push_back(i);
    }

    // Set the timeout
    int timeout_usec = 5000000;
    
    // Call method
    std::thread test_thread( Push_Event_Queue_After_Timeout, 
                             std::ref(test_queue),
                             event_list,
                             timeout_usec );

    // Start the pop
    for( int i=0; i<10; i++ ){
        
        // Get the next value
        int value, id;
        test_queue.Pop_Event( id, value);
        
        // Check the value
        ASSERT_EQ( value, i );
        ASSERT_EQ( id, instance_id );
    }

    // Join the thread
    test_thread.join();

}


