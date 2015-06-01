/**
 * @file    A_Render_Manager_ASCII.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Render_Manager_ASCII.hpp"

// C++ Standard Libraries
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>

// CLI Libraries
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"
#include "../utility/String_Utilities.hpp"

namespace CLI{
namespace RENDER{

const std::string BUFFER_NEWLINE = "\n\r";

/****************************/
/*      Constructor         */
/****************************/
A_Render_Manager_ASCII::A_Render_Manager_ASCII( A_Render_Driver_Context_Base::ptr_t driver_context )
 :  A_Render_Manager_Base(),
    m_class_name("A_Render_Manager_ASCII"),
    m_history_window(nullptr),
    m_window_rows(0),
    m_window_cols(0),
    m_min_content_row(1),
    m_min_content_col(2)
{
    // Cast the driver
    m_render_driver_context = std::dynamic_pointer_cast<A_Render_Driver_Context_ASCII>(driver_context);
    
    // Set the rows and columns
    m_window_rows = m_render_driver_context->Get_Window_Rows();
    m_window_cols = m_render_driver_context->Get_Window_Cols();


    // Create new render state
    m_render_state.reset(new A_Render_State( CORE::ConnectionType::SOCKET, 
                                             m_command_history));
}


/****************************/
/*      Constructor         */
/****************************/
A_Render_Manager_ASCII::A_Render_Manager_ASCII( const int& window_rows,
                                                const int& window_cols )
 :  A_Render_Manager_Base(),
    m_class_name("A_Render_Manager_ASCII"),
    m_history_window(nullptr),
    m_window_rows(window_rows),
    m_window_cols(window_cols),
    m_min_content_row(1),
    m_min_content_col(2)
{
    // Create new render state
    m_render_state.reset(new A_Render_State( CORE::ConnectionType::SOCKET, 
                                             m_command_history));
}


/********************************/
/*      Initialize Curses       */
/********************************/
void A_Render_Manager_ASCII::Initialize()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Create new render state
    m_render_state.reset(new A_Render_State( CORE::ConnectionType::SOCKET, 
                                             m_command_history ));

    // Set the size
    m_render_state->Set_Window_Size( m_window_rows, 
                                     m_window_cols );

    // Update the status code string
    m_status_code_string = std::string(m_window_cols/4, ' ');

    // Build the console buffer
    Build_Console_Buffer();
    
    // Build the Help Buffer
    Build_Help_General_Buffer();

    // Print the history
    m_history_window = std::make_shared<ASCII::An_ASCII_History_Window>(m_command_history);

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

}

/********************************/
/*        Finalize Curses       */
/********************************/
void A_Render_Manager_ASCII::Finalize()
{
}


/****************************/
/*      Get the buffer      */
/****************************/
std::vector<std::string>& A_Render_Manager_ASCII::Get_Console_Buffer()
{

    // Check if help requested
    if( m_render_state->Get_Help_Mode() == true ){
        return m_help_menu->Get_Buffer_Data();
    }

    // Otherwise, return the main buffer
    return m_console_buffer;
}


/********************************/
/*      Refresh the screen      */
/********************************/
void A_Render_Manager_ASCII::Refresh()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // If help is selected, then use that buffer
    if( m_render_state->Get_Help_Mode() == true ){
        
        // Print the CLI
        Print_CLI( m_help_menu->Get_Buffer_Data() );
        
        // Log Entry
        BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method (help branch). File: " << __FILE__ << ", Line: " << __LINE__;
        return; 
    }


    // Draw the header
    Print_Header( m_console_buffer );

    
    // Draw the main context
    Print_Main_Content();

    
    // Draw the CLI
    Print_CLI( m_console_buffer );

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

}


/****************************************/
/*          Print the header            */
/****************************************/
void A_Render_Manager_ASCII::Print_Header( std::vector<std::string>& print_buffer )
{
    // Check for status
    if( m_waiting_command_response == true ){
        m_status_code_string = UTILS::ANSI_BACK_RED + UTILS::ANSI_BLACK + "Waiting for Command Response";
        m_status_code_string.resize( m_window_cols/4, ' ' );
    } else {
        m_status_code_string = UTILS::ANSI_BACK_WHITE + std::string( m_window_cols/4, ' ');
    }

    // Find the title length
    int title_length = std::min((int)m_cli_title.size(), m_render_state->Get_Cols()/2);
    int title_width  = m_render_state->Get_Cols() * 5 / 8;
    
    // Define the first title part
    std::string title_header = m_cli_title.substr( 0, title_length);
    title_header.resize(title_width, ' ');

    // Append the status text
    title_header += m_status_code_string + UTILS::ANSI_RESET;
    
    // Set the header
    print_buffer[0] = UTILS::ANSI_CLEARSCREEN + UTILS::ANSI_RESETCURSOR + "     " + title_header + BUFFER_NEWLINE;

}


/************************************************/
/*          Print the Main Context              */
/************************************************/
void A_Render_Manager_ASCII::Print_Main_Content()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Set the min and max positions
    int max_col = m_render_state->Get_Cols()-3;
    int max_row = m_render_state->Get_Rows()-3;
    
    // Update the cli window
    m_history_window->Print_Table( m_console_buffer, 
                                   m_min_content_row,
                                   max_row,
                                   m_min_content_col,
                                   max_col );
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/********************************/
/*          Print the CLI       */
/********************************/
void A_Render_Manager_ASCII::Print_CLI( std::vector<std::string>& print_buffer )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Set the buffer row
    int cli_row = m_window_rows - 2;

    
    // Get the cursor text
    const std::string cursor_text = m_render_state->Get_Cursor_Text();
    const int cli_prompt_pos = m_render_state->Get_Cursor_Pos();

    // Write the Cursor Text
    std::string output = "   ";
    output += UTILS::ANSI_GREEN + std::string("cmd: ") + UTILS::ANSI_RESET;
    
    // Don't do this if the cursor is at 0
    if( cli_prompt_pos > 0 ){
        output += cursor_text.substr(0,cli_prompt_pos);
    }

    // Print the text
    if( (int)cursor_text.size() > 0 && cli_prompt_pos < (int)cursor_text.size() ){
        output += UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + cursor_text[cli_prompt_pos] + UTILS::ANSI_RESET;
    } else {
        output += UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + " " + UTILS::ANSI_RESET;
    }

    // Don't do this if we are at the end
    if( cli_prompt_pos < (int)cursor_text.size()){
        output += cursor_text.substr(cli_prompt_pos+1);
    }


    // Copy to the buffer
    print_buffer[cli_row+0] = output + BUFFER_NEWLINE +  UTILS::ANSI_CURSORINVIS;

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/****************************************/
/*      Build the Console Buffer        */
/****************************************/
void A_Render_Manager_ASCII::Build_Console_Buffer()
{
    // Allocate buffer
    m_console_buffer.resize(m_window_rows, "\n\r");
    m_console_buffer[0].insert(0, UTILS::ANSI_CLEARSCREEN);
}


/*****************************************/
/*      Build the General Help Buffer    */
/*****************************************/
void A_Render_Manager_ASCII::Build_Help_General_Buffer()
{
    // Create the ASCII Help Menu
    m_help_menu = std::make_shared<ASCII::An_ASCII_Help_Menu>( m_cli_title, 
                                                               m_render_state->Get_Rows(),
                                                               m_render_state->Get_Cols(),
                                                               m_min_content_col,
                                                               m_min_content_row,
                                                               m_render_state->Get_Rows(),
                                                               m_cli_command_list,
                                                               m_command_list );
}


} // End of RENDER Namespace
} // End of CLI    Namespace

