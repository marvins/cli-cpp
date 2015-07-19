/**
 * @file    A_Command_Queue.cpp
 * @author  Marvin Smith
 * @date    5/19/2015
*/
#include "A_Command_Queue.hpp"

// CLI Libraries
#include "../utility/Log_Utilities.hpp"


namespace CLI{
namespace CMD{

/******************************/
/*        Constructor         */
/******************************/
A_Command_Queue::A_Command_Queue( const A_Command_Queue_Config& configuration )
  : m_class_name("A_Command_Queue"),
    m_configuration(configuration),
    m_command_queue(new A_Command_Result::ptr_t[configuration.Get_Max_Queue_Size()] ),
    m_head(0),
    m_tail(0),
    m_close_flag(false)
{

    // Initialize the semaphores
#ifdef __APPLE__

    // Unlink each
    sem_unlink("/command_queue_push_semaphore");
    sem_unlink("/command_queue_pop_semaphore");

    // Open each semaphore
    if( (m_push_semaphore = sem_open("/command_queue_push_semaphore", O_CREAT | O_EXCL, 0666, m_configuration.Get_Max_Queue_Size())) == SEM_FAILED ){
        sem_close(m_pop_semaphore);
        sem_unlink("/command_queue_push_semaphore");
        throw std::runtime_error(std::string("Unable to initialize push semaphore. Details: ") + strerror(errno));
    }
    if( (m_pop_semaphore = sem_open("/command_queue_pop_semaphore", O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED ){
        sem_close(m_pop_semaphore);
        sem_unlink("/command_queue_pop_semaphore");
        throw std::runtime_error(std::string("Unable to initialize pop semaphore. Details: ") + strerror(errno));
    }
#else
    m_push_semaphore = new sem_t;
    m_pop_semaphore = new sem_t;
    
    if( sem_init( &m_push_semaphore, 0, m_configuration.Get_Max_Queue_Size()) != 0 ){
        throw std::runtime_error(std::string("Unable to initialize push semaphore. Details: ") + strerror(errno));
    }
    if( sem_init( &m_pop_semaphore, 0, 0) != 0 ){
        throw std::runtime_error(std::string("Unable to initialize pop semaphore. Details: ") + strerror(errno));
    }
#endif
    
    // Initialize array values
    for( int i=0; i<m_configuration.Get_Max_Queue_Size(); i++ ){
        m_command_queue[i] = nullptr;
    }
}


/*********************************/
/*          Destructor           */
/*********************************/
A_Command_Queue::~A_Command_Queue()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    

    // Delete the queue
    delete [] m_command_queue;

    // Set to null
    m_command_queue = nullptr;

#ifdef __APPLE__
    // Close semaphores
    sem_close( m_pop_semaphore );
    sem_close( m_push_semaphore );
    
    // Unlink the semaphores
    sem_unlink("/command_queue_pop_semaphore");
    sem_unlink("/command_queue_push_semaphore");
    
#else
    if( m_push_semaphore != nullptr &&
        m_push_semaphore != NULL )
    {
        delete m_push_semaphore;
    }
    if( m_pop_semaphore != nullptr &&
        m_pop_semaphore != NULL )
    {
        delete m_pop_semaphore;
    }
#endif
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
}


/**************************/
/*         Clear          */
/**************************/
void A_Command_Queue::Clear()
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
void A_Command_Queue::Push_Command( A_Command_Result::ptr_t const& command )
{
    // Decrement the push semaphore
    sem_wait( m_push_semaphore );

    // Lock the mutex
    m_mtx.lock();

    // Set the value
    m_command_queue[m_head] = command;

    // Increment the head
    m_head = (m_head+1) % m_configuration.Get_Max_Queue_Size();

    // Release the Mutex
    m_mtx.unlock();

    // Increment the pop semaphore
    sem_post( m_pop_semaphore );
}

/*****************************/
/*        Pop Command        */
/*****************************/
A_Command_Result::ptr_t A_Command_Queue::Pop_Command()
{
    // Log Entry
    //BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Output
    A_Command_Result::ptr_t  command;

    // Decrement the pop semaphore
    sem_wait( m_pop_semaphore );
    
    // Return if the list is empty
    if( m_close_flag == true ){
        BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
        return nullptr;
    }

    // Lock the mutex
    m_mtx.lock();
    
    // Get the value
    command = m_command_queue[m_tail];
    m_command_queue[m_tail] = nullptr;

    // Update the tail
    m_tail = (m_tail+1) % m_configuration.Get_Max_Queue_Size();
    
    // Unlock the mutex
    m_mtx.unlock();

    // Increment the push semaphore
    sem_post( m_push_semaphore );
    
    // Log Exit
    //BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // return command
    return command;
}

} // End of CMD Namespace
} // End of CLI Namespace

