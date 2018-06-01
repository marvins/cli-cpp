/**
 * @file    A_Connection_Manager_Base.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_CPP_CLI_A_CONNECTION_MANAGER_BASE_HPP__
#define __CLI_CPP_CLI_A_CONNECTION_MANAGER_BASE_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>
#include <thread>

// CLI Libraries
#include "../cmd/A_Command_Queue.hpp"
#include "../cmd/A_Command_Parser.hpp"
#include "../core/A_Session.hpp"
#include "A_Connection_Manager_Base_Config.hpp"


namespace CLI{

/**
 * @class A_Connection_Manager_Base
*/
class A_Connection_Manager_Base{

    public:
        
        /// Pointer type
        typedef std::shared_ptr<A_Connection_Manager_Base> ptr_t;


        /**
         * @brief Default Constructor
         *
         * @param[in] configuration Connection-Manager Configuration items.
         */
        A_Connection_Manager_Base( A_Connection_Manager_Base_Config::ptr_t configuration );


        /**
         * @brief Destructor
        */
        virtual ~A_Connection_Manager_Base();

        
        /**
         * @brief Start the handler
         */
        virtual void Start_Handler();


        /**
         * @brief Stop the handler
         */
        virtual void Signal_Shutdown();

        
        /**
         * @brief Wait for shutdown
         */
        virtual void Wait_Shutdown();


        /**
         * @brief Set the Is Connection Flag
         *
         * @param[in] instance_id Instance to set flag for.
         * @param[in] is_connected Flag to set.
        */
        virtual void Set_Is_Connected_Flag( int instance_id,
                                            bool is_connected ) = 0;


        /**
         * @brief Refresh the screen.
         *
         * @param[in] instance Client instance to refresh.
         */
        virtual void Refresh_Screen( int instance ) = 0;


        /**
         * @brief Refresh all Instances
        */
        virtual void Refresh_Screens() = 0;
        

        /**
         * @brief Get a list of active connections.
         *
         * @return session list.
         */
        virtual std::vector<CORE::Session> Get_Active_Session_List()const = 0;


        /**
         * @brief Print to Logging String
         */
        virtual std::string To_Log_String( int offset )const = 0;

    protected:
        
        /**
         * @brief Run the handler
         */
        virtual void Run_Handler() = 0;


        /// Running Flag
        bool m_is_running;


        /// CLI Command Parser
        CMD::A_Command_Parser::ptr_t  m_command_parser;

        
        /// CLI Command Queue
        CMD::A_Command_Queue::ptr_t    m_command_queue;

    private:
        
        /// Class Name
        std::string m_class_name;
        
        /// Configuration 
        A_Connection_Manager_Base_Config::ptr_t m_configuration;

        /// Thread
        std::thread m_connection_thread;

}; // End of A_Connection_Manager_Base Class

} // End of CLI Namespace

#endif
