/**
 * @file    A_Render_State.hpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#ifndef __CLI_CPP_CLI_A_RENDER_STATE_HPP__
#define __CLI_CPP_CLI_A_RENDER_STATE_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>


// CLI Libraries
#include "../core/ConnectionType.hpp"
#include "../cmd/A_Command_History.hpp"
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
         * @param[in] conn_type Connection type.
         * @param[in] command_history History of commands.
         */
        A_Render_State( CORE::ConnectionType const&    conn_type,
                        CMD::A_Command_History::ptr_t  command_history );

        
        /**
         * @brief Get the rows.
         *
         * @return Number of rows.
         */
        inline virtual int Get_Rows()const{
            return m_window_rows;
        }


        /**
         * @brief Number of columns.
         *
         * @return Number of columns.
         */
        inline virtual int Get_Cols()const{
            return m_window_cols;
        }


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
         * @brief Set Window Size
         */
        virtual void Set_Window_Size( const int& rows,
                                      const int& cols );

        
        /**
         * @brief Set the help mode
         */
        inline void Set_Help_Mode( const bool& help_mode ){
            m_help_mode = help_mode;
        }


        /**
         * @brief Get the help mode
         */
        inline bool Get_Help_Mode()const{
            return m_help_mode;
        }


        /**
         * @brief Process CLI Command
         *
         * @param[in] command Command to process.
         */
        void Process_Command_Result( CMD::A_Command_Result const& result );
        

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
         * @brief Check if input is text.
         *
         * @param[in] input
         *
         * @return True if text, false otherwise.
        */
        bool Is_Text( const int& input )const; 


        /// CLI Text
        std::string m_cli_prompt_text;


        /// CLI Cursor Position
        int m_cli_prompt_cursor_head;


        /// CLI Cursor Position
        int m_cli_prompt_cursor_tail;
        int m_cli_prompt_cursor_at;

        /// Window Rows
        int m_window_rows;

        /// Window Cols
        int m_window_cols;

        /// Help Mode
        bool m_help_mode;

        /// Reference to Command History
        CMD::A_Command_History::ptr_t m_command_history;

        /// Current History Index
        int m_command_history_ptr;

}; // End of A_Render_State Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
