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
#include "../utility/Stopwatch.hpp"


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
    for( int i=0; i<m_config.Get_Event_Work_Queue_Thread_Count(); i++ )
    {
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
    for( size_t i=0; i<m_event_process_threads.size(); i++ )
    {
        m_is_running[i] = false;
        m_event_queue->Push_Event(-1, (int)CLI_Event_Type::CLI_NULL);
    }
    
    
    // Wait to join the threads
    for( size_t i=0; i<m_event_process_threads.size(); i++ )
    {
        if( m_event_process_threads[i].joinable() )
        {
            std::cout << "Closing Thread: " << i << std::endl;
            m_event_process_threads[i].join();
        }
    }
    m_event_process_threads.clear();
    
    
    // Clear the event queue
    m_event_queue->Clear();

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

    // Set the init flag
    instance->m_is_initialized = true;

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: Event_Manager, File: " << __FILE__ << ", Line: " << __LINE__;
}


/********************************/
/*            Finalize          */
/********************************/
void Event_Manager::Finalize()
{
    // Log Entry
    const std::string m_class_name = "Event_Manager";
    CLI_LOG_CLASS_ENTRY();
    
    // Check the singleton instance
    if( instance != nullptr )
    {
        instance->m_is_initialized = false;
        instance.reset();
        instance = nullptr;
    }
    
    
    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/*************************************************************/
/*          Check if Event Manager is Initialized            */
/*************************************************************/
bool Event_Manager::Is_Initialized()
{
    // Check the singleton instance
    if( instance == nullptr ){
        return false;
    } else {
        return instance->m_is_initialized;
    }
}


/**********************************************/
/*          Get Instance Of Handler           */
/**********************************************/
Event_Manager::ptr_t Event_Manager::Instance_Of()
{
    // Log Entry
    const std::string m_class_name = "Event_Manager";
    CLI_LOG_CLASS_ENTRY();
    
    // Check if we are initialized
    if( Is_Initialized() == false ){
        CLI_LOG_CLASS( warning,
                       "Event_Manager has not been initialized.");
        return nullptr;
    }
    
    
    // Log Exit
    CLI_LOG_CLASS_EXIT();

    // Otherwise, return instance
    return instance;
}


/***********************************************/
/*         Register the event handler          */
/***********************************************/
void Event_Manager::Register_CLI_Event_Handler( A_CLI_Event_Handler_Base::ptr_t handler )
{
    // Log Entry
    const std::string m_class_name = "Event_Manager";
    CLI_LOG_CLASS_ENTRY();
    
    
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
    const std::string m_class_name = "Event_Manager";
    CLI_LOG_CLASS( trace, 
                   "Start of method. Event-ID: " + std::to_string(event) + ", Instance: " + std::to_string(instance));
    
    // Make sure we are initialized
    if( Is_Initialized() == false )
    {
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
    
    // Check if the event should be added
    bool filter =  inst->m_config.Filter_Event( event );

    
    // Push the event into the queue
    inst->m_event_queue->Push_Event( instance, 
                                     event,
                                     filter );

    // Log Exit
    CLI_LOG_CLASS( trace, 
                   "End of method. Event-ID: " + std::to_string(event) + ", Instance: " + std::to_string(instance));
}


/*********************************/
/*          Event Runner         */
/*********************************/
void Event_Manager::Event_Process_Runner( const int& thread_id )
{
    // Log Entry
    const std::string m_class_name = "Event_Manager";
    CLI_LOG_CLASS_ENTRY();

    // Misc variables
    int temp_event, temp_instance;
    Stopwatch<double> event_stopwatch;
    Stopwatch<double> wait_stopwatch;

    // Run while the flag is valid
    while( m_is_running[thread_id] == true )
    {
        
        // Log wait
        CLI_LOG_CLASS( trace,
                       "Event-Thread: " + std::to_string(thread_id) + ", Starting Event-Queue Pop.");
        
        // Get the next event
        wait_stopwatch.Start();
        m_event_queue->Pop_Event( temp_instance, 
                                  temp_event);
        wait_stopwatch.Stop();
        event_stopwatch.Start();    

        // Log result    
        CLI_LOG_CLASS( trace,
                       "Event-Thread: " + std::to_string(thread_id) + ", Popped event (" + std::to_string(temp_event) 
                       + "), Event queue size: " + std::to_string(m_event_queue->Get_Current_Size()));

        // Skip null events
        if( temp_event == (int)CLI_Event_Type::CLI_NULL ){
            BOOST_LOG_TRIVIAL(trace) << "CLI_NULL event detected.  Skipping.";
            continue;
        }
    
        // Iterate over event managers
        for( size_t i=0; i<m_event_handlers.size(); i++ ){
            
            // Log
            CLI_LOG_CLASS( trace,
                           "Event-Thread: " + std::to_string(thread_id) + ", Processing Event: " 
                           + std::to_string(temp_event) + ", Handler: " + std::to_string(i));

            // Check if null
            if( m_event_handlers[i] == nullptr )
            {
                CLI_LOG_CLASS( warning,
                               "Event-Thread: " + std::to_string(thread_id) + ", Event handler at position " 
                               + std::to_string(i) + " is currently nullptr.");
            }

            // Check if supported
            else if( m_event_handlers[i]->Is_Supported_Event( temp_event ) == true )
            {
                m_event_handlers[i]->Process_Event( temp_instance, 
                                                    temp_event);
            }
        }

        // Log
        event_stopwatch.Stop();
        {
            std::stringstream ssin;
            ssin << std::fixed << "Finished processing event (" << temp_event << ")  Time Waiting: " 
                 << std::fixed << wait_stopwatch.Get_Duration().count() << " seconds, Time Processing: " 
                 << event_stopwatch.Get_Duration().count() << " seconds";
            CLI_LOG_CLASS( trace, ssin.str() ); 
        }

    }

    // Log Completion
    CLI_LOG_CLASS_EXIT();
}

} // End of EVT Namespace
} // End of CLI Namespace
