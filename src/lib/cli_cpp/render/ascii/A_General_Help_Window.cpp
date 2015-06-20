/**
 * @file    A_General_Help_Window.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#include "A_General_Help_Window.hpp"

// CLI Libraries
#include "../../utility/An_ASCII_Print_Table.hpp"
#include "../../utility/ANSI_Utilities.hpp"
#include "../../utility/String_Utilities.hpp"


namespace CLI{
namespace RENDER{

/**********************************/
/*          Constructor           */
/**********************************/
A_General_Help_Window::A_General_Help_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver,
                                              const std::vector<CMD::A_CLI_Command>&  cli_command_list,
                                              const std::vector<CMD::A_Command>&      command_list )
  : An_ASCII_Render_Window_Base(render_driver),
    m_class_name("A_General_Help_Window"),
    m_cli_command_list(cli_command_list),
    m_command_list(command_list)
{
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

    // Create the CLI Command Table
    Initialize_CLI_Command_Table();


    // Create the Command Table
    Initialize_Command_Table();
    
    
    // Define our stop and start rows
    int help_table_size = 13;
    int max_cli_row = help_table_size + min_row;
        
    // Print Parse Table
    m_cli_command_print_table->Print_Table( m_buffer_data, min_row,     max_cli_row, min_col );
    m_command_print_table->Print_Table(     m_buffer_data, max_cli_row+1, max_row-3, min_col );

}


/*************************************************/
/*       Initialize the CLI Command Table        */
/*************************************************/
void A_General_Help_Window::Initialize_CLI_Command_Table()
{

    // Update the sizes
    int col0_width = 15;
    int col1_width = 25;
    int col2_width = m_render_driver->Get_Window_Cols() - col0_width - col1_width - m_render_driver->Get_Min_Content_Col();

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
void A_General_Help_Window::Initialize_Command_Table()
{

    // Process Command List
    int col0_width = 25;
    int col1_width = 15;
    int col2_width = 10;
    int col3_width = 10;
    int col4_width = 10;
    int col5_width = m_render_driver->Get_Window_Cols() - col0_width - col1_width - col2_width - col3_width - col4_width - m_render_driver->Get_Min_Content_Col();
    
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


} // End of RENDER Namespace
} // End of CLI    Namespace

