/**
 * @file    An_Event_Queue.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_CORE_AN_EVENT_QUEUE_HPP__
#define __CLI_CPP_CORE_AN_EVENT_QUEUE_HPP__

// C++ Standard Libraries
#include <atomic>
#include <memory>
#include <mutex>
#include <semaphore.h>

// CLI Libraries
#include "../core/CLI_Event_Type.hpp"


namespace CLI{
namespace EVT{

/**
 * @class An_Event_Queue
*/
class An_Event_Queue
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<An_Event_Queue> ptr_t;


        /**
         * @brief Constructor
         *
         * @param[in] max_queue_size Max number of elements in the queue before blocking.
        */
        An_Event_Queue( const int& max_queue_size );
        

        /**
         * @brief Destructor
        */
        ~An_Event_Queue();

        
        /**
         * @brief Add Event to Queue.
         *
         * @param[in] event Event to push onto the queue.
         */
        void Push_Event( int const& event );


        /**
         * @brief Pop Event
         *
         * @return Next event on the queue.  If queue is empty, it will block.
         */
        int Pop_Event();


        /**
         * @brief Clear the Semaphore
        */
        void Clear();


        /**
         * @brief Get the queue count.
         *
         * @return Current size.
        */
        inline int Get_Current_Size()const{
            return m_current_size;
        }


        /**
         * @brief Get the max queue size.
         *
         * @return Max queue size.
        */
        inline int Get_Max_Size()const{
            return m_max_queue_size;
        }


    private:
        
        /// Event Queue
        int* m_event_queue;
    
        /// Main Mutex
        std::mutex m_mtx;

        /// Counters
        sem_t* m_push_semaphore;
        sem_t* m_pop_semaphore;

        /// Head and Tail Cursors
        int m_head;
        int m_tail;

        /// Max Queue Size
        int m_max_queue_size;

        /// Close Flag
        std::atomic<bool> m_close_flag;


        /// Current size
        int m_current_size;

}; // End of An_Event_Queue Class

} // End of EVT Namespace
} // End of CLI Namespace

#endif
