/**
 * @file    State_Manager.hpp
 * @author  Marvin Smith
 * @date    10/26/2016
*/
#ifndef __CLI_CPP_APPS_MULTIUSER_CORE_STATE_MANAGER_HPP__
#define __CLI_CPP_APPS_MULTIUSER_CORE_STATE_MANAGER_HPP__

// C++ Standard Libraries
#include <condition_variable>
#include <deque>
#include <mutex>


// Application Libraries
#include <cli_cpp.hpp>


/**
 * @class State_Manager
*/
class State_Manager
{

    public: 

        /**
         * @brief Constructor
        */
        State_Manager();
        

        /**
         * @brief Destructor
        */
        virtual ~State_Manager();
        
        
        /**
         * @brief Get the CLI-Manager
         */
        inline CLI::A_CLI_Manager::ptr_t Get_CLI_Manager()const{
            return m_cli_manager;
        }


        /**
         * @brief Set the CLI-Manager
         */
        inline void Set_CLI_Manager( CLI::A_CLI_Manager::ptr_t cli_manager ){
            m_cli_manager = cli_manager;
        }


        /**
         * @brief Signal System Shutdown
         */
        void Signal_System_Shutdown();


        /**
         * @brief Wait on system shutdown.
         */
        void Wait_On_System_Shutdown();
        

        /**
         * @brief Signal Session Update
         */
        void Notify_Session_Event( const CLI::CORE::Session_Event& event );
        

        /**
         * @brief Get Session Event LIst
         */
        inline std::deque<CLI::CORE::Session_Event> Get_Session_Event_List()const{
            return m_session_events;
        }
        

    private:
        
        /// Shutdown Variables 
        std::mutex               m_shutdown_mutex;
        std::condition_variable  m_shutdown_cv;
    
        /// Shutdown System State
        bool m_shutdown_system;
        
        /// CLI-Manager
        CLI::A_CLI_Manager::ptr_t m_cli_manager;

        /// Session Events
        std::deque<CLI::CORE::Session_Event> m_session_events;

}; // End of State_Manager Class

#endif
