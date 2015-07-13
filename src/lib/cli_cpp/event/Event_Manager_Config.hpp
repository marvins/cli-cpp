/**
 * @file    Event_Manager_Config.hpp
 * @author  Marvin Smith
 * @date    7/3/2015
*/
#ifndef __CLI_CPP_EVENT_EVENT_MANAGER_CONFIG_HPP__
#define __CLI_CPP_EVENT_EVENT_MANAGER_CONFIG_HPP__

// C++ Standard Libraries
#include <string>


namespace CLI{
namespace EVT{

/**
 * @class Event_Manager_Config
*/
class Event_Manager_Config
{
    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] event_queue_max_capacity Number of slots in the event queue for events.  Pushing past this number will block.
         * @param[in] event_work_queue_threads Number of threads to process events in the manager.
        */
        Event_Manager_Config( const int& event_queue_max_capacity = 50,
                              const int& event_work_queue_threads = 2 );


        /**
         * @brief Get the Event Queue Max Capacity.
         *
         * @return Max number of items that can be stored on the work queue.
        */
        inline int Get_Event_Queue_Max_Capacity()const{
            return m_event_queue_max_capacity;
        }


        /**
         * @brief get the Event Work Queue Thread Count.
         *
         * @return Event work queue thread count.
        */
        inline int Get_Event_Work_Queue_Thread_Count()const{
            return m_event_work_queue_threads;
        }


    private:
        
        /// Class Name
        std::string m_class_name;


        /// Number of spaces on the event queue
        int m_event_queue_max_capacity;


        /// Event work queue thread count
        int m_event_work_queue_threads;


}; // End of Event_Manager_Config Class

} // End of EVT Namespace
} // End of CLI Namespace

#endif
