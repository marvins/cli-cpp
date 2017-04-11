/**
 * @file    State_Manager.hpp
 * @author  Marvin Smith
 * @date    6/2/2015
*/
#ifndef __CLI_CPP_APP_CORE_STATE_MANAGER_HPP__
#define __CLI_CPP_APP_CORE_STATE_MANAGER_HPP__

// C++ Standard Libraries
#include <condition_variable>
#include <mutex>

// Application Libraries
#include "../utils/Network_Scanner.hpp"


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
        ~State_Manager();

        
        /**
         * @brief Signal System Shutdown
         */
        void Signal_System_Shutdown();


        /**
         * @brief Wait on system shutdown.
         */
        void Wait_On_System_Shutdown();

        
        /**
         * @brief Get the network scanner.
        */
        inline Network_Scanner::ptr_t Get_Network_Scanner(){
            return m_network_scanner;
        }
    
    private:
        
        /// Shutdown Variables 
        std::mutex               m_shutdown_mutex;
        std::condition_variable  m_shutdown_cv;
    
        /// Shutdown System State
        bool m_shutdown_system;

        /// Network Scanner
        Network_Scanner::ptr_t m_network_scanner;

}; // End of State_Manager Class

#endif
