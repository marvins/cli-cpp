/**
 * @file    A_Main_Window.hpp
 * @author  Marvin Smith
 * @date    5/30/2015
 */
#ifndef __CLI_CPP_RENDER_ASCII_A_MAIN_WINDOW_HPP__
#define __CLI_CPP_RENDER_ASCII_A_MAIN_WINDOW_HPP__

// CLI Libraries
#include "An_ASCII_Render_Window_Base.hpp"
#include "An_ASCII_History_Window.hpp"

namespace CLI{
namespace RENDER{

/**
 * @class A_Main_Window
*/
class A_Main_Window : public An_ASCII_Render_Window_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Main_Window> ptr_t;
        
        /**
         * @brief Constructor
        */
        A_Main_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver,
                       CMD::A_Command_History::ptr_t        command_history );
    
        /**
         * @brief Retrieve the buffer data
        */
        virtual std::vector<std::string>& Get_Buffer_Data();


    protected:
        
        /**
         * @brief Print the Main Content.
         */
        void Print_Main_Content();


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Command History
        CMD::A_Command_History::ptr_t m_command_history;

        /// History Window
        An_ASCII_History_Window::ptr_t m_history_window;

        /// Shortcut print line
        std::string m_shortcut_print_line;


}; // End of A_Main_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace


#endif
