/**
 * @file    TEST_Event_Manager_Config.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/event/Event_Manager_Config.hpp>


/*******************************************/
/*          Test the Constructors          */
/*******************************************/
TEST(  Event_Manager_Config, Constructor )
{
    // Expected results
    const int exp_event_queue_max_capacity_01 = 50;
    const int exp_event_work_queue_threads_01 = 2;
    
    const int exp_event_queue_max_capacity_02 = 150;
    const int exp_event_work_queue_threads_02 = 4;

    // Create a config using the default constructor
    CLI::EVT::Event_Manager_Config config01;

    // Test the results
    ASSERT_EQ( config01.Get_Event_Queue_Max_Capacity(),      exp_event_queue_max_capacity_01 );
    ASSERT_EQ( config01.Get_Event_Work_Queue_Thread_Count(), exp_event_work_queue_threads_01 );

    // Create a config using the parameterized constructor
    CLI::EVT::Event_Manager_Config config02( exp_event_queue_max_capacity_02,
                                             exp_event_work_queue_threads_02 );

    // Test the results
    ASSERT_EQ( config02.Get_Event_Queue_Max_Capacity(),      exp_event_queue_max_capacity_02 );
    ASSERT_EQ( config02.Get_Event_Work_Queue_Thread_Count(), exp_event_work_queue_threads_02 );

}

