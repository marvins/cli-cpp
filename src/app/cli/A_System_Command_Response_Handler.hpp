/**
 * @file    A_System_Command_Response_Handler.hpp
 * @author  Marvin Smith
 * @date    6/2/2015
 */
#ifndef __CLI_A_SYSTEM_COMMAND_RESPONSE_HANDLER_HPP__
#define __CLI_A_SYSTEM_COMMAND_RESPONSE_HANDLER_HPP__

// CLI Libraries
#include <cli_cpp/cli/A_Command_Response_Handler_Base.hpp>

// Demo Libraries
#include "../core/State_Manager.hpp"


/**
 * @class A_System_Command_Response_Handler
 */
class A_System_Command_Response_Handler : public CLI::A_Command_Response_Handler_Base 
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_System_Command_Response_Handler> ptr_t;


        /**
         * @brief Constructor
         */
        A_System_Command_Response_Handler( State_Manager& state_manager );


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
        
        /// State Manager
        State_Manager& m_state_manager;

}; // End of A_System_Command_Response_Handler Class


#endif
