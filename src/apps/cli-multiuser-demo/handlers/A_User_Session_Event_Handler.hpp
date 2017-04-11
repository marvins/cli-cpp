/**
 * @file    A_User_Session_Event_Handler.hpp
 * @author  Marvin Smith
 * @date    10/30/2016
 */
#ifndef __CLI_CPP_APPS_MULTIUSER_DEMO_HANDLERS_A_SESSION_EVENT_HANDLER_HPP__
#define __CLI_CPP_APPS_MULTIUSER_DEMO_HANDLERS_A_SESSION_EVENT_HANDLER_HPP__


// CLI Libraries
#include <cli_cpp/cli/A_Session_Event_Handler_Base.hpp>

// Demo Libraries
#include "../core/State_Manager.hpp"


/**
 * @class A_User_Session_Event_Handler
 */
class A_User_Session_Event_Handler : public CLI::A_Session_Event_Handler_Base 
{
    public:
        
        /**
         * @brief Constructor
         */
        A_User_Session_Event_Handler( State_Manager& state_manager );


        /**
         * @brief Process the Session Info
         */
        virtual void Process_Event( const CLI::CORE::Session_Event& session );

    private:
        
        /// Class Name
        std::string m_class_name;

        /// Internal State Manager
        State_Manager& m_state_manager;

}; // End of A_User_Session_Event_Handler Class



#endif
