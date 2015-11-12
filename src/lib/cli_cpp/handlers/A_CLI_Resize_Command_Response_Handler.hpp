/**
 * @file    A_CLI_Resize_Command_Response_Handler.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_LIB_HANDLERS_A_CLI_RESIZE_COMMAND_RESPONSE_HANDLER_HPP__
#define __CLI_CPP_LIB_HANDLERS_A_CLI_RESIZE_COMMAND_RESPONSE_HANDLER_HPP__

// CLI Libraries
#include "../cli/A_Command_Response_Handler_Base.hpp"

namespace CLI{
namespace HANDLER{

/**
 * @class A_CLI_Resize_Command_Response_Handler
*/
class A_CLI_Resize_Command_Response_Handler : public CLI::A_Command_Response_Handler_Base 
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_CLI_Resize_Command_Response_Handler> ptr_t;


        /**
         * @brief Constructor
         */
        A_CLI_Resize_Command_Response_Handler();


        /**
         * @brief Check if valid.
         */
        virtual bool Is_Supported( const CLI::CMD::A_Command_Result& command )const;


        /**
         * @brief Process the Command
         */
        virtual void Process_Command( CLI::CMD::A_Command_Result::ptr_t command,
                                      const bool&                       wait_on_response );

    private:
        
        /// Class Name
        std::string m_class_name;

}; // End of A_CLI_Resize_Command_Response_Handler Class


} // End of HANDLER Namespace
} // End of CLI     Namespace

#endif
