/**
 * @file    An_Event_Queue.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_CORE_AN_EVENT_QUEUE_HPP__
#define __CLI_CPP_CORE_AN_EVENT_QUEUE_HPP__

// C++ Standard Libraries
#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <semaphore.h>
#include <string>
#include <tuple>

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
         * @param[in] id    ID of the connection.
         * @param[in] event Event to push onto the queue.
         * @param[in] filter Flag if we should filter if the flag already exists.
         */
        void Push_Event( const int&  id,
                         const int&  event,
                         const bool& filter = false );


        /**
         * @brief Pop Event
         *
         * @return Next event on the queue.  If queue is empty, it will block.
         */
        void Pop_Event( int& id, 
                        int& event );


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


        /**
         * @brief Has Event
         *
         * @param[in] event_id
         *
         * @return True if event inside, false otherwise.
        */
        inline bool Has_Event( const int& event_id )const
        {
            return (m_active_events.find(event_id) != m_active_events.end() &&
                    m_active_events.find(event_id)->second > 0 );
        }


        /**
         * @brief Register Event
         *
         * @param[in] event_id
        */
        void Register_Event( const int& event_id );


        /**
         * @brief Unregister Event
         *
         * @param[in] event_id
        */
        void Unregister_Event( const int& event_id );


        /// Class Name
        std::string m_class_name;
        
        /// Event Queue
        std::tuple<int,int>* m_event_queue;
    
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

        /// Active Events
        std::map<int,int> m_active_events;
        std::mutex        m_active_mutex;

}; // End of An_Event_Queue Class

} // End of EVT Namespace
} // End of CLI Namespace

#endif
