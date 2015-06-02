/**
 * @file    A_Main_Window.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#include "A_Main_Window.hpp"

// CLI Libraries
#include "../../utility/ANSI_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace RENDER{

/*********************************/
/*          Constructor          */
/*********************************/
A_Main_Window::A_Main_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver,
                              CMD::A_Command_History::ptr_t             command_history )
    : An_ASCII_Render_Window_Base(render_driver),
      m_class_name("A_Main_Window"),
      m_command_history(command_history)
{
    // Build the history window
    m_history_window = std::make_shared<An_ASCII_History_Window>( m_command_history ); 
}


/****************************************/
/*          Print the Header            */
/****************************************/
void A_Main_Window::Print_Header()
{
    // Get the CLI Title
    std::string cli_title = m_render_driver->Get_CLI_Title();
    
    // Status Code String
    std::string status_code_string;

    // Check for status
    if( m_render_driver->Check_Waiting_Command_Response() == true ){
        status_code_string = UTILS::ANSI_BACK_RED + UTILS::ANSI_BLACK + "Waiting for Command Response";
        status_code_string.resize( m_render_driver->Get_Window_Cols()/4, ' ' );
    } else {
        status_code_string = UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + UTILS::Format_String( "Ready", m_render_driver->Get_Window_Cols()/4);
    }

    // Find the title length
    int title_length = std::min((int)cli_title.size(), m_render_driver->Get_Window_Cols()/2);
    int title_width  = m_render_driver->Get_Window_Cols() * 5 / 8;
    
    // Define the first title part
    std::string title_header = cli_title.substr( 0, title_length);
    title_header.resize(title_width, ' ');

    // Append the status text
    title_header += status_code_string + UTILS::ANSI_RESET;
    
    // Set the header
    m_buffer_data[0] = UTILS::ANSI_CLEARSCREEN + UTILS::ANSI_RESETCURSOR + "     " + title_header + UTILS::ANSI_NEWLINE;
}
 

/********************************************/
/*          Print the Main Content          */
/********************************************/
void A_Main_Window::Print_Main_Content()
{
    int max_col = m_render_driver->Get_Window_Cols()-3;
    int max_row = m_render_driver->Get_Window_Rows()-3;
    int min_col = m_render_driver->Get_Min_Content_Col();
    int min_row = m_render_driver->Get_Min_Content_Row();
    
    // Update the cli window
    m_history_window->Print_Table( m_buffer_data, 
                                   min_row,
                                   max_row,
                                   min_col,
                                   max_col );
}


/****************************************/
/*          Get the Buffer Data         */
/****************************************/
std::vector<std::string>& A_Main_Window::Get_Buffer_Data()
{
    // Print the header
    Print_Header();

    // Print the main content
    Print_Main_Content();

    // Return the buffer table
    return m_buffer_data;
}

} // End of RENDER Namespace
} // End of CLI    Namespace

