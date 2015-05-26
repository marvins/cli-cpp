/**
 * @file    A_Render_Manager_ASCII.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Render_Manager_ASCII.hpp"

// C++ Standard Libraries
#include <iostream>
#include <memory>
#include <sstream>

// CLI Libraries
#include "../utility/ANSI_Utilities.hpp"
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
    m_window_rows(0),
    m_window_cols(0),
    m_history_window(nullptr)
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
    m_window_rows(window_rows),
    m_window_cols(window_cols),
    m_history_window(nullptr)
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

    // Create new render state
    m_render_state.reset(new A_Render_State( CORE::ConnectionType::SOCKET, 
                                             m_command_history ));

    // Set the size
    m_render_state->Set_Window_Size( m_window_rows, 
                                     m_window_cols );

    // Build the console buffer
    Build_Console_Buffer();
    
    // Build the Help Buffer
    Build_Help_General_Buffer();

    // Print the history
    m_history_window = std::make_shared<ASCII::An_ASCII_History_Window>(m_command_history);

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

    // If help is selected, then use that buffer
    if( m_render_state->Get_Help_Mode() == true ){
        return; 
    }


    // Draw the header
    Print_Header( m_console_buffer );

    
    // Draw the main context
    Print_Main_Content();

    
    // Draw the footer
    Print_Footer();

    
    // Draw the CLI
    Print_CLI( m_console_buffer );


}


/****************************************/
/*          Print the header            */
/****************************************/
void A_Render_Manager_ASCII::Print_Header( std::vector<std::string>& print_buffer )
{
    
    // Set the header
    print_buffer[0] = UTILS::ANSI_CLEARSCREEN + "     " + m_cli_title + BUFFER_NEWLINE;

}


/************************************************/
/*          Print the Main Context              */
/************************************************/
void A_Render_Manager_ASCII::Print_Main_Content()
{

    // Define our stop and start rows
    int starty = 2;
    int endy   = m_render_state->Get_Rows() - 5;
    
    
    // Define our start columns
    int offset_col = 5;
    std::string BUFFER_OFFSET( offset_col, ' ');

    
    // Table Sizes
    const int cmd_entry_width   = 7;
    const int input_entry_width = m_render_state->Get_Cols() - cmd_entry_width - (2*offset_col);


    // Create Header lines
    std::string header_line_row = "+";
    std::string header_data_row = "|";
    
    
    for( int i=0; i<cmd_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("CMD", cmd_entry_width);
    
    header_line_row += "+";
    header_data_row += "|";

    for( int i=0; i<input_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("  Input", input_entry_width, UTILS::StringAlignment::LEFT);
    
    header_line_row += "+" + BUFFER_NEWLINE;
    header_data_row += "|" + BUFFER_NEWLINE;


    // Print Table Header
    m_console_buffer[starty++] = BUFFER_OFFSET + header_line_row;
    m_console_buffer[starty++] = BUFFER_OFFSET + header_data_row;
    m_console_buffer[starty++] = BUFFER_OFFSET + header_line_row;

    // Build a blank table entry line
    std::string blank_line_row  = "|" + std::string(cmd_entry_width, ' ') + "|" + std::string(input_entry_width,' ') + "|" + BUFFER_NEWLINE;
    
    // Iterate over main window region
    int row_id = 0;
    std::string row_data;
    bool skip_row = false;
    for( int row = starty; row <= endy; row++, row_id++ )
    {
        
        // If we need to skip the row
        if( skip_row == true ){ 
            m_console_buffer[row] = BUFFER_OFFSET + blank_line_row;
            continue;
        }


        // Check if we still have commands to print
        else if( row_id < (int)m_command_history->Size() ){
        
            // Creatde new row string
            row_data = "|" + UTILS::Format_String( UTILS::num2str<int>( m_command_history->Get_Entry( row_id ).Get_Command_ID()),
                                                   cmd_entry_width );
            row_data += "|" + UTILS::Format_String( "  " + m_command_history->Get_Entry( row_id ).Get_Command_String(),
                                                    input_entry_width,
                                                    UTILS::StringAlignment::LEFT );
            row_data += "|";

            // Print
            m_console_buffer[row] = BUFFER_OFFSET + row_data + BUFFER_NEWLINE;
        }


        // Otherwise, print a blank line
        else{
            m_console_buffer[row] = BUFFER_OFFSET + blank_line_row;
            continue;
        }

    }

    // Print bottom row
    m_console_buffer[endy+1] = BUFFER_OFFSET + header_line_row;


}


/****************************************/
/*          Print the Footer            */
/****************************************/
void A_Render_Manager_ASCII::Print_Footer()
{


}


/********************************/
/*          Print the CLI       */
/********************************/
void A_Render_Manager_ASCII::Print_CLI( std::vector<std::string>& print_buffer )const
{
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
    if( cursor_text.size() > 0 && cli_prompt_pos < cursor_text.size() ){
        output += UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + cursor_text[cli_prompt_pos] + UTILS::ANSI_RESET;
    } else {
        output += UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + " " + UTILS::ANSI_RESET;
    }

    // Don't do this if we are at the end
    if( cli_prompt_pos < cursor_text.size()){
        output += cursor_text.substr(cli_prompt_pos+1);
    }

    // Check if awaiting response
    std::string WARNING_ROW;
    if( m_waiting_command_response == true ){
        WARNING_ROW = "      " + UTILS::ANSI_BLACK + UTILS::ANSI_BACK_RED + "   WAITING FOR COMMAND RESPONSE   " + UTILS::ANSI_RESET;
    }

    output += "\n\r";

    // Copy to the buffer
    print_buffer[cli_row+0] = output;
    print_buffer[cli_row+1] = WARNING_ROW;

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
                                                               3,
                                                               3,
                                                               m_render_state->Get_Rows()-4,
                                                               m_cli_command_list,
                                                               m_command_list );
}


} // End of RENDER Namespace
} // End of CLI    Namespace

