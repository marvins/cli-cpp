/**
 * @file    An_ASCII_Help_Menu.hpp
 * @author  Marvin Smith
 * @date    5/25/2015
*/
#ifndef __CLI_CPP_RENDER_ASCII_AN_ASCII_HELP_MENU_HPP__
#define __CLI_CPP_RENDER_ASCII_AN_ASCII_HELP_MENU_HPP__

// CLI Libraries
#include "../../cmd/A_CLI_Command.hpp"
#include "../../cmd/A_Command.hpp"
#include "../../utility/An_ASCII_Print_Table.hpp"
#include "../../utility/ANSI_Utilities.hpp"
#include "../../utility/String_Utilities.hpp"

// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

namespace CLI{
namespace RENDER{
namespace ASCII{


/**
 * @class An_ASCII_Help_Menu
*/
class An_ASCII_Help_Menu{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<An_ASCII_Help_Menu> ptr_t;


        /**
         * @brief Create the Menu.
         *
         * @param[in] cli_title Command-Line title.
        */
        An_ASCII_Help_Menu( const std::string&                      cli_title,
                            const int&                              window_rows,
                            const int&                              window_cols,
                            const int&                              min_col,
                            const int&                              min_row,
                            const int&                              max_row,
                            const std::vector<CMD::A_CLI_Command>&  cli_command_list,
                            const std::vector<CMD::A_Command>&      command_list );

        /**
         * @brief Get the buffer
        */
        inline std::vector<std::string> Get_Buffer_Data()const{
            return m_buffer_data;
        }

        /**
         * @brief Get the buffer
        */
        inline std::vector<std::string>& Get_Buffer_Data(){
            return m_buffer_data;
        }

    private:

        /**
         * @brief Initialize the Menu
        */
        void Initialize();

        void Initialize_CLI_Command_Table( int& current_row );

        void Initialize_Command_Table();

        /// Command-Line Title
        std::string m_cli_title;

        /// Window Rows
        int m_window_rows;

        /// Window Columns
        int m_window_cols;

        /// Min Column
        int m_min_col;

        /// Min Row
        int m_min_row;

        /// Max Row
        int m_max_row;

        /// CLI Command LIst
        std::vector<CMD::A_CLI_Command> m_cli_command_list;

        /// Command List
        std::vector<CMD::A_Command> m_command_list;

        /// Render Print Managers
        UTILS::An_ASCII_Print_Table::ptr_t  m_command_print_table;
        UTILS::An_ASCII_Print_Table::ptr_t  m_cli_command_print_table;
       
        /// Buffer Data
        std::vector<std::string> m_buffer_data;


}; // End of An_ASCII_Help_Menu Class


} // End of ASCII  Namespace
} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
