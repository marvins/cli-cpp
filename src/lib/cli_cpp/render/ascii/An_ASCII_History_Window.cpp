/**
 * @file    An_ASCII_History_Window.cpp
 * @author  Marvin Smith
 * @date    5/25/2015
*/
#include "An_ASCII_History_Window.hpp"

// CLI Libraries
#include "../../utility/String_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace RENDER{
namespace ASCII{


/**************************************/
/*            Constructor             */
/**************************************/
An_ASCII_History_Window::An_ASCII_History_Window( CMD::A_Command_History::ptr_t command_history )
  : m_class_name("An_ASCII_History_Window"),
    m_command_history(command_history)
{
}


/*****************************************/
/*        Print Table Information        */
/*****************************************/
bool An_ASCII_History_Window::Print_Table( std::vector<std::string>& buffer_data,
                                           int const&                min_row,
                                           int const&                max_row,
                                           int const&                min_col,
                                           int const&                max_col )const
{
    // Define our offset amount
    std::string BUFFER_OFFSET( min_col, ' ');

    // Define our newline buffer
    const std::string BUFFER_NEWLINE = "\n\r";
    
    // Table Sizes
    const int cmd_entry_width   = 7;
    const int status_entry_width = (max_col - cmd_entry_width)/2;
    const int input_entry_width = max_col - status_entry_width - cmd_entry_width - min_col;


    // Create Header lines
    std::string header_line_row = "+";
    std::string header_data_row = "|";
    
    
    for( int i=0; i<cmd_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("CMD", cmd_entry_width);
    
    header_line_row += "+";
    header_data_row += "|";

    for( int i=0; i<input_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("  Input", input_entry_width, UTILS::StringAlignment::LEFT);
    
    header_line_row += "+";
    header_data_row += "|";

    for( int i=0; i<status_entry_width; i++ ){ header_line_row += "-"; }
    header_data_row += UTILS::Format_String("  Status", status_entry_width, UTILS::StringAlignment::LEFT);
   
    header_line_row += "+" + BUFFER_NEWLINE;
    header_data_row += "|" + BUFFER_NEWLINE;

    // Set the current row
    int current_row = min_row;

    // Print Table Header
    buffer_data[current_row++] = BUFFER_OFFSET + header_line_row;
    buffer_data[current_row++] = BUFFER_OFFSET + header_data_row;
    buffer_data[current_row++] = BUFFER_OFFSET + header_line_row;

    // Build a blank table entry line
    std::string blank_line_row  = "|" + std::string(cmd_entry_width, ' ') + "|" + std::string(input_entry_width,' ') + "|" + std::string(status_entry_width,' ') + "|" + BUFFER_NEWLINE;
    
    // Iterate over main window region
    int row_id = m_command_history->Size()-1;
    std::string row_data;
    bool skip_row = false;
    for( int row = max_row-1; row >= current_row; row--, row_id-- )
    {
        
        // If we need to skip the row
        if( skip_row == true ){ 
            buffer_data[row] = BUFFER_OFFSET + blank_line_row;
            continue;
        }


        // Check if we still have commands to print
        else if( row_id < (int)m_command_history->Size() && row_id >= 0 )
        {
        
            // Creatde new row string
            row_data = "|" + UTILS::Format_String( UTILS::num2str<int>( m_command_history->Get_Entry( row_id ).Get_Command_ID()),
                                                   cmd_entry_width );
            row_data += "|" + UTILS::Format_String( "  " + m_command_history->Get_Entry( row_id ).Get_Command_String(),
                                                    input_entry_width,
                                                    UTILS::StringAlignment::LEFT );
            row_data += "|" + UTILS::Format_String( "  " + m_command_history->Get_Entry( row_id ).Get_Command_Result().Get_Parse_Status_String(),
                                                    status_entry_width,
                                                    UTILS::StringAlignment::LEFT );
            row_data += "|";

            // Print
            buffer_data[row] = BUFFER_OFFSET + row_data + BUFFER_NEWLINE;
        }


        // Otherwise, print a blank line
        else{
            buffer_data[row] = BUFFER_OFFSET + blank_line_row;
            continue;
        }

    }

    // Print bottom row
    buffer_data[max_row] = BUFFER_OFFSET + header_line_row;

    // Return successful operation
    return true;
}


} // End of ASCII  Namespace
} // End of RENDER Namespace
} // End of CLI    Namespace




