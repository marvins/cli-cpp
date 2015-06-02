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

// CLI Libraries
#include "A_Render_Driver_Context_Base.hpp"
#include "A_Render_State.hpp"
#include "../cmd/A_CLI_Command.hpp"
#include "../cmd/A_Command_History.hpp"
#include "../cmd/A_Command_Result.hpp"
#include "../cmd/A_Command_Parser.hpp"
#include "../cmd/A_Command_Queue.hpp"


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
         */
        A_Render_Manager_Base( CMD::A_Command_Parser const& command_parser );
        

        /**
         * @brief Initialize
        */
        virtual void Initialize() = 0;


        /** 
         * @brief Finalize
        */
        virtual void Finalize() = 0;


        /**
         * @brief Refresh the Screen.
         */
        virtual void Refresh() = 0;
        

        /**
         * @brief Update the rendering driver context.
         *
         * @param[in] driver_context Rendering driver to register.
         */
        virtual void Update_Render_Driver_Context( A_Render_Driver_Context_Base::ptr_t driver_context ) = 0;

        inline virtual void Update_Command_Queue( CMD::A_Command_Queue::ptr_t command_queue ){
            m_command_queue = command_queue;
        }

        
        /**
         * @brief Set the Title
         *
         * @param[in] cli_title
        */
        inline virtual void Set_CLI_Title( const std::string& cli_title )
        {
            m_cli_title = cli_title;
        }


        /**
         * @brief Append Command To History.
         *
         * @param[in] command_string String representing what the user typed in.
         * @param[in] command_result Parsing and evaluation result.
         */
        inline virtual void Add_Command_History( const std::string&            command_string,
                                                 CMD::A_Command_Result::ptr_t  command_result )
        {
            m_command_history->Add_Entry( CMD::A_Command_History_Entry( ++m_command_counter,
                                                                        command_string,
                                                                        command_result ));
        } 


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
         */
        virtual void Process_Keyboard_Input( const int& key );
        

        /**
         * @brief Process the current command text.
        */
        virtual void Process_Command();


    protected:
        
        /// CLI Title
        std::string m_cli_title;
        
        /// Command History
        CMD::A_Command_History::ptr_t m_command_history;


        /// Command Queue
        CMD::A_Command_Queue::ptr_t m_command_queue;


        /// Command Counter
        int m_command_counter;
        
        /// Render State
        A_Render_State::ptr_t m_render_state;
        
        /// Command Parser
        CMD::A_Command_Parser m_command_parser;


    private:

        /// Class Name
        std::string m_class_name;

}; // End of A_Render_Manager Class

} // End of RENDER Namespace
} // End of CLI    Namespace


#endif
