/**
 * @file    A_Render_State.cpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#include "A_Render_State.hpp"

// CLI Libraries
#include "../thirdparty/ncurses/NCurses_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace RENDER{

/************************************/
/*          Constructor             */
/************************************/
A_Render_State::A_Render_State( CORE::ConnectionType const&    conn_type,
                                CMD::A_Command_History::ptr_t  command_history )
  : m_cli_prompt_text(""),
    m_cli_prompt_cursor_head(0),
    m_cli_prompt_cursor_tail(0),
    m_cli_prompt_cursor_at(0),
    m_window_rows(0),
    m_window_cols(0),
    m_help_mode(false),
    m_command_history(command_history)
{
}


/************************/
/*      Push Text       */
/************************/
void A_Render_State::Process_Input( const int& input )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    BOOST_LOG_TRIVIAL(trace) << "Input Value: " << input;

    // SKip if < 0
    if( input < 0 ){ 
        BOOST_LOG_TRIVIAL(trace) << "Invalid Input Value.";
        return; 
    }


    // check for backspace
    if( input == KEY_BACKSPACE || input == 127 ){
        Apply_Backspace();
        return;
    }

    // check for delete
    else if( input == KEY_DC ){
        Apply_Delete();
        return;
    }

    // Check for left-key
    else if( input == KEY_LEFT ){
        Apply_Left_Key();
        return;
    }

    // Check for right-key
    else if( input == KEY_RIGHT ){
        Apply_Right_Key();
        return;
    }

    // Check for up-key
    else if( input == KEY_UP ){
        Apply_Up_Key();
        return;
    }

    // Check for down-key
    else if( input == KEY_DOWN ){
        Apply_Down_Key();
        return;
    }
    
    // Check for text
    else if( Is_Text( input ) == true ){

        // Otherwise, add character to string
        m_cli_prompt_text.push_back((char)input);

        // increment head
        m_cli_prompt_cursor_head++;
        m_cli_prompt_cursor_at++;

    }

}


/**************************************/
/*          Set window size           */
/**************************************/
void A_Render_State::Set_Window_Size( const int& rows,
                                      const int& cols )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    m_window_rows = rows;
    m_window_cols = cols;
}


/*********************************************/
/*          Clear the cursor text            */
/*********************************************/
void A_Render_State::Clear_Cursor_Text()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // clear the string
    m_cli_prompt_text = "";

    // Reset the cursors
    m_cli_prompt_cursor_head = 0;
    m_cli_prompt_cursor_tail = 0;
    m_cli_prompt_cursor_at   = 0;

    // reset the history pointer
    m_command_history_ptr = m_command_history->Size();

}


/*******************************/
/*      Apply a backspace      */
/*******************************/
void A_Render_State::Apply_Backspace()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    BOOST_LOG_TRIVIAL(trace) << "CLI Prompt Text: " << m_cli_prompt_text << ", Size: " << m_cli_prompt_text.size() << ", Cursor At: " << m_cli_prompt_cursor_at;

    // Erase the current character
    if( m_cli_prompt_text.size() > 0 && m_cli_prompt_cursor_at > 0){

        // Avoid going into negative space
        m_cli_prompt_cursor_head = std::max( 0, m_cli_prompt_cursor_head-1);
        m_cli_prompt_cursor_at   = std::max( 0, m_cli_prompt_cursor_at-1);
        BOOST_LOG_TRIVIAL(trace) << "  New CLI Cursor Head: " << m_cli_prompt_cursor_head;
        BOOST_LOG_TRIVIAL(trace) << "  New CLI Cursor At  : " << m_cli_prompt_cursor_at;

        // Delete the character
        m_cli_prompt_text.erase( m_cli_prompt_cursor_at, 1 );
        BOOST_LOG_TRIVIAL(trace) << "Erase Completed.";
    }
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}

/*******************************/
/*      Apply a Delete         */
/*******************************/
void A_Render_State::Apply_Delete()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Erase the current character
    if( m_cli_prompt_text.size() > 0 && m_cli_prompt_cursor_at <= ((int)m_cli_prompt_text.size()-1))
    {
        m_cli_prompt_text.erase( m_cli_prompt_cursor_at, 1 );

        // Back up the cursor
        m_cli_prompt_cursor_head--;
    }
}


/******************************/
/*      Apply Right Key       */
/******************************/
void A_Render_State::Apply_Left_Key()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Move the head left
    m_cli_prompt_cursor_at = std::max( m_cli_prompt_cursor_at-1, 0);

}

/******************************/
/*      Apply Left Key        */
/******************************/
void A_Render_State::Apply_Right_Key()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Move the head right
    m_cli_prompt_cursor_at = std::min( m_cli_prompt_cursor_at+1, (int)m_cli_prompt_text.size());
}


/******************************/
/*       Apply Up Key         */
/******************************/
void A_Render_State::Apply_Down_Key()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Skip if the cursor is at the max
    if( m_command_history_ptr < (m_command_history->Size()) ){

        // Increment the counter
        m_command_history_ptr++;
        
        // Change the text
        if( m_command_history_ptr != m_command_history->Size() ){
            m_cli_prompt_text = m_command_history->Get_Entry( m_command_history_ptr ).Get_Command_String();
        } else {
            m_cli_prompt_text = "";
        }

        // Update the pointers
        m_cli_prompt_cursor_at = 0;
        m_cli_prompt_cursor_tail = 0;
        m_cli_prompt_cursor_head = m_cli_prompt_text.size();


    }

}


/**********************************/
/*         Apply Down Key         */
/**********************************/
void A_Render_State::Apply_Up_Key()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // skip if the cursor is at zero
    if( m_command_history_ptr > 0 ){
        
        // decrement the counter
        m_command_history_ptr--;
    
        // Change the text
        m_cli_prompt_text = m_command_history->Get_Entry( m_command_history_ptr ).Get_Command_String();
        
        // Update the pointers
        m_cli_prompt_cursor_at = 0;
        m_cli_prompt_cursor_tail = 0;
        m_cli_prompt_cursor_head = m_cli_prompt_text.size();
    }
}


/********************************************/
/*      Process a CLI Command Result        */
/********************************************/
void A_Render_State::Process_Command_Result( const CMD::A_Command_Result& result ){

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // If help
    if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_HELP )
    {
        Set_Help_Mode(true);
    }

    // If back
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_BACK )
    {
        // If in help mode
        if( Get_Help_Mode() == true ){
            Set_Help_Mode(false);
        }

        // Otherwise, error
    }

    // If clear
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_CLEAR )
    {
        // Delete the history
        m_command_history->Clear();
    }
}


/************************/
/*      Check Text      */
/************************/
bool A_Render_State::Is_Text( const int& input )const
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Check for the alphabet
    if( (input >= 'a' && input <= 'z') ||
        (input >= 'A' && input <= 'Z') )
    {
        return true;
    }

    // Check for Numbers
    if( input >= '0' && input <= '9' )
    {
        return true;
    }
       
    // Check for other chars
    if( input == ' ' || 
        input == '.' ||
        input == ',' ||
        input == '_' ||
        input == '?' )
    {
        return true;
    }
    
    // Math Operators
    if( input == '+' || 
        input == '-' ||
        input == '|' ||
        input == '*' ||
        input == '^' )
    {
        return true;
    }

    return false;
}


} // End of RENDER Namespace
} // End of CLI    Namespace
