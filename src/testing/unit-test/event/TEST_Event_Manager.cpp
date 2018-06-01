/**
 * @file    TEST_Event_Manager.cpp
 * @author  Marvin Smith
 * @date    7/4/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/event/Event_Manager.hpp>

/*******************************************************************/
/*          Test the Event Manager's Initialization Methods        */
/*******************************************************************/
TEST( Event_Manager, Initialization )
{
    // Check the event manager and make sure it is initialized
    ASSERT_FALSE( CLI::EVT::Event_Manager::Is_Initialized() );
    
    // Create an event manager configuration
    CLI::EVT::Event_Manager_Config config01;

    // Initialize
    CLI::EVT::Event_Manager::Initialize( config01 );

    // Make sure its initialized
    ASSERT_TRUE( CLI::EVT::Event_Manager::Is_Initialized() );

    // Finalize
    CLI::EVT::Event_Manager::Finalize();

    // Make sure it is no longer initialized
    ASSERT_FALSE( CLI::EVT::Event_Manager::Is_Initialized() );

}


/**************************************************************************/
/*          Test the Event-Manager's Request Instance-ID Method.          */
/**************************************************************************/
TEST( Event_Manager, Instance_ID_Methods )
{
    // Check the event manager and make sure it is initialized
    ASSERT_FALSE( CLI::EVT::Event_Manager::Is_Initialized() );

    // Create an event manager configuration
    CLI::EVT::Event_Manager_Config config01;

    // Initialize
    CLI::EVT::Event_Manager::Initialize( config01 );

    // Make sure its initialized
    ASSERT_TRUE( CLI::EVT::Event_Manager::Is_Initialized() );


    // Make requests
    ASSERT_EQ( CLI::EVT::Event_Manager::Request_Instance_ID(), 0);
    ASSERT_EQ( CLI::EVT::Event_Manager::Request_Instance_ID(), 1);
    ASSERT_EQ( CLI::EVT::Event_Manager::Request_Instance_ID(), 2);
    ASSERT_EQ( CLI::EVT::Event_Manager::Request_Instance_ID(), 3);

    // Release one
    CLI::EVT::Event_Manager::Release_Instance_ID(2);

    // Request again
    ASSERT_EQ( CLI::EVT::Event_Manager::Request_Instance_ID(), 2);
    ASSERT_EQ( CLI::EVT::Event_Manager::Request_Instance_ID(), 4);


    // Finalize
    CLI::EVT::Event_Manager::Finalize();

    // Make sure it is no longer initialized
    ASSERT_FALSE( CLI::EVT::Event_Manager::Is_Initialized() );
}
