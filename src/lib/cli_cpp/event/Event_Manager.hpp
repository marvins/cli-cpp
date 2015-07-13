/**
 * @file    Event_Manager.hpp
 * @author  Marvin Smith
 * @date    5/30/2015
 */
#ifndef __CLI_CPP_LIB_CORE_EVENT_MANAGER_HPP__
#define __CLI_CPP_LIB_CORE_EVENT_MANAGER_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>
#include <thread>
#include <vector>


// CLI Libraries
#include "../core/CLI_Event_Type.hpp"
#include "A_CLI_Event_Handler_Base.hpp"
#include "An_Event_Queue.hpp"
#include "Event_Manager_Config.hpp"


namespace CLI{
namespace EVT{

/**
 *  @class Event_Manager
 */
class Event_Manager{

    public:
        
        
        /**
         * @brief Destructor
        */
        ~Event_Manager();


        /**
         * @brief Initialize the Event Manager.
         *
         * @param[in] event_queue_max_capacity Max number of messages to wait in the event queue.
         * @param[in] event_work_queue_threads Number of threads to process jobs on the work queue.
         */
        static void Initialize( Event_Manager_Config const& config );


        /**
         * @brief Finalize the Event Manager
        */
        static void Finalize();

        
        /**
         * @brief Check if initialized.
         *
         * @return True if initialized, false otherwise.
        */
        static bool Is_Initialized();


        /**
         * @brief Register CLI Event Handler.
         *
         * @param[in] handler Event handler to process commands.
         */
        static void Register_CLI_Event_Handler( A_CLI_Event_Handler_Base::ptr_t handler );
        

        /**
         * @brief Process_Event
         *
         * @param[in] instance Which client the event originated from.
         * @param[in] event Event ID.  For keyboard entries, this is the ascii value, for CLI Commands, this is < -2. Check CLI_Event_Type class for more info.
        */
        static void Process_Event( const int& instance, 
                                   const int& event );

    private:

        /// Pointer Type
        typedef std::shared_ptr<Event_Manager> ptr_t;


        /**
         * @brief Constructor
         *
         * @param[in] event_queue_max_capacity Max size of the event queue.
         * @param[in] event_work_queue_threads Number of threads to process jobs.
         */
        Event_Manager( Event_Manager_Config const& config );
        
        
        /**
         * @brief Get Instance of the event manager.
         *
         * @return Event_Manager global singleton instance.
        */
        static Event_Manager::ptr_t Instance_Of();


        /** 
         * @brief Event process thread runner.
         *
         * @param[in] thread_id ID of the particular thread for indexing specific resources.
         */
        void Event_Process_Runner( const int& thread_id );


        /// Class Name
        std::string m_class_name;
        

        /// Configuration
        Event_Manager_Config m_config;


        /// List of event handlers
        std::vector<A_CLI_Event_Handler_Base::ptr_t> m_event_handlers;
        

        /// Event Manager Queue
        An_Event_Queue::ptr_t m_event_queue;

        
        /// Process thread
        std::vector<std::thread>  m_event_process_threads;

        
        // Running flag
        std::vector<bool> m_is_running;
        

        // Initialized 
        std::atomic<bool> m_is_initialized;

}; // End of Event_Manager Class

} // End of EVT Namespace
} // End of CLI Namespace

#endif
