/**
 * @file    A_CLI_Manager.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_A_CLI_MANAGER_HPP__
#define __CLI_A_CLI_MANAGER_HPP__

// CLI Libraries
#include "A_CLI_Manager_Configuration.hpp"
#include "A_Command_Response_Handler_Base.hpp"
#include "A_Session_Event_Handler_Base.hpp"
#include "../cmd/A_Command_Queue.hpp"
#include "../handlers/A_Custom_Window_Command_Response_Handler.hpp"


// C++ Standard Libraries
#include <memory>
#include <thread>

namespace CLI{

/**
 * @class A_CLI_Manager
 *
 * @brief Primary CLI management interface.
 */
class A_CLI_Manager{

    public:

        /// Pointer Type
        typedef std::shared_ptr<A_CLI_Manager> ptr_t;

        
        /**
         * @brief Constructor
         *
         * @param[in] configuration CLI Manager Configuration parameters.
         */
        A_CLI_Manager( const A_CLI_Manager_Configuration& configuration );


        /**
         * @brief Destructor
        */
        ~A_CLI_Manager();

        
        /**
         * @brief Connect the CLI Manager
         */
        void Connect();


        /**
         * @brief Wait for shutdown.
         */
        void Wait_Shutdown();


        /**
         * @brief Disconnect the CLI Manager
         */
        void Disconnect();


        /**
         * @brief Get the CLI Connection Type
         *
         * @return CLI Connection Type.
         */
        inline CORE::ConnectionType Get_Connection_Type()const{
            return m_configuration.Get_Connection_Type();
        }


        /**
         * @brief Register Command Response Handler.
         *
         * @param[in] handler Command-Response Handler to register with the system.
         */
        void Register_Command_Response_Handler( A_Command_Response_Handler_Base::ptr_t handler );
        

        /**
         * @brief Register a Session Response Handler.
         *
         * @param[in] handler Session-Response Handler to register with the system
         */
        void Register_Session_Event_Handler( A_Session_Event_Handler_Base::ptr_t handler );

        
        /**
         * @brief Register Custom Render Window
         *
         * @param[in] render_window   Custom window to register.
         * @param[in] command         Command that will render the window.
        */
        bool Register_Custom_Render_Window( RENDER::An_ASCII_Render_Window_Base::ptr_t  render_window,
                                            CMD::A_Command const&                       command );
        
        
        /**
         * @brief Get list of active sessions.
         *
         * @return List of session instances.
         */
        std::vector<CORE::Session> Get_Active_Session_List()const;


    private:

        /**
         * @brief Process Command Result Messages
        */
        void Process_Command_Results();
        

        /**
         * @brief Register Internal Command Response Handlers.
        */
        void Register_Internal_Command_Response_Handlers();


        /**
         * @brief Register the Internal Event Handlers.
        */
        void Register_Internal_Event_Handlers();
        

        /**
         * @brief Initialize the Connection Manager.
        */
        void Initialize_Connection_Manager();

        
        /// Class Name
        std::string m_class_name;

        
        /// Configuration
        A_CLI_Manager_Configuration m_configuration;

        
        /// CLI Connection Handler
        A_Connection_Manager_Base::ptr_t m_connection_manager;

        
        /// Handler Thread
        std::thread m_handler_thread;
        std::atomic<bool> m_handler_thread_running;

        
        /// Handler Queue
        CMD::A_Command_Queue::ptr_t m_command_queue;

        
        /// CLI Handler List
        std::vector<A_Command_Response_Handler_Base::ptr_t> m_command_handlers;

        /// Custom Window Command Response Handler
        HANDLER::A_Custom_Window_Command_Response_Handler::ptr_t m_custom_window_command_handler;


}; // End of A_CLI_Manager Class

} // End of CLI Namespace

#endif
