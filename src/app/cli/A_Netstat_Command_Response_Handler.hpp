/**
 * @file    A_Netstat_Command_Response_Handler.hpp
 * @author  Marvin Smith
 * @date    5/25/2015
*/
#ifndef __CLI_CPP_APP_A_NETSTAT_COMMAND_RESPONSE_HANDLER_HPP__
#define __CLI_CPP_APP_A_NETSTAT_COMMAND_RESPONSE_HANDLER_HPP__

// CLI Libraries
#include <cli_cpp/cli/A_Command_Response_Handler_Base.hpp>

/**
 * @class A_Netstat_Command_Response_Handler
*/
class A_Netstat_Command_Response_Handler : public CLI::A_Command_Response_Handler_Base 
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Netstat_Command_Response_Handler> ptr_t;


        /**
         * @brief Constructor
         */
        A_Netstat_Command_Response_Handler();


        /**
         * @brief Check if valid.
         */
        virtual bool Is_Supported( const CLI::CMD::A_Command_Result& command )const;


        /**
         * @brief Process the Command
         */
        virtual void Process_Command( CLI::CMD::A_Command_Result::ptr_t command );


}; // End of A_Netstat_Command_Response_Handler Class

#endif
