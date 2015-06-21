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
    // Print the main content
    Print_Main_Content();

    // Return the buffer table
    return m_buffer_data;
}

} // End of RENDER Namespace
} // End of CLI    Namespace

