/**
 * @file    A_Render_State.hpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#ifndef __CLI_CPP_CLI_A_RENDER_STATE_HPP__
#define __CLI_CPP_CLI_A_RENDER_STATE_HPP__

// C++ Standard Libraries
#include <atomic>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>


// CLI Libraries
#include "../core/ConnectionType.hpp"
#include "../cmd/A_Command_History.hpp"
#include "../cmd/A_Command_Parser.hpp"
#include "../cmd/A_Command_Result.hpp"


namespace CLI{
namespace RENDER{


/**
 * @class A_Render_State
 */
class A_Render_State{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Render_State> ptr_t;


        /**
         * @brief Constructor
         * 
         * @param[in] command_parser Parser for auto-complete.
         */
        A_Render_State( CMD::A_Command_Parser::ptr_t   command_parser );
        
        
        /**
         * @brief Destructor
        */
        ~A_Render_State();

        
        /**
         * @brief Get the Cursor Position.
         *
         * @return Cursor position.
         */
        inline virtual int Get_Cursor_Pos()const{
            return m_cli_prompt_cursor_at;
        }


        /**
         * @brief Get the cursor text.
         *
         * @return Cursor text.
         */
        inline std::string Get_Cursor_Text()const{
            return m_cli_prompt_text.substr(m_cli_prompt_cursor_tail,
                                            m_cli_prompt_cursor_head - m_cli_prompt_cursor_tail);
        }


        /**
         * @brief Clear the cursor text.
         */
        void Clear_Cursor_Text();

        
        /**
         * @brief Add Text
         */
        virtual void Process_Input( const int& input );
   
        
        /**
         * @brief Process CLI Command
         *
         * @param[in] command Command to process.
         */
        void Process_Command_Result( CMD::A_Command_Result const& result );
        

        /**
         * @brief Active Command Queue Size
         *
         * @return Active command queue size.
        */
        inline int Get_Active_Command_Queue_Size()const{
            return m_active_command_queue.size();
        }


        /**
         * @brief Load the next active command.
        */
        inline void Load_Next_Active_Command()
        {
        
            // Clear cursor text
            Clear_Cursor_Text();
            
            // Update the cursor text
            m_cli_prompt_text = m_active_command_queue[0];
        
            // Update the pointers
            m_cli_prompt_cursor_at = m_cli_prompt_text.size();
            m_cli_prompt_cursor_tail = 0;
            m_cli_prompt_cursor_head = m_cli_prompt_text.size();
            
            // Remove the active command
            m_active_command_queue.pop_front();
        }


        /**
         * @brief Check the sleep mode
         *
         * @return True if sleeping, false otherwise.
        */
        bool Get_Sleep_Mode()const;


        /**
         * @brief Get the CLI Pause Mode Status
         *
         * @return True if waiting for user input, false otherwise.
        */
        bool Get_Pause_Mode()const;

        
        /**
         * @brief Reset the CLI Pause Mode
         */
        void Reset_Pause_Mode();
       

        /**
         * @brief Get the Command-History Object.
         *
         * @return Command-History.
        */
        inline CMD::A_Command_History::ptr_t Get_Command_History()const{
            return m_command_history;
        }


        /**
         * @brief Add a Command to the Command History.
         *
         * @param[in] cli_text CLI text to add to the history
         * @param[in] command_result Command to tie to text.
        */
        inline void Add_Command_History( const std::string& cli_text,
                                         const CMD::A_Command_Result::ptr_t command_result )
        {
            // Add to history
            m_command_history->Add_Entry( CMD::A_Command_History_Entry( m_command_history->Size(),
                                                                        cli_text,
                                                                        command_result ));
        }

        
    private:

        /**
         * @brief Add Backspace
         */
        void Apply_Backspace();
        

        /**
         * @brief Apply Delete
         */
        void Apply_Delete();
        

        /**
         * @brief Apply Left Key
        */
        void Apply_Left_Key();


        /**
         * @brief Apply Right Key
        */
        void Apply_Right_Key();


        /**
         * @brief Apply the Up Key.
         */
        void Apply_Up_Key();


        /**
         * @brief Apply the Down Key
         */
        void Apply_Down_Key();

        
        /**
         * @brief Apply the Tab Key
        */
        void Apply_Tab_Key();


        /**
         * @brief Check if input is text.
         *
         * @param[in] input
         *
         * @return True if text, false otherwise.
        */
        bool Is_Text( const int& input )const; 


        /**
         * @brief Run sleep mode 
         *
         * @param[in] sleep_seconds Number of seconds to sleep.
         */
        void Run_Sleep_Mode( const double sleep_seconds );



        /// CLI Text
        std::string m_cli_prompt_text;


        /// CLI Cursor Position
        int m_cli_prompt_cursor_head;


        /// CLI Cursor Position
        int m_cli_prompt_cursor_tail;
        int m_cli_prompt_cursor_at;


        /// Reference to Command History
        CMD::A_Command_History::ptr_t m_command_history;


        /// Reference to Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;


        /// Current History Index
        int m_command_history_ptr;


        /// Active Command Queue
        std::deque<std::string> m_active_command_queue;

        /// Sleep Mode
        std::atomic<bool> m_sleep_mode;


        /// Sleep Mode Thread
        std::thread m_sleep_mode_thread;


        /// Waiting User Key
        bool m_waiting_user_input;


}; // End of A_Render_State Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
