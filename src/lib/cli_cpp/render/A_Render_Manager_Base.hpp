/**
 * @file    A_Render_Manager_Base.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_CPP_RENDER_A_RENDER_MANAGER_BASE_HPP__
#define __CLI_CPP_RENDER_A_RENDER_MANAGER_BASE_HPP__

// C++ Standard Libraries
#include <deque>
#include <memory>
#include <string>
#include <thread>


// CLI Libraries
#include "A_Render_Driver_Context_Base.hpp"
#include "A_Render_State.hpp"
#include "../cmd/A_CLI_Command.hpp"
#include "../cmd/A_Command_History.hpp"
#include "../cmd/A_Command_Result.hpp"
#include "../cmd/A_Command_Parser.hpp"
#include "../cmd/A_Command_Queue.hpp"
#include "../render/ascii/An_ASCII_Render_Window_Base.hpp"


namespace CLI{
namespace RENDER{


/**
 * @class A_Render_Manager_Base.
 *
 * @brief Contains the basic elements required to render CLI windows.
 */
class A_Render_Manager_Base
{

    public:


        /// Pointer Type
        typedef std::shared_ptr<A_Render_Manager_Base> ptr_t;


        /**
         * @brief Constructor
         *
         * @param[in] instance_id    ID to load into the manager.
         * @param[in] command_parser Command parser to process cli results.
         */
        A_Render_Manager_Base( int                           instance_id,
                               CORE::SessionType             session_type,
                               CMD::A_Command_Parser::ptr_t  command_parser,
                               CMD::A_Command_Queue::ptr_t   command_queue );


        /**
         * @brief Initialize the Render-Manager
        */
        virtual void Initialize() = 0;


        /**
         * @brief Finalize the Render-Manager.
        */
        virtual void Finalize() = 0;


        /**
         * @brief Command the system to wait on the input command response.
         */
        virtual void Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response ) = 0;


        /**
         * @brief Get the waiting status
         *
         * @return True if waiting on command result response.
         */
        virtual bool Check_Waiting_Command_Response() = 0;


        /**
         * @brief Process Keyboard Input
         *
         * @param[in] key Input key to handle.
         */
        virtual void Process_Keyboard_Input( const int& key );


        /**
         * @brief Process the current command text.
        */
        virtual void Process_Command();


        /**
         * @brief Set the Current Window
        */
        virtual void Set_Current_Window( const int& window_id ) = 0;


        /**
         * @brief Set the CLI Window Size
         *
         * @param[in] rows CLI Window Rows.
         * @param[in] cols CLI Window Cols.
         */
        virtual void Set_CLI_Window_Size( const int& rows,
                                          const int& cols );


        /**
         * @brief Set the window to the appropriate Detailed Help ID.
         *
         * @param[in] command_name
        */
        virtual bool Set_CLI_Detailed_Help_Window( const std::string& command_name ) = 0;


        /**
         * @brief Add a Custom Render Window.
         *
         * @param[in] render_window Render window to add.
         *
         * @return ID of the window.
        */
        virtual int Register_Custom_Render_Window( An_ASCII_Render_Window_Base::ptr_t render_window ) = 0;


        /**
         * @brief Find a Window-ID by a requested trigger command.
         *
         * @param[in] command  Command to query against.
         *
         * @return Window-ID.  -1 if no matching window found.
         */
        virtual int Find_Window_ID_By_Trigger_Command( const CMD::A_Command& command )const = 0;


        /**
         * Send an Asynchronous Message.
         *
         * @param[in] topic_name
         * @param[in] message
        */
        virtual void Send_Asynchronous_Message( const std::string& topic_name,
                                                const std::string& message ) = 0;

    protected:


        /**
         * @brief Refresh the Screen.
         */
        virtual void Refresh() = 0;



        /**
         * @brief Get the header status bar text.
         *
         * @return Header status bar text.
        */
        virtual std::string Get_Header_Status_Bar_Text()const = 0;


        /**
         * @brief Get the header mode bar text.
         *
         * @return Header mode bar text.
        */
        virtual std::string Get_Header_Mode_Bar_Text()const = 0;

        
        /// Session-Type
        CORE::SessionType m_session_type;

        /// Command Queue
        CMD::A_Command_Queue::ptr_t m_command_queue;


        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;


        /// Render Driver Context
        A_Render_Driver_Context_Base::ptr_t m_render_driver_context;


        /// Local Render State
        A_Render_State::ptr_t m_render_state;


        /// Instance ID
        int m_instance_id;

    private:

        /// Class Name
        std::string m_class_name;


}; // End of A_Render_Manager Class

} // End of RENDER Namespace
} // End of CLI    Namespace


#endif
