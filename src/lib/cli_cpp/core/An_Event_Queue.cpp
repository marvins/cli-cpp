/**
 * @file    An_Event_Queue.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include "An_Event_Queue.hpp"

// CLI Libraries
#include "../utility/Log_Utilities.hpp"


namespace CLI{
namespace CORE{

/******************************/
/*        Constructor         */
/******************************/
An_Event_Queue::An_Event_Queue( const int& max_queue_size )
  : m_event_queue(new int[max_queue_size] ),
    m_head(0),
    m_tail(0),
    m_max_queue_size(max_queue_size),
    m_close_flag(false),
    m_current_size(0)
{
    // Initialize the semaphores
    sem_init( &m_push_semaphore, 0, max_queue_size);
    sem_init( &m_pop_semaphore, 0, 0);

    // Initialize array values
    for( int i=0; i<m_max_queue_size; i++ ){
        m_event_queue[i] = (int)CLI_Event_Type::CLI_NULL;
    }
}


/*********************************/
/*          Destructor           */
/*********************************/
An_Event_Queue::~An_Event_Queue()
{
    // Delete the queue
    delete [] m_event_queue;

    // Set to null
    m_event_queue = nullptr;
}


/**************************/
/*         Clear          */
/**************************/
void An_Event_Queue::Clear()
{
    // Set close flag
    m_close_flag = true;

    // Increment all semaphores
    sem_post( &m_push_semaphore );
    sem_post( &m_pop_semaphore );

}


/*****************************/
/*        Push Command       */
/*****************************/
void An_Event_Queue::Push_Event( int const& event )
{
    // Decrement the push semaphore
    sem_wait( &m_push_semaphore );

    
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
    sem_post( &m_pop_semaphore );
}

/*****************************/
/*        Pop Command        */
/*****************************/
int An_Event_Queue::Pop_Event()
{
    
    // Output
    int event;


    // Decrement the pop semaphore
    sem_wait( &m_pop_semaphore );


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
    sem_post( &m_push_semaphore );
    
    
    // return command
    return event;
}

} // End of CORE Namespace
} // End of CLI  Namespace

