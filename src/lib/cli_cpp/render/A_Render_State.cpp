/**
 * @file    A_Render_State.cpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#include "A_Render_State.hpp"

// C++ Standard Libraries
#include <iostream>

// CLI Libraries
#include "../core/CLI_Event_Type.hpp"
#include "../core/Event_Manager.hpp"
#include "../utility/Log_Utilities.hpp"

namespace CLI{
namespace RENDER{

/************************************/
/*          Constructor             */
/************************************/
A_Render_State::A_Render_State( CORE::ConnectionType const&    conn_type,
                                CMD::A_Command_History::ptr_t  command_history,
                                CMD::A_Command_Parser::ptr_t   command_parser )
  : m_cli_prompt_text(""),
    m_cli_prompt_cursor_head(0),
    m_cli_prompt_cursor_tail(0),
    m_cli_prompt_cursor_at(0),
    m_window_rows(0),
    m_window_cols(0),
    m_command_history(command_history),
    m_command_parser(command_parser),
    m_command_history_ptr(m_command_history->Size())
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
    if( input == (int)CORE::CLI_Event_Type::KEYBOARD_BACKSPACE || input == 127 ){
        Apply_Backspace();
        return;
    }

    // check for delete
    else if( input == (int)CORE::CLI_Event_Type::KEYBOARD_DELETE_KEY ){
        Apply_Delete();
        return;
    }

    // Check for left-key
    else if( input == (int)CORE::CLI_Event_Type::KEYBOARD_LEFT_ARROW ){
        Apply_Left_Key();
        return;
    }

    // Check for right-key
    else if( input == (int)CORE::CLI_Event_Type::KEYBOARD_RIGHT_ARROW ){
        Apply_Right_Key();
        return;
    }

    // Check for up-key
    else if( input == (int)CORE::CLI_Event_Type::KEYBOARD_UP_ARROW ){
        Apply_Up_Key();
        return;
    }

    // Check for down-key
    else if( input == (int)CORE::CLI_Event_Type::KEYBOARD_DOWN_ARROW ){
        Apply_Down_Key();
        return;
    }

    // Check for Tab Key
    else if( input == (int)CORE::CLI_Event_Type::KEYBOARD_TAB_KEY ){
        Apply_Tab_Key();
        return;
    }
    
    // Check for text
    else if( Is_Text( input ) == true ){

        // Otherwise, add character to string
        m_cli_prompt_text.insert( m_cli_prompt_text.begin() + m_cli_prompt_cursor_at,
                                  (char)input );

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
        m_cli_prompt_cursor_at = m_cli_prompt_text.size();
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
        m_cli_prompt_cursor_at = m_cli_prompt_text.size();
        m_cli_prompt_cursor_tail = 0;
        m_cli_prompt_cursor_head = m_cli_prompt_text.size();
    }
}


/***********************************/
/*          Apply Tab Key          */
/***********************************/
void A_Render_State::Apply_Tab_Key()
{
    // Make sure the command parser is not null
    if( m_command_parser == nullptr ){
        BOOST_LOG_TRIVIAL(fatal) << "Command parser is null. Expect a seg fault. File: " << __FILE__ << ", Line: " << __LINE__;
    }

    // Query the command parser
    std::vector<std::string> autocomplete_match_list;

    m_command_parser->Update_Autocomplete_String( m_cli_prompt_text,
                                                  autocomplete_match_list );

    // If the size is 1, then just update to that.
    if( autocomplete_match_list.size() == 1 ){
        
        // Set the text
        m_cli_prompt_text = autocomplete_match_list[0];
        m_cli_prompt_cursor_at = m_cli_prompt_text.size();
        m_cli_prompt_cursor_head = m_cli_prompt_text.size();
        m_cli_prompt_cursor_tail = 0;

    }
    else if( autocomplete_match_list.size() > 1 ){

        // Get the best match
        m_cli_prompt_text   = UTILS::String_Substring_Match( autocomplete_match_list );
        m_cli_prompt_cursor_at = m_cli_prompt_text.size();
        m_cli_prompt_cursor_head = m_cli_prompt_text.size();
        m_cli_prompt_cursor_tail = 0;
    }

}


/********************************************/
/*      Process a CLI Command Result        */
/********************************************/
void A_Render_State::Process_Command_Result( const CMD::A_Command_Result& result ){

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // If help
    if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_HELP ){
        CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_HELP );
    }


    // If back
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_BACK ){
        CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_BACK );
    }


    // If Log
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_LOG ){
        CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_LOG );
    }

    
    // If adding an alias
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_ALIAS_ADD ){
        
        bool valid_alias;
        CMD::A_Command_Alias temp_alias = CMD::A_Command_Alias::From_CLI_Input( UTILS::String_Merge( result.Get_Argument_Value_List() ),
                                                                                valid_alias);
        if( valid_alias == true ){
            m_command_parser->Add_Command_Alias( temp_alias );
        }
    }


    // If removing an alias
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_ALIAS_REMOVE ){
        bool valid_alias;
        CMD::A_Command_Alias temp_alias = CMD::A_Command_Alias::From_CLI_Input( UTILS::String_Merge( result.Get_Argument_Value_List() ),
                                                                                valid_alias);
        if( valid_alias == true ){
            m_command_parser->Remove_Command_Alias( temp_alias );
        }
    }


    // If listing aliases
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_ALIAS_LIST ){
        CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_ALIAS_LIST );
    }


    // If clear
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_CLEAR )
    {
        m_command_history->Clear();
    }

    // If We are running a CLI Run Script
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_RUN_SCRIPT ){

        // Get the path
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
        input == '?' ||
        input == '/' )
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
