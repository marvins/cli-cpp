/**
 * @file    A_Main_Window.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#include "An_Async_Message_Window.hpp"

// CLI Libraries
#include "../../utility/ANSI_Utilities.hpp"
#include "../../utility/Log_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace RENDER{

/*********************************/
/*          Constructor          */
/*********************************/
An_Async_Message_Window::An_Async_Message_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver )
    : An_ASCII_Render_Window_Base(render_driver),
      m_class_name("An_Async_Message_Window")
{

    // Build the shortcut print line
    m_shortcut_print_line = "  " + UTILS::ANSI_BLUE + "Shortcuts:" + UTILS::ANSI_RESET + "  F2) Help, F3) Log Output, F4) Alias List, F5) Variable List." + UTILS::ANSI_NEWLINE;

    // Initialize the Print Table
    Initialize_Print_Table();
}


/**********************************/
/*        Send Async Data         */
/**********************************/
void An_Async_Message_Window::Send_Asynchronous_Message( const std::string& topic_name,
                                                         const std::string& message )
{
    // Log Entry
    CLI_LOG_CLASS_ENTRY();

    const std::string format_string = "%Y:%m:%d_%H:%M:%S";
    
    // Create timestamp string
    char buffer[80];

    time_t rawtime = (time_t)time(nullptr);
    struct tm * timeinfo;
    timeinfo = gmtime( &rawtime );

    strftime (buffer,80,format_string.c_str(),timeinfo);
    
    // Create output
    std::string ts_string(buffer);

    // Update table
    m_msg_history.push_back(std::make_tuple( ts_string, topic_name, message ));

    m_print_table->Add_Entry( m_msg_history.size(), 
                              0, 
                              ts_string );
    
    m_print_table->Add_Entry( m_msg_history.size(), 
                              1, 
                              topic_name );
    
    m_print_table->Add_Entry( m_msg_history.size(), 
                              2, 
                              message );
    
    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/****************************************/
/*          Get the Buffer Data         */
/****************************************/
std::vector<std::string>& An_Async_Message_Window::Get_Buffer_Data()
{
    // Log Entry
    CLI_LOG_CLASS_ENTRY();

    // Print the main content
    Print_Main_Content();

    // Return the buffer table
    return m_buffer_data;
}


/********************************************/
/*          Print the Main Content          */
/********************************************/
void An_Async_Message_Window::Print_Main_Content()
{
    // Log Entry
    CLI_LOG_CLASS_ENTRY();

    int max_col = m_render_driver->Get_Window_Cols()-3;
    int max_row = m_render_driver->Get_Window_Rows()-4;
    int min_col = m_render_driver->Get_Min_Content_Col();
    int min_row = m_render_driver->Get_Min_Content_Row();
   
        
    // Update the cli window
    m_print_table->Print_Table( m_buffer_data, 
                                min_row,
                                max_row,
                                min_col );

    // Print the shortcut bar
    std::string adjusted_shortcut_print_line = m_shortcut_print_line;
    if( (int)adjusted_shortcut_print_line.size() >= max_col ){
        adjusted_shortcut_print_line = adjusted_shortcut_print_line.substr(0, max_col-1);
    }
    m_buffer_data[max_row+1] = adjusted_shortcut_print_line;

}


/***************************************************/
/*          Initialize the Printing Table          */
/***************************************************/
void An_Async_Message_Window::Initialize_Print_Table()
{
    // Titles
    std::vector<std::string> titles;
    titles.push_back("Date/Time");
    titles.push_back("Topic-Name");
    titles.push_back("Message");
    
    std::vector<int> widths;
    widths.push_back(25);
    widths.push_back(30);
    widths.push_back(m_render_driver->Get_Window_Cols() - m_render_driver->Get_Min_Content_Col() - 55);

    // Build the print table
    m_print_table = std::make_shared<UTILS::An_ASCII_Print_Table>( titles,
                                                                   widths,
                                                                   UTILS::An_ASCII_Print_Table_Config(false,false));

}


} // End of RENDER Namespace
} // End of CLI    Namespace

