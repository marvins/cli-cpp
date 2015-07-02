/**
 * @file    A_CLI_Resize_Command_Response_Handler.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_LIB_HANDLERS_A_CLI_RESIZE_COMMAND_RESPONSE_HANDLER_HPP__
#define __CLI_CPP_LIB_HANDLERS_A_CLI_RESIZE_COMMAND_RESPONSE_HANDLER_HPP__

// CLI Libraries
#include "../cli/A_Command_Response_Handler_Base.hpp"
#include "../render/A_Render_Manager_Base.hpp"

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
         *
         * @param[in] render_state Render state manager which contains the CLI Size.
         */
        A_CLI_Resize_Command_Response_Handler( RENDER::A_Render_Manager_Base::ptr_t render_manager );


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
    
        
        /// Render Manager
        RENDER::A_Render_Manager_Base::ptr_t m_render_manager;


}; // End of A_CLI_Resize_Command_Response_Handler Class


} // End of HANDLER Namespace
} // End of CLI     Namespace

#endif
