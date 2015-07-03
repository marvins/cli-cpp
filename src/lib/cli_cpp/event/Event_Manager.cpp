/**
 * @file    Event_Manager.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
 */
#include "Event_Manager.hpp"

// C++ Standard Libraries
#include <iostream>
#include <unistd.h>


// CLI Libraries
#include "../utility/Log_Utilities.hpp"

namespace CLI{
namespace EVT{

static std::shared_ptr<Event_Manager> instance = nullptr;

/**************************/
/*      Constructor       */
/**************************/
Event_Manager::Event_Manager( const int& event_queue_max_capacity,
                              const int& event_work_queue_threads )
  : m_class_name("Event_Manager"),
    m_is_running(event_work_queue_threads, true)
{
    
    // Create the event queue
    m_event_queue = std::make_shared<An_Event_Queue>(event_queue_max_capacity);


    // Start the threads
    m_event_process_threads.clear();
    for( int i=0; i<event_work_queue_threads; i++ ){
        m_event_process_threads.push_back( std::thread( &Event_Manager::Event_Process_Runner,
                                                        this,
                                                        i ) );
    }

}


/**************************/
/*       Destructor       */
/**************************/
Event_Manager::~Event_Manager()
{

    // Stop the thread
    for( size_t i=0; i<m_event_process_threads.size(); i++ ){
        m_is_running[i] = false;
        m_event_queue->Push_Event((int)CLI_Event_Type::CLI_NULL);
    }
    
    
    // Clear the event queue
    m_event_queue->Clear();

    
    // Wait to join the threads
    for( size_t i=0; i<m_event_process_threads.size(); i++ ){
        if( m_event_process_threads[i].joinable() ){
            m_event_process_threads[i].join();
        }
    }


    // Reset
    m_event_queue.reset();

}


/********************************/
/*          Initialize          */
/********************************/
void Event_Manager::Initialize( const int& event_queue_max_capacity,
                                const int& event_work_queue_threads )
{
    // Check the singleton instance
    if( instance == nullptr ){
        instance = Event_Manager::ptr_t(new Event_Manager( event_queue_max_capacity,
                                                           event_work_queue_threads ));
    }

}


/********************************/
/*          Initialize          */
/********************************/
void Event_Manager::Finalize()
{
    // Check the singleton instance
    if( instance != nullptr ){
        instance = nullptr;
    }

}

/**********************************************/
/*          Get Instance Of Handler           */
/**********************************************/
Event_Manager::ptr_t Event_Manager::Instance_Of()
{
    // Initialize
    Initialize();

    return instance;
}


/***********************************************/
/*         Register the event handler          */
/***********************************************/
void Event_Manager::Register_CLI_Event_Handler( A_CLI_Event_Handler_Base::ptr_t handler )
{
    // Get an instance
    Event_Manager::ptr_t inst = Instance_Of();

    // add the handler to the list
    inst->m_event_handlers.push_back(handler);
}


/*****************************************/
/*           Process an Event            */
/*****************************************/
void Event_Manager::Process_Event( const int& event )
{

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Event ID: " << event << ",  File: " << __FILE__ << ", Line: " << __LINE__;
    
    
    // Get an instance
    Event_Manager::ptr_t inst = Instance_Of();

    
    // Add event to queue
    inst->m_event_queue->Push_Event( event );

}


/*********************************/
/*          Event Runner         */
/*********************************/
void Event_Manager::Event_Process_Runner( const int& thread_id )
{
    // Misc variables
    int temp_event;

    // Run while the flag is valid
    while( m_is_running[thread_id] == true )
    {

        // Get the next event
        temp_event = m_event_queue->Pop_Event();

        // Skip null events
        if( temp_event == (int)CLI_Event_Type::CLI_NULL ){
            continue;
        }
    
        // Iterate over event managers
        for( size_t i=0; i<m_event_handlers.size(); i++ ){
            
            // Log
            BOOST_LOG_TRIVIAL(trace) << "Processing event " << temp_event << " through handler " << i << std::endl;

            // Check if null
            if( m_event_handlers[i] == nullptr ){
                BOOST_LOG_TRIVIAL(warning) << "Event handler at position " << i << " is currently nullptr. Method: " << __func__ << ", File: " << __FILE__ << ", Line: " << __LINE__;
            }

            // Check if supported
            else if( m_event_handlers[i]->Is_Supported_Event( temp_event ) == true ){
                m_event_handlers[i]->Process_Event(temp_event);
            }
        }

    }

}

} // End of EVT Namespace
} // End of CLI Namespace
