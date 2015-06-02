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
#include <vector>


// CLI Libraries
#include "A_CLI_Event_Handler_Base.hpp"
#include "CLI_Event_Type.hpp"


namespace CLI{
namespace CORE{

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
         * @brief Initialize the Event Manager
         */
        static void Initialize();


        /**
         * @brief Register CLI Event Handler.
         *
         * @param[in] handler Event handler to process commands.
         */
        static void Register_CLI_Event_Handler( A_CLI_Event_Handler_Base::ptr_t handler );
        

        /**
         * @brief Process_Event
         *
         * @param[in] event Event ID.  For keyboard entries, this is the ascii value, for CLI Commands, this is < -2. Check CLI_Event_Type class for more info.
        */
        static void Process_Event( const int& event );

    private:

        /// Pointer Type
        typedef std::shared_ptr<Event_Manager> ptr_t;


        /**
         * @brief Constructor
         */
        Event_Manager();

        
        /**
         * @brief Start Thread
         */
        void Run();


        /**
         * @brief Get Instance
        */
        static Event_Manager::ptr_t Instance_Of();


        /// Class Name
        std::string m_class_name;


        /// List of event handlers
        std::vector<A_CLI_Event_Handler_Base::ptr_t> m_event_handlers;

}; // End of Event_Manager Class

} // End of CORE Namespace
} // End of CLI  Namespace

#endif
