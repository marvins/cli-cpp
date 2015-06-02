/**
 * @file    An_ASCII_Print_Table.cpp
 * @author  Marvin Smith
 * @date    5/24/2015
*/
#include "An_ASCII_Print_Table.hpp"

// C++ Standard Libraries
#include <iostream>
#include <stdexcept>

// CLI Libraries
#include "ANSI_Utilities.hpp"
#include "String_Utilities.hpp"

namespace CLI{
namespace UTILS{


/**************************/
/*      Constructor       */
/**************************/
An_ASCII_Print_Table_Config::An_ASCII_Print_Table_Config( const bool& blank_line_before_entry,
                                                          const bool& blank_line_after_entry )
  :  m_blank_line_before_entry( blank_line_before_entry ),
     m_blank_line_after_entry( blank_line_after_entry )
{
}


/**************************/
/*      Constructor       */
/**************************/
An_ASCII_Print_Table::An_ASCII_Print_Table( const std::vector<std::string>& column_titles,
                                            const std::vector<int>&         column_widths,
                                            const An_ASCII_Print_Table_Config& configuration )
 : m_column_titles(column_titles),
   m_column_widths(column_widths),
   m_table_data( column_titles.size() ),
   m_table_colors( column_titles.size() ),
   m_configuration(configuration),
   m_is_valid(true)
{
    
    // Check the column widths and titles
    if( column_titles.size() != column_widths.size() ){
        m_is_valid = false;
    }
}


/*******************************/
/*      Print the table        */
/*******************************/
bool An_ASCII_Print_Table::Print_Table( std::vector<std::string>&  print_data,
                                        const int&                 min_row,
                                        const int&                 max_row,
                                        const int&                 min_col ) const
{
    // Define our current row
    int cur_row = min_row;

    // Make sure the current size is large enough for the print table
    if( (int)print_data.size() <= max_row ){
        print_data.resize( max_row+1, "\n\r");
    }

    //    Create the Header, Header Line, and Blank Lines 
    std::string header_line_row = "+";
    std::string header_data_row = "|";
    std::string blank_line_row  = "|";
    
    // Iterate over each column
    for( int tcol=0; tcol < (int)m_column_titles.size(); tcol++ ){
        
        // Iterate over each position in the table
        for( int c=0; c<(m_column_widths[tcol]-1); c++ ){
            header_line_row += '-'; 
        }
        header_data_row += UTILS::Format_String( " " + m_column_titles[tcol],
                                                 m_column_widths[tcol]-1,
                                                 UTILS::StringAlignment::LEFT );
        blank_line_row += std::string( m_column_widths[tcol]-1, ' ');

        // append the extra
        header_line_row += "+";
        header_data_row += "|";
        blank_line_row  += '|';

    }

    // Print Table Header
    print_data[cur_row++] = std::string(min_col,' ') + header_line_row.c_str() + ANSI_NEWLINE;
    print_data[cur_row++] = std::string(min_col,' ') + header_data_row.c_str() + ANSI_NEWLINE;
    print_data[cur_row++] = std::string(min_col,' ') + header_line_row.c_str() + ANSI_NEWLINE;
    
    // misc variables
    bool skip_row = false;
    int current_row_entry = 0;
    std::string current_line;
    
    // Print the actual table data
    // Iterate over main window region
    for( int row = cur_row; row < max_row; row++ ){
        
        // Check if we have data left to print.  If so, print blank lines
        if( current_row_entry >= (int)m_table_data[0].size() ){
            skip_row = true; 
        }

        // Check if we need to skip the row
        if( skip_row == true ){
            skip_row = false;
            print_data[row] = std::string(min_col,' ') + blank_line_row.c_str() + ANSI_NEWLINE;
            continue;
        }


        // Reset the string
        current_line = std::string(min_col, ' ') + "|";

        // Print the data
        for( int col=0; col<(int)m_table_data.size(); col++ ){
            
            // Set the color
            //attron(COLOR_PAIR(m_table_colors[col][current_row_entry]));

            // Append column
            current_line += UTILS::Format_String( m_table_data[col][current_row_entry], 
                                                  m_column_widths[col]-1,
                                                  UTILS::StringAlignment::LEFT );
            
            // Set the color
            //attroff(COLOR_PAIR(m_table_colors[col][current_row_entry]));
            
            // Print the end
            current_line += "|";
        }
        
        if( row >= (int)print_data.size() ){
            return true;
        }
        
        // Print
        print_data[row] = current_line + ANSI_NEWLINE;

        // make blank space underneath
        if( m_configuration.Has_Blank_Line_After_Entry() == true ){
            skip_row = true;
        }

        // Increment row entry
        current_row_entry++;
        if( current_row_entry >= (int)print_data.size() ){
            return true;
        }
    }


    // Print the bottom row
    if( max_row >= (int)print_data.size() ){
        return true;
    }
    print_data[max_row] = std::string(min_col,' ') + header_line_row + ANSI_NEWLINE;

    // Return success
    return true;
}

/********************************/
/*      Add Entry to Table      */
/********************************/
void An_ASCII_Print_Table::Add_Entry( const int& row,
                                      const int& col,
                                      const std::string& data,
                                      const int& color_code )
{

    // Check column sizes
    if( col >= (int)m_table_data.size() ){
        throw std::runtime_error( "Problem in table.");
    }

    // Resize the rows if necessary
    if( (int)m_table_data[col].size() <= row ){
        for( int c=0; c<(int)m_table_data.size(); c++ ){
            m_table_data[c].resize( row+1, std::string(""));
            m_table_colors[c].resize( row+1, 0 );
        }
    }

    // Set the value
    m_table_data[col][row] = data;
    m_table_colors[col][row] = color_code;

}


/******************************/
/*       Add Blank Row        */
/******************************/
void An_ASCII_Print_Table::Add_Blank_Row( const int& row )
{
    // Check if the table is large enough
    bool table_resized = false;
    for( int col=0; col < (int)m_table_data.size(); col++ )
    {
        if( (int)m_table_data[col].size() <= row )
        {
            m_table_data[col].resize(   row+1, std::string(""));
            m_table_colors[col].resize( row+1, 0);
            table_resized = true;
        }
    }

    if( table_resized == true ){
        return;
    }

    // Insert blank rows
    for( int c=0; c<(int)m_table_data.size(); c++ )
    {
        // Insert the blank rows
        m_table_data[c].insert(   m_table_data[c].begin()   + row, std::string(""));
        m_table_colors[c].insert( m_table_colors[c].begin() + row, 0 );
    }
}


} // End of UTILS Namespace
} // End of CLI   Namespace

