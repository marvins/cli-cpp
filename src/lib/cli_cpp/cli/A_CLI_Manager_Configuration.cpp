/**
 * @file    A_CLI_Manager_Configuration.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_CLI_Manager_Configuration.hpp"

// CLI Libraries
#include "A_Connection_Manager_Socket.hpp"
#include "../render/A_Render_Driver_Context_Factory.hpp"
#include "../render/A_Render_Manager_Factory.hpp"

// C++ Standard Libraries
#include <iostream>
#include <unistd.h>


namespace CLI{


/***************************/
/*      Constructor        */
/***************************/
A_CLI_Manager_Configuration::A_CLI_Manager_Configuration()
  : m_class_name("A_CLI_Manager_Configuration"),
    m_command_parser(nullptr),
    m_redirect_stdout(false),
    m_redirect_stderr(false),
    m_async_message_refresh_time(500)
{
}


/************************************************************/
/*          Check if the configuration is valid             */
/************************************************************/
bool A_CLI_Manager_Configuration::Is_Valid()const
{
    // Check if the configuration is null
    if( m_connection_manager_configurations.empty() )
    {
        return false;
    }
    for( auto mgr_conf : m_connection_manager_configurations )
    {
        if( mgr_conf == nullptr ){
            return false;
        }
    }


    // If no failures, yet, then success
    return true;
}


} // End of CLI Namespace
