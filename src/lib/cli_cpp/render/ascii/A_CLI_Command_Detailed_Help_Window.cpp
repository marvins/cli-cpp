/**
 * @file    A_CLI_Command_Detailed_Help_Window.cpp
 * @author  Marvin Smith
 * @date    7/3/2015
*/
#include "A_CLI_Command_Detailed_Help_Window.hpp"

// CLI Libraries
#include "../../utility/An_ASCII_Print_Table.hpp"
#include "../../utility/ANSI_Utilities.hpp"
#include "../../utility/String_Utilities.hpp"


namespace CLI{
namespace RENDER{

/**********************************/
/*          Constructor           */
/**********************************/
A_CLI_Command_Detailed_Help_Window::A_CLI_Command_Detailed_Help_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver,
                                                                        CMD::A_CLI_Command const&               cli_command )
  : A_Detailed_Help_Window(render_driver),
    m_class_name("A_CLI_Command_Detailed_Help_Window"),
    m_cli_command(cli_command)
{
    // Add the command names to the valid list
    std::vector<std::string> valid_names = cli_command.Get_Command_Name_List();
    for( size_t i=0; i<valid_names.size(); i++ ){
        m_valid_command_names.push_back(valid_names[i]);
    }


    // Update the buffer data
    Update_Buffer_Lines();
}


/******************************************/
/*          Update CLI Buffer Data        */
/******************************************/
void A_CLI_Command_Detailed_Help_Window::Update_Buffer_Data()
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
void A_CLI_Command_Detailed_Help_Window::Update_Buffer_Lines()
{
    
    // Define the min row and col
    int min_row = m_render_driver->Get_Min_Content_Row();
    int min_col = m_render_driver->Get_Min_Content_Col();

    std::string offset(min_col,' ');

    // Set the header
    int current_row = min_row;
    
    // Table Sizes
    const int title_entry_width = m_render_driver->Get_Window_Cols() - min_col;

    // Create Header lines
    std::string header_line_row = std::string(min_col,' ') + "+";
    std::string header_data_row = std::string(min_col,' ') + "|";

    const std::string title_bar = std::string(min_col, ' ') + m_cli_command.Get_Formal_Name() + " Detailed Command Information";

    for( int i=0; i<title_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String( title_bar, title_entry_width);

    header_line_row += "+";
    header_data_row += "|";

    m_buffer_data[current_row++] = header_line_row + UTILS::ANSI_NEWLINE;
    m_buffer_data[current_row++] = header_data_row + UTILS::ANSI_NEWLINE;
    m_buffer_data[current_row++] = header_line_row + UTILS::ANSI_NEWLINE;
    current_row++;


    // Print the command name
    m_buffer_data[current_row++] = offset + UTILS::ANSI_BLUE + "CLI Task: " + UTILS::ANSI_RESET + m_cli_command.Get_Formal_Name() + UTILS::ANSI_NEWLINE;
    current_row++;

    std::string cli_names_list = m_cli_command.Get_Command_Name_List()[0];
    for( size_t i=0; i<m_cli_command.Get_Command_Name_List().size(); i++ ){
        cli_names_list += ", " + m_cli_command.Get_Command_Name_List()[i];
    }
    m_buffer_data[current_row++] = offset + UTILS::ANSI_BLUE + "Valid CLI Commands: " + UTILS::ANSI_RESET + cli_names_list + UTILS::ANSI_NEWLINE;

}


} // End of RENDER Namespace
} // End of CLI    Namespace

