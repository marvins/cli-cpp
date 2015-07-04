/**
 * @file    A_Detailed_Help_Window.cpp
 * @author  Marvin Smith
 * @date    7/3/2015
*/
#include "A_Detailed_Help_Window.hpp"

// CLI Libraries
#include "../../utility/An_ASCII_Print_Table.hpp"
#include "../../utility/ANSI_Utilities.hpp"
#include "../../utility/String_Utilities.hpp"


namespace CLI{
namespace RENDER{

/**********************************/
/*          Constructor           */
/**********************************/
A_Detailed_Help_Window::A_Detailed_Help_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver )
  : An_ASCII_Render_Window_Base(render_driver),
    m_class_name("A_Detailed_Help_Window")
{

    // Update the buffer data
    Update_Buffer_Lines();
}


/******************************************/
/*          Update CLI Buffer Data        */
/******************************************/
void A_Detailed_Help_Window::Update_Buffer_Data()
{
    // Get original row count
    int original_row_count = m_buffer_data.size();


    // Call on parent method
    An_ASCII_Render_Window_Base::Update_Buffer_Data();


    // Check if the buffer size changed
    if( (int)m_buffer_data.size() != original_row_count ){
        Update_Buffer_Lines();
    }

}


/************************************/
/*      Update Buffer Line Data     */
/************************************/
void A_Detailed_Help_Window::Update_Buffer_Lines()
{
    
    /*
    // Define the min row and col
    int min_row = m_render_driver->Get_Min_Content_Row();
    int min_col = m_render_driver->Get_Min_Content_Col();
    int max_row = m_render_driver->Get_Window_Rows();

    // Set the header
    m_buffer_data[0] = UTILS::ANSI_CLEARSCREEN + UTILS::ANSI_RESETCURSOR + "     " + m_render_driver->Get_CLI_Title() + UTILS::ANSI_NEWLINE;
    int current_row = min_row;

    // Table Sizes
    const int title_entry_width = m_render_driver->Get_Window_Cols() - min_col;

    // Create Header lines
    std::string header_line_row = std::string(min_col,' ') + "+";
    std::string header_data_row = std::string(min_col,' ') + "|";

    for( int i=0; i<title_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("Help Menu", title_entry_width);

    header_line_row += "+";
    header_data_row += "|";

    m_buffer_data[current_row++] = header_line_row + UTILS::ANSI_NEWLINE;
    m_buffer_data[current_row++] = header_data_row + UTILS::ANSI_NEWLINE;
    m_buffer_data[current_row++] = header_line_row + UTILS::ANSI_NEWLINE;

    // Update the CLI Command Table
    Update_CLI_Command_Table();


    // Update the Command Table
    Update_Command_Table();


    // Define our stop and start rows
    int help_table_size = std::min( (int)m_cli_command_list.size()+3, max_row / 2);
    int max_cli_row = help_table_size + min_row;

    // Print Parse Table
    m_cli_command_print_table->Print_Table( m_buffer_data, min_row,     max_cli_row, min_col );
    m_command_print_table->Print_Table(     m_buffer_data, max_cli_row+1, max_row-3, min_col );
    */


}


/*********************************************/
/*          Check if Matching Name           */
/*********************************************/
bool A_Detailed_Help_Window::Is_Matching_Name( const std::string& test_name )const
{
    // Iterate over names
    for( size_t i=0; i<m_valid_command_names.size(); i++ ){
        if( m_valid_command_names[i] == test_name ){
            return true;
        }
    }
    return false;
}


} // End of RENDER Namespace
} // End of CLI    Namespace

