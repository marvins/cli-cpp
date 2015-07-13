/**
 * @file    A_Network_Asset_Command_Response_Handler.hpp
 * @author  Marvin Smith
 * @date    7/6/2015
*/
#ifndef __CLI_CPP_APP_A_NETWORK_ASSET_COMMAND_RESPONSE_HANDLER_HPP__
#define __CLI_CPP_APP_A_NETWORK_ASSET_COMMAND_RESPONSE_HANDLER_HPP__


// CLI Libraries
#include <cli_cpp/cli/A_Command_Response_Handler_Base.hpp>

// Demo Application Libraries
#include "../utils/Network_Scanner.hpp"

// C++ Libraries
#include <string>


/**
 * @class A_Network_Asset_Command_Response_Handler
*/
class A_Network_Asset_Command_Response_Handler : public CLI::A_Command_Response_Handler_Base 
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Network_Asset_Command_Response_Handler> ptr_t;


        /**
         * @brief Constructor.
         *
         * @param[in] network_scanner Network scanner to manage.
         */
        A_Network_Asset_Command_Response_Handler( Network_Scanner::ptr_t m_network_scanner );


        /**
         * @brief Check if valid.
         */
        virtual bool Is_Supported( const CLI::CMD::A_Command_Result& command )const;


        /**
         * @brief Process the Command
         */
        virtual void Process_Command( CLI::CMD::A_Command_Result::ptr_t command );

    private:

        /// Class Name
        std::string m_class_name;

        /// Network Scanner
        Network_Scanner::ptr_t m_network_scanner;

}; // End of A_Network_Asset_Command_Response_Handler Class

#endif
