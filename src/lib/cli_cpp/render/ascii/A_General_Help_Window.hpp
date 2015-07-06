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
#include "../../cmd/A_Command_Parser.hpp"
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
         * @brief Constructor.
         *
         * @param[in] render_driver Driver containing rendering parameters.
         * @param[in] command_parser Command parser containing both the CLI and general commands.
        */
        A_General_Help_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver,
                               CMD::A_Command_Parser::ptr_t            command_parser );


        /**
         * @brief Update the buffer data.
         */
        virtual void Update_Buffer_Data();


        /**
         * @brief Get the Window Title.
         *
         * @return Window Title.
        */
        inline virtual std::string Get_Window_Title()const{
            return "General Help Window";
        }

    private:


        /**
         * @brief Update Buffer Lines
        */
        void Update_Buffer_Lines();

        
        /**
         * @brief Update the CLI Command Print Table.
        */
        void Update_CLI_Command_Table();

        
        /**
         * @brief Update the Command Print Table.
        */
        void Update_Command_Table();

        
        /// Class Name
        std::string m_class_name;
        
        
        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;


        /// Render Print Managers
        UTILS::An_ASCII_Print_Table::ptr_t  m_command_print_table;
        UTILS::An_ASCII_Print_Table::ptr_t  m_cli_command_print_table;

        /// Current Command List Sizes
        int m_current_command_list_size;
        int m_current_cli_command_list_size;


}; // End of A_General_Help_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
