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
#include "../render/A_Render_Manager_Base.hpp"

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
         */
        A_Connection_Manager_Base();


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
         * @brief Update the Registered Rendering Manager
         *
         * @param[in] render_manager Rendering manager to attach.
         */
        inline virtual void Update_Render_Manager( RENDER::A_Render_Manager_Base::ptr_t render_manager )
        {
            m_render_manager = render_manager;
            m_render_state = m_render_manager->Get_Render_State();
        }


        /**
         * @brief Update the Registered Command Parser.
         *
         * @param[in] command_parser Parser to attach to connection manager.
         */
        inline virtual void Update_Command_Parser( CMD::A_Command_Parser::ptr_t command_parser )
        {
            m_command_parser = command_parser;
        }
        

        /**
         * @brief Update the Command Queue
         *
         * @param[in] command_queue Command queue to attach to connection manager.
        */
        inline virtual void Update_Command_Queue( CMD::A_Command_Queue::ptr_t command_queue )
        {
            m_command_queue = command_queue;
        }


    protected:
        
        /**
         * @brief Process the argument
         */
        virtual void Process_Command();
        

        /**
         * @brief Run the handler
         */
        virtual void Run_Handler() = 0;


        /// Running Flag
        bool m_is_running;


        /// Connected Flag
        bool m_is_connected;


        /// Render Manager
        RENDER::A_Render_Manager_Base::ptr_t m_render_manager;

        
        /// Current Render State
        RENDER::A_Render_State::ptr_t m_render_state;

        /// CLI Command Parser
        CMD::A_Command_Parser::ptr_t  m_command_parser;

        /// CLI Command Queue
        CMD::A_Command_Queue::ptr_t    m_command_queue;

    private:
        
        /// Class Name
        std::string m_class_name;

        /// Thread
        std::thread m_connection_thread;

}; // End of A_Connection_Manager_Base Class

} // End of CLI Namespace

#endif
