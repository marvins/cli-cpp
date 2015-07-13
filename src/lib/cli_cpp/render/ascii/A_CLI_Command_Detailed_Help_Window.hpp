/**
 * @file    A_CLI_Command_Detailed_Help_Window.hpp
 * @author  Marvin Smith
 * @date    7/3/2015
*/
#ifndef __CLI_CPP_RENDER_ASCII_A_CLI_COMMAND_DETAILED_HELP_WINDOW_HPP__
#define __CLI_CPP_RENDER_ASCII_A_CLI_COMMAND_DETAILED_HELP_WINDOW_HPP__

// CLI Libraries
#include "A_Detailed_Help_Window.hpp"
#include "../A_Render_Driver_Context_ASCII.hpp"
#include "../../cmd/A_CLI_Command.hpp"


// C++ Libraries
#include <memory>
#include <string>


namespace CLI{
namespace RENDER{

/**
 * @class A_CLI_Command_Detailed_Help_Window
*/
class A_CLI_Command_Detailed_Help_Window : public A_Detailed_Help_Window
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<A_CLI_Command_Detailed_Help_Window> ptr_t;

        
        /**
         * @brief Constructor
         *
         * @param[in] render_driver Driver containing rendering parameters.
         * @param[in] cli_command   CLI Command to print information about.
         */
        A_CLI_Command_Detailed_Help_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver,
                                        CMD::A_CLI_Command const&            command );
        

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
            return m_cli_command.Get_Formal_Name() + " Detailed Help";
        }


    private:


        /**
         * @brief Update Buffer Lines
        */
        void Update_Buffer_Lines();


        /// Class Name
        std::string m_class_name;

        /// Command
        CMD::A_CLI_Command m_cli_command;



}; // End of A_CLI_Command_Detailed_Help_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
