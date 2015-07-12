/**
 * @file    A_Custom_Window_Command_Response_Handler.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_LIB_HANDLERS_A_CUSTOM_WINDOW_COMMAND_RESPONSE_HANDLER_HPP__
#define __CLI_CPP_LIB_HANDLERS_A_CUSTOM_WINDOW_COMMAND_RESPONSE_HANDLER_HPP__

// C++ Libraries
#include <map>


// CLI Libraries
#include "../cli/A_Command_Response_Handler_Base.hpp"
#include "../cmd/A_Command.hpp"


namespace CLI{
namespace HANDLER{

/**
 * @class A_Custom_Window_Command_Response_Handler
*/
class A_Custom_Window_Command_Response_Handler : public CLI::A_Command_Response_Handler_Base 
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Custom_Window_Command_Response_Handler> ptr_t;


        /**
         * @brief Constructor
         */
        A_Custom_Window_Command_Response_Handler();


        /**
         * @brief Check if valid.
         */
        virtual bool Is_Supported( const CLI::CMD::A_Command_Result& command )const;


        /**
         * @brief Process the Command
         */
        virtual void Process_Command( CLI::CMD::A_Command_Result::ptr_t command );


        /**
         * @brief Add Trigger Command.
         *
         * @param[in] command    to trigger a render window.
         * @param[in] window_id  Window ID to set in the render manager.
        */
        void Register_Trigger_Command( CMD::A_Command const& command,
                                       int const&            window_id );


    private:
        
        /// Class Name
        std::string m_class_name;
    
        
        /// List of Commands and their matching IDs.
        std::map<int,CMD::A_Command> m_trigger_commands;


}; // End of A_CLI_Resize_Command_Response_Handler Class


} // End of HANDLER Namespace
} // End of CLI     Namespace

#endif
