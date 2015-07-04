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
#include <sstream>

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
    BOOST_LOG_TRIVIAL(trace) << "Start of " << m_class_name << "::" << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    
    // Create the queue
    if( max_queue_size < 1 ){
        throw std::runtime_error("Size cannot be less than 1.");
    }
    m_event_queue = new int[max_queue_size];
    
    
    // Initialize the semaphores
    if( (m_pop_semaphore = sem_open("/pop_semaphore", O_CREAT, 0666, 0)) == SEM_FAILED ){
        sem_close(m_pop_semaphore);
        sem_unlink("/pop_semaphore");
        throw std::runtime_error(std::string("Unable to initialize pop semaphore. Details: ") + strerror(errno));
    }
    
    if( (m_push_semaphore = sem_open("/push_semaphore", O_CREAT, 0666, max_queue_size)) == SEM_FAILED ){
        sem_close(m_push_semaphore);
        sem_unlink("/push_semaphore");
        throw std::runtime_error(std::string("Unable to initialize push semaphore. Details: ") + strerror(errno));
    }

    
    // Initialize array values
    for( int i=0; i<m_max_queue_size; i++ ){
        m_event_queue[i] = (int)CLI_Event_Type::CLI_NULL;
    }


    // Set the current size
    m_current_size = 0;
    
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
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

    // Close semaphores
    sem_close( m_pop_semaphore );
    sem_close( m_push_semaphore );
    
    // Unlink the semaphores
    sem_unlink("/pop_semaphore");
    sem_unlink("/push_semaphore");

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/**************************/
/*         Clear          */
/**************************/
void An_Event_Queue::Clear()
{
    // Set close flag
    m_close_flag = true;

    // Increment all semaphores
    sem_post( m_push_semaphore );
    sem_post( m_pop_semaphore );

}


/*****************************/
/*        Push Command       */
/*****************************/
void An_Event_Queue::Push_Event( int const& event )
{
    // Decrement the push semaphore
    if( sem_wait( m_push_semaphore ) < 0 ){
        std::stringstream sin;
        sin << "Error with semaphore.";
        throw std::runtime_error(sin.str());   
    }

    
    // Lock the mutex
    m_mtx.lock();

    
    // Set the value
    m_event_queue[m_head] = event;

    
    // Update the size
    m_current_size++;


    // Increment the head
    m_head = (m_head+1) % m_max_queue_size;


    // Release the Mutex
    m_mtx.unlock();


    // Increment the pop semaphore
    sem_post( m_pop_semaphore );
}

/*****************************/
/*        Pop Command        */
/*****************************/
int An_Event_Queue::Pop_Event()
{
    
    // Output
    int event;


    // Decrement the pop semaphore
    if( sem_wait( m_pop_semaphore ) != 0 ){
        std::stringstream sin;
        sin << "sem_wait failed with error. Details: " << strerror(errno) << ", File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__;
        throw std::runtime_error(sin.str());
    }


    // Return if the list is empty
    if( m_close_flag == true ){
        BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
        return (int)CLI_Event_Type::CLI_NULL;
    }


    // Lock the mutex
    m_mtx.lock();


    // Get the value
    event = m_event_queue[m_tail];
    m_event_queue[m_tail] = (int)CLI_Event_Type::CLI_NULL;

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
    
    
    // return command
    return event;
}

} // End of EVT Namespace
} // End of CLI Namespace

