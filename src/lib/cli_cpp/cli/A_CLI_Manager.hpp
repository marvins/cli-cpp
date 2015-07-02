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
#include "../cmd/A_Command_Queue.hpp"
#include "../render/A_Render_Driver_Context_Base.hpp"
#include "../render/A_Render_Manager_Base.hpp"


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
         */
        void Register_Command_Response_Handler( A_Command_Response_Handler_Base::ptr_t handler );

    private:

        /**
         * @brief Process Command Result Messages
        */
        void Process_Command_Results();
        

        /**
         * @brief Register Internal Command Response Handlers.
        */
        void Register_Internal_Command_Response_Handlers();

        
        /// Class Name
        std::string m_class_name;

        
        /// Configuration
        A_CLI_Manager_Configuration m_configuration;

        
        /// CLI Connection Handler
        A_Connection_Manager_Base::ptr_t m_connection_manager;

        
        /// Render Manager
        RENDER::A_Render_Manager_Base::ptr_t m_render_manager;

        
        /// Handler Thread
        std::thread m_handler_thread;
        std::atomic<bool> m_handler_thread_running;

        
        /// Handler Queue
        CMD::A_Command_Queue::ptr_t m_command_queue;

        
        /// CLI Handler List
        std::vector<A_Command_Response_Handler_Base::ptr_t> m_command_handlers;


}; // End of A_CLI_Manager Class

} // End of CLI Namespace

#endif
