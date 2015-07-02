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
         *
         * @param[in] command_parser Command parser to process cli results.
         */
        A_Render_Manager_Base( CMD::A_Command_Parser::ptr_t command_parser );
        

        /**
         * @brief Initialize
        */
        virtual void Initialize() = 0;


        /** 
         * @brief Finalize
        */
        virtual void Finalize() = 0;

        
        /**
         * @brief Get the render state.
         *
         * @return Render state.
         */
        inline virtual A_Render_State::ptr_t Get_Render_State()const{
            return m_render_state;
        }

        
        /**
         * @brief Refresh the Screen.
         */
        virtual void Refresh() = 0;
        

        /**
         * @brief Update the rendering driver context.
         *
         * @param[in] driver_context Rendering driver to register.
         */
        virtual void Update_Render_Driver_Context( A_Render_Driver_Context_Base::ptr_t driver_context ){
            m_render_driver_context = driver_context;
        }


        /**
         * @brief Update the Command Queue Pointer.
         *
         * @param[in] command_queue Command queue to refer to.
         */
        inline virtual void Update_Command_Queue( CMD::A_Command_Queue::ptr_t command_queue ){
            m_command_queue = command_queue;
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



    protected:

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

        
        /// Command History
        CMD::A_Command_History::ptr_t m_command_history;


        /// Command Queue
        CMD::A_Command_Queue::ptr_t m_command_queue;


        /// Command Counter
        int m_command_counter;
        
        
        /// Render State
        A_Render_State::ptr_t m_render_state;
        

        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;

        
        /// Render Driver Context
        A_Render_Driver_Context_Base::ptr_t m_render_driver_context;


    private:

        /// Class Name
        std::string m_class_name;
        
        

}; // End of A_Render_Manager Class

} // End of RENDER Namespace
} // End of CLI    Namespace


#endif
