/**
 * @file    An_ASCII_Help_Menu.cpp
 * @author  Marvin Smith
 * @date    5/25/2015
*/
#include "An_ASCII_Help_Menu.hpp"

// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace RENDER{
namespace ASCII{

/// Buffer Newline
const std::string BUFFER_NEWLINE = "\n\r";

/******************************/
/*        Constructor         */
/******************************/
An_ASCII_Help_Menu::An_ASCII_Help_Menu( const std::string&                      cli_title,
                                        const int&                              window_rows,
                                        const int&                              window_cols,
                                        const int&                              min_col,
                                        const int&                              min_row,
                                        const int&                              max_row,
                                        const std::vector<CMD::A_CLI_Command>&  cli_command_list,
                                        const std::vector<CMD::A_Command>&      command_list )
  : m_cli_title(cli_title),
    m_window_rows(window_rows),
    m_window_cols(window_cols),
    m_min_col(min_col),
    m_min_row(min_row),
    m_max_row(max_row),
    m_cli_command_list(cli_command_list),
    m_command_list(command_list)
{
    // Initialize
    Initialize();
}


/****************************************/
/*          Initialize the Menu         */
/****************************************/
void An_ASCII_Help_Menu::Initialize()
{
    // Resize buffer
    m_buffer_data.resize(m_window_rows, "\n\r");

    // Set the header
    m_buffer_data[0] = UTILS::ANSI_CLEARSCREEN + UTILS::ANSI_RESETCURSOR + "     " + m_cli_title + BUFFER_NEWLINE;
    int current_row = m_min_row;
    
    // Table Sizes
    const int title_entry_width = m_window_cols - m_min_col;

    // Create Header lines
    std::string header_line_row = std::string(m_min_col,' ') + "+";
    std::string header_data_row = std::string(m_min_col,' ') + "|";
    
    for( int i=0; i<title_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("Help Menu", title_entry_width);
    
    header_line_row += "+";
    header_data_row += "|";

    m_buffer_data[current_row++] = header_line_row + BUFFER_NEWLINE;
    m_buffer_data[current_row++] = header_data_row + BUFFER_NEWLINE;
    m_buffer_data[current_row++] = header_line_row + BUFFER_NEWLINE;

    // Create the CLI Command Table
    Initialize_CLI_Command_Table();


    // Create the Command Table
    Initialize_Command_Table();
    
    
    // Define our stop and start rows
    int help_table_size = 10;
    int max_cli_row = help_table_size + m_min_row;
        
    // Print Parse Table
    m_cli_command_print_table->Print_Table( m_buffer_data, m_min_row,     max_cli_row, m_min_col );
    m_command_print_table->Print_Table(     m_buffer_data, max_cli_row+1, m_max_row-3, m_min_col );


}

/*************************************************/
/*       Initialize the CLI Command Table        */
/*************************************************/
void An_ASCII_Help_Menu::Initialize_CLI_Command_Table()
{

    // Update the sizes
    int col0_width = 15;
    int col1_width = 25;
    int col2_width = m_window_cols - col0_width - col1_width - m_min_col;

    // Process Parser Command List
    std::vector<std::string> titles;
    std::vector<int>  widths;
    titles.push_back("CLI Task");            widths.push_back(col0_width);
    titles.push_back("Valid Command Names"); widths.push_back(col1_width);
    titles.push_back("Description");         widths.push_back(col2_width);
    m_cli_command_print_table = std::make_shared<UTILS::An_ASCII_Print_Table>(  titles,
                                                                                widths, 
                                                                                UTILS::An_ASCII_Print_Table_Config(false,false) );
    
    // Add entries
    std::string command_list;
    std::vector<std::string> command_name_list;
    for( int i=0; i<(int)m_cli_command_list.size(); i++ ){

        // Set the Formal Name
        m_cli_command_print_table->Add_Entry( i, 0, " " + m_cli_command_list[i].Get_Formal_Name() );

        // Set argument list
        command_list = "";
        command_name_list = m_cli_command_list[i].Get_Command_Name_List();
        for( int j=0; j<(int)command_name_list.size(); j++ ){
            command_list += command_name_list[j];
            if( j < (int)command_name_list.size()-1){
                command_list += ", ";
            }
        }
        
        m_cli_command_print_table->Add_Entry( i, 1, " " + command_list );
        
        
        // Add Description
        m_cli_command_print_table->Add_Entry( i, 2, " " + m_cli_command_list[i].Get_Description() );
    }
}


/********************************************/
/*       Initialize the Command Table       */
/********************************************/
void An_ASCII_Help_Menu::Initialize_Command_Table()
{

    // Process Command List
    int col0_width = 25;
    int col1_width = 15;
    int col2_width = 10;
    int col3_width = 10;
    int col4_width = 10;
    int col5_width = m_window_cols - col0_width - col1_width - col2_width - col3_width - col4_width - m_min_col;
    
    std::vector<int>  widths;
    std::vector<std::string> titles;
    titles.push_back("Command");         widths.push_back(col0_width);
    titles.push_back("Arguments");       widths.push_back(col1_width);
    titles.push_back("Arg-Type");        widths.push_back(col2_width);
    titles.push_back("Arg-Req.");        widths.push_back(col3_width);
    titles.push_back("Default");         widths.push_back(col4_width);
    titles.push_back("Description");     widths.push_back(col5_width);

    m_command_print_table = std::make_shared<UTILS::An_ASCII_Print_Table>( titles, 
                                                                           widths, 
                                                                           UTILS::An_ASCII_Print_Table_Config(false,false));

    // Add entries
    std::vector<CMD::A_Command_Argument> argument_list;
    int current_row = 0;
    for( int i=0; i<(int)m_command_list.size(); i++ ){

        // Set the Formal Name
        m_command_print_table->Add_Entry( current_row, 0, m_command_list[i].Get_Name() );

        // Set the description
        m_command_print_table->Add_Entry( current_row, 5, m_command_list[i].Get_Description() );
        
        // Set the argument list and types
        argument_list = m_command_list[i].Get_Argument_List();
        for( int j=0; j<(int)argument_list.size(); j++ ){
            
            // Increment the row
            current_row++;

            // Set the argument
            m_command_print_table->Add_Entry( current_row, 1, argument_list[j].Get_Name() );

            // Set the argument type
            m_command_print_table->Add_Entry( current_row, 2, CMD::CommandArgumentTypeToString(argument_list[j].Get_Type()));

            // Set the required flag
            if( argument_list[j].Is_Required() ){
                m_command_print_table->Add_Entry( current_row, 3, "true");
            } else {
                m_command_print_table->Add_Entry( current_row, 3, "false");
            }

            // Set the default value
            m_command_print_table->Add_Entry( current_row, 4, argument_list[j].Get_Default_Value() );

            // Set the description
            m_command_print_table->Add_Entry( current_row, 5, argument_list[j].Get_Description() );

        }

        // Increment the row
        current_row++;

        // Add Blank Line
        m_command_print_table->Add_Blank_Row( current_row );

        // Increment the row
        current_row++;
    }

}

} // End of ASCII  Namespace
} // End of RENDER Namespace
} // End of CLI    Namespace
