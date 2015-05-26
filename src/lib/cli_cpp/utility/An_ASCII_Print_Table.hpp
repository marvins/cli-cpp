/**
 * @file    An_ASCII_Print_Table.hpp
 * @author  Marvin Smith
 * @date    5/23/2015
*/
#ifndef __CLI_CPP_LIB_UTILITY_AN_ASCII_PRINT_TABLE_HPP__
#define __CLI_CPP_LIB_UTILITY_AN_ASCII_PRINT_TABLE_HPP__


// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

namespace CLI{
namespace UTILS{

/**
 * @class An_ASCII_Print_Table_Config
*/
class An_ASCII_Print_Table_Config
{
    public:
        
        /**
         * @brief Constructor
        */
        An_ASCII_Print_Table_Config( const bool& blank_line_before_entry = true,
                                     const bool& blank_line_after_entry  = true );
        

        /**
         * @brief Check if we need to have a blank line before the entry.
         */
        inline bool Has_Blank_Line_Before_Entry()const{
            return m_blank_line_before_entry;
        }
        
        
        /**
         * @brief Check if we need to have a blank line after the entry.
         */
        inline bool Has_Blank_Line_After_Entry()const{
            return m_blank_line_after_entry;
        }

    private:
        
        /// Blank line before entry
        bool m_blank_line_before_entry;

        /// Blank line after entry
        bool m_blank_line_after_entry;

}; // End of An_ASCII_Print_Table_Config Class

/**
 * @class An_ASCII_Print_Table
 */
class An_ASCII_Print_Table
{

    public:
        

        /// Pointer Type
        typedef std::shared_ptr<An_ASCII_Print_Table> ptr_t;

        /**
         * @brief Constructor
         */
        An_ASCII_Print_Table( std::vector<std::string>const&      column_titles,
                              std::vector<int> const&             column_widths,
                              An_ASCII_Print_Table_Config const&  configuration = An_ASCII_Print_Table_Config());

        
        /**
         * @brief Return a formatted string for printing.
         */
        bool Print_Table( std::vector<std::string>& print_data,
                          const int& min_row,
                          const int& max_row,
                          const int& min_col )const;

        /**
         * @brief Add Entry
        */
        void Add_Entry( const int& row, 
                        const int& col, 
                        const std::string& data,
                        const int& color_code = 0 );


        /**
         * @brief Add blank entry.
         */
        void Add_Blank_Row( const int& row );


        // Get the string
        inline std::vector<std::string> Get_String_Data()const{
            return m_table_output_data;
        }
        
        
        /**
         * @brief Check if the table is valid.
         *
         * @return True if valid, false otherwise.
         */
       inline bool Is_Valid()const{
           return m_is_valid;
       }


    private:
        
        /// Column Titles
        std::vector<std::string> m_column_titles;

        /// Column Widths
        std::vector<int>         m_column_widths;

        /// Table Data
        std::vector<std::vector<std::string>> m_table_data;
        
        /// Table Color Data
        std::vector<std::vector<int>> m_table_colors;

        /// Output data
        std::vector<std::string> m_table_output_data;

        /// Configuration
        An_ASCII_Print_Table_Config m_configuration;

        ///Valid Flag
        bool m_is_valid;

}; // End of An_NCurses_Table Class

} // End of NCURSES Namespace
} // End of CLI     Namespace

#endif
