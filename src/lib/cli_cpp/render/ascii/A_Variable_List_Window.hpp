/**
 * @file    A_Variable_List_Window.hpp
 * @author  Marvin Smith
 * @date    7/20/2015
*/
#ifndef __CLI_CPP_RENDER_ASCII_A_VARIABLE_LIST_WINDOW_HPP__
#define __CLI_CPP_RENDER_ASCII_A_VARIABLE_LIST_WINDOW_HPP__


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
 * @class A_Variable_List_Window
*/
class A_Variable_List_Window : public An_ASCII_Render_Window_Base
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Variable_List_Window> ptr_t;


        /**
         * @brief Constructor
         *
         * @param[in] render_driver Rendering driver containing the window size.
         * @param[in] command_parser Command-Parser containing the variable list.
        */
        A_Variable_List_Window( A_Render_Driver_Context_ASCII::ptr_t    render_driver,
                                const CMD::A_Command_Parser::ptr_t      command_parser );
        
        
        /**
         * @brief Get the Window Title
         *
         * @return Window-Title.
        */
        inline virtual std::string  Get_Window_Title()const{
            return "CLI Variable List Window";
        }


        /**
         * @brief Update the Buffer Data
        */
        virtual void Update_Buffer_Data();
    
    
    private:

        
        /**
         * @brief Initialize the Variable List Table.
        */
        void Update_Variable_List_Table();

        
        /// Class Name
        std::string m_class_name;
        

        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;
        

        /// Render Print Managers
        UTILS::An_ASCII_Print_Table::ptr_t  m_variable_print_table;


}; // End of A_Variable_List_Window Class


} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
