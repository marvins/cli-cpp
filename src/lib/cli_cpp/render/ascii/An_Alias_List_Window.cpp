/**
 * @file    An_Alias_List_Window.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#include "An_Alias_List_Window.hpp"

// CLI Libraries
#include "../../utility/An_ASCII_Print_Table.hpp"
#include "../../utility/ANSI_Utilities.hpp"
#include "../../utility/String_Utilities.hpp"


// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace RENDER{

/**********************************/
/*          Constructor           */
/**********************************/
An_Alias_List_Window::An_Alias_List_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver,
                                            const CMD::A_Command_Parser::ptr_t      command_parser )
  : An_ASCII_Render_Window_Base(render_driver),
    m_class_name("An_Alias_List_Window"),
    m_command_parser(command_parser)
{
    // Define the min row and col
    int min_row = m_render_driver->Get_Min_Content_Row();
    int min_col = m_render_driver->Get_Min_Content_Col();
    
    // Set the header
    m_buffer_data[0] = UTILS::ANSI_CLEARSCREEN + UTILS::ANSI_RESETCURSOR + "     " + m_render_driver->Get_CLI_Title() + UTILS::ANSI_NEWLINE;
    int current_row = min_row;
    
    // Table Sizes
    const int title_entry_width = m_render_driver->Get_Window_Cols() - min_col;

    // Create Header lines
    std::string header_line_row = std::string(min_col,' ') + "+";
    std::string header_data_row = std::string(min_col,' ') + "|";
    
    for( int i=0; i<title_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("Alias List", title_entry_width);
    
    header_line_row += "+";
    header_data_row += "|";

    m_buffer_data[current_row++] = header_line_row + UTILS::ANSI_NEWLINE;
    m_buffer_data[current_row++] = header_data_row + UTILS::ANSI_NEWLINE;
    m_buffer_data[current_row++] = header_line_row + UTILS::ANSI_NEWLINE;

    // Update the Alias List Table
    Update_Alias_List_Table();
    
    

}


/*************************************/
/*       Update the List table       */
/*************************************/
void An_Alias_List_Window::Update_Buffer_Data()
{

    // Call Parent Method First
    An_ASCII_Render_Window_Base::Update_Buffer_Data();

    // Update the alias list table
    Update_Alias_List_Table();

}


/*************************************************/
/*       Initialize the CLI Command Table        */
/*************************************************/
void An_Alias_List_Window::Update_Alias_List_Table()
{
    // Define the min row and col
    int min_row = m_render_driver->Get_Min_Content_Row();
    int min_col = m_render_driver->Get_Min_Content_Col();
    int max_row = m_render_driver->Get_Window_Rows();

    // Update the sizes
    int col0_width = m_render_driver->Get_Window_Cols() * 0.5;
    int col1_width = m_render_driver->Get_Window_Cols() - col0_width - m_render_driver->Get_Min_Content_Col();

    // Process Parser Command List
    std::vector<std::string> titles;
    std::vector<int>  widths;
    titles.push_back("Alias Name");      widths.push_back(col0_width);
    titles.push_back("Command Text");    widths.push_back(col1_width);
    m_alias_print_table = std::make_shared<UTILS::An_ASCII_Print_Table>(  titles,
                                                                          widths, 
                                                                          UTILS::An_ASCII_Print_Table_Config(false,false) );
    
    // Add entries
    std::vector<CMD::A_Command_Alias> alias_list = m_command_parser->Get_Alias_List();
    for( int i=0; i<(int)alias_list.size(); i++ ){

        // Set the Alias Name
        m_alias_print_table->Add_Entry( i, 0, " " + alias_list[i].Get_Alias_Name() );

        // Set the Command Text
        m_alias_print_table->Add_Entry( i, 1, " " + alias_list[i].Get_Command_Text() );
    }

    // Print Parse Table
    m_alias_print_table->Print_Table( m_buffer_data, min_row,     max_row-3, min_col );
}

} // End of RENDER Namespace
} // End of CLI    Namespace

