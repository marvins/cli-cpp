/**
 * @file    State_Manager.hpp
 * @author  Marvin Smith
 * @date    10/26/2016
*/
#ifndef __CLI_CPP_APPS_MULTIUSER_CORE_STATE_MANAGER_HPP__
#define __CLI_CPP_APPS_MULTIUSER_CORE_STATE_MANAGER_HPP__

// C++ Standard Libraries
#include <condition_variable>
#include <mutex>

// Application Libraries


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

        
    private:
        
        /// Shutdown Variables 
        std::mutex               m_shutdown_mutex;
        std::condition_variable  m_shutdown_cv;
    
        /// Shutdown System State
        bool m_shutdown_system;

}; // End of State_Manager Class

#endif
