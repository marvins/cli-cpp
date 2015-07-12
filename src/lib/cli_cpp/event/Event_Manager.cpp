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

/// Global Event Manager Instance
static std::shared_ptr<Event_Manager> instance = nullptr;

/**************************/
/*      Constructor       */
/**************************/
Event_Manager::Event_Manager( Event_Manager_Config const& config )
  : m_class_name("Event_Manager"),
    m_config(config),
    m_is_running(config.Get_Event_Work_Queue_Thread_Count(), true)
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: " << m_class_name << ", File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Create the event queue
    m_event_queue = std::make_shared<An_Event_Queue>(m_config.Get_Event_Queue_Max_Capacity());
    
    // Print the queue in the outer thread
    int tempA, tempB;
    m_event_queue->Push_Event(-1, (int)CLI_Event_Type::CLI_NULL);
    m_event_queue->Pop_Event(tempA, tempB);

    // Start the threads
    m_event_process_threads.clear();
    for( int i=0; i<m_config.Get_Event_Work_Queue_Thread_Count(); i++ ){
        m_event_process_threads.push_back( std::thread( &Event_Manager::Event_Process_Runner,
                                                        this,
                                                        i ) );
    }

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: " << m_class_name << ", File: " << __FILE__ << ", Line: " << __LINE__;
}


/**************************/
/*       Destructor       */
/**************************/
Event_Manager::~Event_Manager()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: " << m_class_name << ", File: " << __FILE__ << ", Line: " << __LINE__;

    // Stop the thread
    for( size_t i=0; i<m_event_process_threads.size(); i++ ){
        m_is_running[i] = false;
        m_event_queue->Push_Event(-1, (int)CLI_Event_Type::CLI_NULL);
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

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: " << m_class_name << ", File: " << __FILE__ << ", Line: " << __LINE__;
}


/********************************/
/*          Initialize          */
/********************************/
void Event_Manager::Initialize( Event_Manager_Config const& config )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Check the singleton instance
    if( instance == nullptr ){
        instance = Event_Manager::ptr_t(new Event_Manager( config ));
    }

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
}


/********************************/
/*            Finalize          */
/********************************/
void Event_Manager::Finalize()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Check the singleton instance
    if( instance != nullptr ){
        instance.reset();
        instance = nullptr;
    }
    
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
}


/*************************************************************/
/*          Check if Event Manager is Initialized            */
/*************************************************************/
bool Event_Manager::Is_Initialized()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Check the singleton instance
    if( instance == nullptr ){
        return false;
    }
    return true;
}


/**********************************************/
/*          Get Instance Of Handler           */
/**********************************************/
Event_Manager::ptr_t Event_Manager::Instance_Of()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Check if we are initialized
    if( Is_Initialized() == false ){
        BOOST_LOG_TRIVIAL(warning) << "Event_Manager has not been initialized while calling method " << __func__;
        return nullptr;
    }
    
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;

    // Otherwise, return instance
    return instance;
}


/***********************************************/
/*         Register the event handler          */
/***********************************************/
void Event_Manager::Register_CLI_Event_Handler( A_CLI_Event_Handler_Base::ptr_t handler )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
    
    
    // Make sure we are initialized
    if( Is_Initialized() == false ){
        BOOST_LOG_TRIVIAL(error) << "Unable to register the CLI Event Handler as the Event-Manager is not initialized. File: " << __FILE__ << ", Method: " << __func__ << ", Line: " << __LINE__;
    }


    // Get an instance
    Event_Manager::ptr_t inst = Instance_Of();

    // add the handler to the list
    inst->m_event_handlers.push_back(handler);
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
}


/*****************************************/
/*           Process an Event            */
/*****************************************/
void Event_Manager::Process_Event( const int& instance, 
                                   const int& event )
{

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Event ID: " << event << ",  File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Make sure we are initialized
    if( Is_Initialized() == false ){
        BOOST_LOG_TRIVIAL(error) << "Event-Manager is not initialized. Method: " << __func__ << ", Class: Event_Manager,  File: " << __FILE__ << ", Line: " << __LINE__;
        return;
    }
    
    // Get an instance
    Event_Manager::ptr_t inst = Instance_Of();

    
    // Add event to queue
    if( inst == nullptr || inst->m_event_queue == nullptr ){
        BOOST_LOG_TRIVIAL(trace) << "Event queue is currently null.";
        return;
    }
    inst->m_event_queue->Push_Event( instance, event );

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
}


/*********************************/
/*          Event Runner         */
/*********************************/
void Event_Manager::Event_Process_Runner( const int& thread_id )
{
    // Misc variables
    int temp_event, temp_instance;

    // Run while the flag is valid
    while( m_is_running[thread_id] == true )
    {
        
        // Get the next event
        m_event_queue->Pop_Event( temp_instance, 
                                  temp_event);
            
        // Log result    
        BOOST_LOG_TRIVIAL(trace) << "Popped event (" << temp_event << "), Event queue size: " << m_event_queue->Get_Current_Size();

        // Skip null events
        if( temp_event == (int)CLI_Event_Type::CLI_NULL ){
            BOOST_LOG_TRIVIAL(trace) << "CLI_NULL event detected.  Skipping.";
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
                m_event_handlers[i]->Process_Event( temp_instance, 
                                                    temp_event);
            }
        }

    }

}

} // End of EVT Namespace
} // End of CLI Namespace
