/**
 * @file    A_General_Help_Window.hpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#ifndef __CLI_CPP_RENDER_ASCII_A_GENERAL_HELP_WINDOW_HPP__
#define __CLI_CPP_RENDER_ASCII_A_GENERAL_HELP_WINDOW_HPP__

// CLI Libraries
#include "An_ASCII_Render_Window_Base.hpp"
#include "../../cmd/A_CLI_Command.hpp"
#include "../../cmd/A_Command.hpp"
#include "../../utility/An_ASCII_Print_Table.hpp"

// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

namespace CLI{
namespace RENDER{

/**
 * @class A_General_Help_Window
*/
class A_General_Help_Window : public An_ASCII_Render_Window_Base
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<A_General_Help_Window> ptr_t;


        /**
         * @brief Constructor
        */
        A_General_Help_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver,
                               const std::vector<CMD::A_CLI_Command>&  cli_command_list,
                               const std::vector<CMD::A_Command>&      command_list );


    private:


        void Initialize_CLI_Command_Table();

        void Initialize_Command_Table();

        
        /// Class Name
        std::string m_class_name;
        
        
        /// CLI Command LIst
        std::vector<CMD::A_CLI_Command> m_cli_command_list;

        /// Command List
        std::vector<CMD::A_Command> m_command_list;

        /// Render Print Managers
        UTILS::An_ASCII_Print_Table::ptr_t  m_command_print_table;
        UTILS::An_ASCII_Print_Table::ptr_t  m_cli_command_print_table;

}; // End of A_General_Help_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
