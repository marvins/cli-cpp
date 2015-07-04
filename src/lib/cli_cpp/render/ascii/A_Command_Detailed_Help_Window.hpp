/**
 * @file    A_Command_Detailed_Help_Window.hpp
 * @author  Marvin Smith
 * @date    7/3/2015
*/
#ifndef __CLI_CPP_RENDER_ASCII_A_COMMAND_DETAILED_HELP_WINDOW_HPP__
#define __CLI_CPP_RENDER_ASCII_A_COMMAND_DETAILED_HELP_WINDOW_HPP__

// CLI Libraries
#include "A_Detailed_Help_Window.hpp"
#include "../A_Render_Driver_Context_ASCII.hpp"


// C++ Libraries
#include <memory>
#include <string>


namespace CLI{
namespace RENDER{

/**
 * @class A_Command_Detailed_Help_Window
*/
class A_Command_Detailed_Help_Window : public A_Detailed_Help_Window
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Command_Detailed_Help_Window> ptr_t;

        
        /**
         * @brief Constructor
         *
         * @param[in] render_driver Driver containing rendering parameters.
         * @param[in] command       Command to print information about.
         */
        A_Command_Detailed_Help_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver,
                                        CMD::A_Command const&                command );
        

        /**
         * @brief Update the buffer data.
         */
        virtual void Update_Buffer_Data();


    private:


        /**
         * @brief Update Buffer Lines
        */
        void Update_Buffer_Lines();


        /// Class Name
        std::string m_class_name;

        /// Command
        CMD::A_Command m_command;



}; // End of A_Command_Detailed_Help_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
