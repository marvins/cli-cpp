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

    // Build the shortcut print line
    m_shortcut_print_line = "  " + UTILS::ANSI_BLUE + "Shortcuts:" + UTILS::ANSI_RESET + "  F2) Help, F3) Log Output, F4) Alias List.";
}


/********************************************/
/*          Print the Main Content          */
/********************************************/
void A_Main_Window::Print_Main_Content()
{
    int max_col = m_render_driver->Get_Window_Cols()-3;
    int max_row = m_render_driver->Get_Window_Rows()-5;
    int min_col = m_render_driver->Get_Min_Content_Col();
    int min_row = m_render_driver->Get_Min_Content_Row();
    
    // Update the cli window
    m_history_window->Print_Table( m_buffer_data, 
                                   min_row,
                                   max_row,
                                   min_col,
                                   max_col );

    // Print the shortcut bar
    std::string adjusted_shortcut_print_line = m_shortcut_print_line;
    if( (int)adjusted_shortcut_print_line.size() >= max_col ){
        adjusted_shortcut_print_line = adjusted_shortcut_print_line.substr(0, max_col-1);
    }
    m_buffer_data[max_row+1] = adjusted_shortcut_print_line;
}


/****************************************/
/*          Get the Buffer Data         */
/****************************************/
std::vector<std::string>& A_Main_Window::Get_Buffer_Data()
{
    // Print the main content
    Print_Main_Content();

    // Return the buffer table
    return m_buffer_data;
}

} // End of RENDER Namespace
} // End of CLI    Namespace

