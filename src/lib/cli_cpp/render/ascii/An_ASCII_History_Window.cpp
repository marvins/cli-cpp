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


/**************************************/
/*            Constructor             */
/**************************************/
An_ASCII_History_Window::An_ASCII_History_Window( CMD::A_Command_History::ptr_t command_history )
  : m_class_name("An_ASCII_History_Window"),
    m_command_history(command_history),
    m_table_headers(3),
    m_table_alignments(3)
{
    
    // Table Headers
    m_table_headers[0] = "CMD";
    m_table_headers[1] = " Input";
    m_table_headers[2] = " Status";

    // Table Alignments
    m_table_alignments[0] = UTILS::StringAlignment::CENTER;
    m_table_alignments[1] = UTILS::StringAlignment::LEFT;
    m_table_alignments[2] = UTILS::StringAlignment::LEFT;

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
    std::vector<int> table_widths(3);
    table_widths[0] = 7;
    table_widths[1] = (max_col - table_widths[0])/2;
    table_widths[2] = max_col - table_widths[1] - table_widths[0] - min_col;


    // Misc strings
    std::vector<std::string> print_buffers(3);
    std::vector<bool> print_flags(3);
    int max_temp_row;
    
    
    // Create Header lines
    std::string header_line_row = "+";
    std::string header_data_row = "|";
    
    for( size_t a=0; a<table_widths.size(); a++ ){
          header_line_row += UTILS::String_Fill("-", '-', table_widths[a]-1) + "+";
          header_data_row += UTILS::Format_String( m_table_headers[a], table_widths[a], m_table_alignments[a]) + "|";
    } 
    header_line_row += BUFFER_NEWLINE;
    header_data_row += BUFFER_NEWLINE;


    // Set the current row
    int current_row = min_row;

    // Print Table Header
    buffer_data[current_row++] = BUFFER_OFFSET + header_line_row;
    buffer_data[current_row++] = BUFFER_OFFSET + header_data_row;
    buffer_data[current_row++] = BUFFER_OFFSET + header_line_row;

    // Build a blank table entry line
    std::string blank_line_row;
    for( size_t i=0; i<table_widths.size(); i++ ){
        blank_line_row += "|" + std::string(table_widths[i],' ');
    }
    blank_line_row += "|" + BUFFER_NEWLINE;
   

    // Iterate over main window region
    int row_id = m_command_history->Size()-1;
    std::string row_data, temp_buff;
    
    // Start at the bottom row and move up
    int row_position = max_row-1;
    while( row_id >= 0 && row_position >= current_row )
    {

        //  Build the print data
        print_buffers[0] = UTILS::num2str<int>(m_command_history->Get_Entry(row_id).Get_Command_ID());
        print_buffers[1] = " " + m_command_history->Get_Entry( row_id ).Get_Command_String();
        print_buffers[2] = " " + m_command_history->Get_Entry( row_id ).Get_Command_Result()->Get_Parse_Status_String();


        // Compute max number of rows required for printing
        max_temp_row = 0;
        for( size_t a=0; a<print_buffers.size(); a++ )
            max_temp_row = std::max( Get_Data_Row_Count( print_buffers[a], table_widths[a]), max_temp_row );

        // Reset all print flags
        for( size_t fid=0; fid<print_flags.size(); fid++ ){
            print_flags[fid] = true;
        }

        // Iterate while there is still data to print
        for( int mr=max_temp_row; mr>= 0; mr-- ){

            // Clear the Data
            row_data = "|";

            // iterate over each print buffer and format the output
            for( size_t a=0; a<print_buffers.size(); a++ )
            {
                
                if( print_flags[a] == true ){
                    row_data += UTILS::Format_String( Strip_Data(print_buffers[a], table_widths[a]),
                                                      table_widths[a], 
                                                      m_table_alignments[a]) + "|";
                }
                else{
                    row_data += UTILS::String_Fill(" ", ' ', table_widths[a]-1) + "|";
                }
            }
             
            // Write the buffer row
            if( row_position-mr >= current_row ){
                buffer_data[row_position-mr] = BUFFER_OFFSET + row_data + BUFFER_NEWLINE;
            }

            // Update the buffers
            for( size_t a=0; a<print_buffers.size(); a++ ){
                    
                // Prune the buffer to get what is left
                temp_buff = Prune_Data( print_buffers[a], table_widths[a] );
                
                // If we have more data to print
                if( temp_buff.size() > 1 ){
                    print_buffers[a] = " " + temp_buff;
                }
                // Otherwise, stop printing
                else{
                    print_flags[a] = false;
                }
            }
        }

        // Decrement the row
        row_position -= (max_temp_row + 1);
        
        // Decrement the row id
        row_id--;

    }

    // For remaining rows, print blank lines
    for( int row=row_position; row >= current_row; row-- ){
        buffer_data[row] = BUFFER_OFFSET + blank_line_row;
    }

    // Print bottom row
    buffer_data[max_row] = BUFFER_OFFSET + header_line_row;


    // Return successful operation
    return true;
}

/*******************************/
/*    Get the data row count   */
/*******************************/
int An_ASCII_History_Window::Get_Data_Row_Count( const std::string& data,
                                                 const int& cols ) const
{
    // Compute the baseline row count
    int count = data.size() / cols;

    // Look for newlines
    for( size_t i=0; i<data.size(); i++ ){
        if( data[i] == '\n' ){
            count++;
        }
    }
    return count;
}


/******************************/
/*        Strip the data      */
/******************************/
std::string An_ASCII_History_Window::Strip_Data( const std::string& data,
                                                 const int& cols )const
{
    // Check input size
    if( data.size() <= 0 ){
        return "";
    }
    
    // Create output
    int max_col = std::min( (int)data.size(), cols );
    std::string output = data.substr(0, max_col);

    // Iterate, looking for the first newline
    for( size_t i=1; i<output.size(); i++ ){
        if( output[i] == '\n' ){
            return output.substr(0, i);
        }
    }

    return output;
}




/******************************/
/*        Prune the data      */
/******************************/
std::string An_ASCII_History_Window::Prune_Data( const std::string& data,
                                                 const int& cols )const
{
    // Check input size
    if( data.size() <= 0 ){
        return "";
    }

    // Iterate over what we have, looking for the first newline
    int max_col = std::min( cols, (int)data.size());
    int split_idx = max_col;
    for( int i=1; i<max_col; i++ ){
        if( data[i] == '\n' ){
            split_idx = i;
            break;
        }
    }

    // Create output
    std::string output = data.substr(split_idx);
    
    // Trim any newlines
    if( output[0] == '\n' ){
        output = output.substr(1);
    }

    return output;
}


} // End of RENDER Namespace
} // End of CLI    Namespace




