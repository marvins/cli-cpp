/**
 * @file    An_Alias_List_Window.hpp
 * @author  Marvin Smith
 * @date    6/20/2015
*/
#ifndef __CLI_CPP_RENDER_ASCII_AN_ALIAS_LIST_WINDOW_HPP__
#define __CLI_CPP_RENDER_ASCII_AN_ALIAS_LIST_WINDOW_HPP__


// CLI Libraries
#include "An_ASCII_Render_Window_Base.hpp"
#include "../../cmd/A_Command_Parser.hpp"
#include "../../utility/An_ASCII_Print_Table.hpp"

// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

namespace CLI{
namespace RENDER{

/**
 * @class An_Alias_List_Window
*/
class An_Alias_List_Window : public An_ASCII_Render_Window_Base
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<An_Alias_List_Window> ptr_t;


        /**
         * @brief Constructor
        */
        An_Alias_List_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver,
                              const CMD::A_Command_Parser::ptr_t      command_parser );
        
        
        /**
         * @brief Get the Window Title
        */
        inline virtual std::string  Get_Window_Title()const{
            return "CLI Alias List Window";
        }


        /**
         * @brief Update the Buffer Data
        */
        virtual void Update_Buffer_Data();
    
    
    private:

        
        /**
         * @brief Initialize the Alias List Table.
        */
        void Update_Alias_List_Table();

        
        /// Class Name
        std::string m_class_name;
        
        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;
        
        /// Render Print Managers
        UTILS::An_ASCII_Print_Table::ptr_t  m_alias_print_table;

}; // End of An_Alias_List_Window Class


} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
