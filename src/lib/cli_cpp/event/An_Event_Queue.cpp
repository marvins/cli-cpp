/**
 * @file    An_Event_Queue.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include "An_Event_Queue.hpp"


// CLI Libraries
#include "../utility/Log_Utilities.hpp"


// C++ Standard Libraries
#include <cerrno>
#include <iostream>
#include <stdexcept>
#include <sstream>

// Semaphore
#include <semaphore.h>

namespace CLI{
namespace EVT{

/******************************/
/*        Constructor         */
/******************************/
An_Event_Queue::An_Event_Queue( const int& max_queue_size )
  : m_class_name("An_Event_Queue"),
    m_head(0),
    m_tail(0),
    m_max_queue_size(max_queue_size),
    m_close_flag(false),
    m_current_size(0)
{

    // Log Entry
    CLI_LOG_CLASS_ENTRY();
    
    
    // Create the queue
    if( max_queue_size < 1 ){
        throw std::runtime_error("Size cannot be less than 1.");
    }
    m_event_queue = new std::tuple<int,int>[max_queue_size];
    
    
    // Initialize the semaphores
#ifdef __APPLE__   
    
    // Unlink each 
    sem_unlink("/pop_semaphore");
    sem_unlink("/push_semaphore");

    // Open each semaphore
    if( (m_pop_semaphore = sem_open("/pop_semaphore", O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED ){
        sem_close(m_pop_semaphore);
        sem_unlink("/pop_semaphore");
        throw std::runtime_error(std::string("Unable to initialize pop semaphore. Details: ") + strerror(errno));
    }
    
    if( (m_push_semaphore = sem_open("/push_semaphore", O_CREAT | O_EXCL, 0666, max_queue_size)) == SEM_FAILED ){
        sem_close(m_push_semaphore);
        sem_unlink("/push_semaphore");
        throw std::runtime_error(std::string("Unable to initialize push semaphore. Details: ") + strerror(errno));
    }
#else
    // Allocate the semaphores
    m_pop_semaphore = new sem_t;
    m_push_semaphore = new sem_t;
    
    // Initialized Semaphores
    if( sem_init( m_pop_semaphore, 0, 0) != 0 ){
        throw std::runtime_error(std::string("Unable to initialize pop semaphore. Details: ") + strerror(errno));
    }
    if( sem_init( m_push_semaphore, 0, max_queue_size) != 0 ){
        throw std::runtime_error(std::string("Unable to initialize push semaphore. Details: ") + strerror(errno));
    }
#endif

    
    // Initialize array values
    for( int i=0; i<m_max_queue_size; i++ ){
        m_event_queue[i] = std::make_tuple(-1, (int)CLI_Event_Type::CLI_NULL);
    }


    // Set the current size
    m_current_size = 0;
    
    
    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/*********************************/
/*          Destructor           */
/*********************************/
An_Event_Queue::~An_Event_Queue()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    
    // Delete the queue
    delete [] m_event_queue;

    // Set to null
    m_event_queue = nullptr;


#ifdef __APPLE__
    /// APPLE should remove their Unix badge as they don't implement sem_init, sem_getvalue, and sem_destroy
    // Close semaphores
    sem_close( m_pop_semaphore );
    sem_close( m_push_semaphore );
    
    // Unlink the semaphores
    sem_unlink("/pop_semaphore");
    sem_unlink("/push_semaphore");

#else
    // Linux is the real unix
    sem_destroy( m_pop_semaphore  );
    sem_destroy( m_push_semaphore );
    
    // Deallocate
    if( m_pop_semaphore != NULL && m_pop_semaphore != nullptr ){
        delete m_pop_semaphore;
    }
    if( m_push_semaphore != NULL && m_push_semaphore != nullptr ){
        delete m_push_semaphore;
    }
#endif


    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/**************************/
/*         Clear          */
/**************************/
void An_Event_Queue::Clear()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Class: " << m_class_name << ", File: " << __FILE__ << ", Line: " << __LINE__;
    
    
    // Set close flag
    m_close_flag = true;

    // Increment all semaphores
    sem_post( m_push_semaphore );
    sem_post( m_pop_semaphore );

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: " << m_class_name << ", File: " << __FILE__ << ", Line: " << __LINE__;
}


/*****************************/
/*        Push Command       */
/*****************************/
void An_Event_Queue::Push_Event( const int&  instance,
                                 const int&  event,
                                 const bool& filter )
{
    // Log Entry
    CLI_LOG_CLASS( trace,
                   "Start of Method. Inst-ID: " + std::to_string(instance) 
                   + ", Event-ID: " + std::to_string(event) 
                   + ", Filter-Flag: " + std::to_string(filter));

   
    // Check if we need to filter
    m_active_mutex.lock();
    if( filter == true && Has_Event( event ) == true )
    {
        BOOST_LOG_TRIVIAL(debug) << "Filtering Instance: " << instance << ", Event-ID: " << event;
        m_active_mutex.unlock();
        return;
    }
    m_active_mutex.unlock();


    // Decrement the push semaphore
    if( sem_wait( m_push_semaphore ) < 0 ){
        std::stringstream sin;
        sin << "Error with semaphore.";
        throw std::runtime_error(sin.str());   
    }

    
    // Lock the mutex
    m_mtx.lock();


    // Register the Event
    Register_Event( event );
    
    // Set the value
    m_event_queue[m_head] = std::make_tuple(instance, event);

    
    // Update the size
    m_current_size++;


    // Increment the head
    m_head = (m_head+1) % m_max_queue_size;


    // Release the Mutex
    m_mtx.unlock();


    // Increment the pop semaphore
    sem_post( m_pop_semaphore );
    
    
    // Log Exit
    CLI_LOG_CLASS_EXIT();
}

/*****************************/
/*        Pop Command        */
/*****************************/
void An_Event_Queue::Pop_Event( int& instance, 
                                int& event )
{
    // Log Entry
    CLI_LOG_CLASS( trace,
                   "Start of Method. Inst-ID: " + std::to_string(instance) 
                   + ", Event-ID: " + std::to_string(event));
    
    // Decrement the pop semaphore
    if( sem_wait( m_pop_semaphore ) != 0 ){
        std::stringstream sin;
        sin << "sem_wait failed with error. Details: " << strerror(errno) << ", File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__;
        throw std::runtime_error(sin.str());
    }


    // Return if the list is empty
    if( m_close_flag == true ){
        BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
        instance = -1;
        event = (int)CLI_Event_Type::CLI_NULL;
        return; 
    }


    // Lock the mutex
    m_mtx.lock();


    // Get the value
    instance = std::get<0>(m_event_queue[m_tail]);
    event    = std::get<1>(m_event_queue[m_tail]);
    
    // set null
    std::get<0>(m_event_queue[m_tail]) = (int)CLI_Event_Type::CLI_NULL;
    std::get<1>(m_event_queue[m_tail]) = -1;

    
    // Unregister the Event
    Unregister_Event( event );

    // Update the size
    m_current_size--;
    
    // Update the tail
    m_tail = (m_tail+1) % m_max_queue_size;
    
    
    // Unlock the mutex
    m_mtx.unlock();

    
    // Increment the push semaphore
    if( sem_post( m_push_semaphore ) < 0 ){
        std::stringstream sin;
        sin << "sem_push failed with error. Details: " << strerror(errno) << ", File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__;
        throw std::runtime_error(sin.str());
    }
    

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Class: " << m_class_name << ", File: " << __FILE__ << ", Line: " << __LINE__;
    
    // return command
}


/************************************/
/*          Register Event          */
/************************************/
void An_Event_Queue::Register_Event( const int& event_id )
{
    m_active_mutex.lock();

    // Check to see if ID exists
    if( m_active_events.find(event_id) == m_active_events.end() )
    {
        m_active_events[event_id] = 1;
    }
    else{
        m_active_events[event_id]++;
    }

    m_active_mutex.unlock();
}


/**************************************/
/*          Unregister Event          */
/**************************************/
void An_Event_Queue::Unregister_Event( const int& event_id )
{
    m_active_mutex.lock();
    
    if( m_active_events.find(event_id) == m_active_events.end() )
    {
        BOOST_LOG_TRIVIAL(error) << "Attempting to remove event-id (" << event_id << ") despite not being registered.";
        return;
    }

    m_active_events[event_id]--;
    
    m_active_mutex.unlock();
}


} // End of EVT Namespace
} // End of CLI Namespace

