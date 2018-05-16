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
      m_command_parser(nullptr)
{
}


/***************************/
/*      Constructor        */
/***************************/
A_CLI_Manager_Configuration::A_CLI_Manager_Configuration( std::vector<A_Connection_Manager_Base_Config::ptr_t> connection_configs,
                                                          std::map<CORE::SessionType,
                                                                   RENDER::Render_Driver_Config_Base::ptr_t>   render_driver_configs,
                                                          CMD::A_Command_Parser::ptr_t                         command_parser,
                                                          CMD::A_Command_Queue_Config                          command_queue_config,
                                                          EVT::Event_Manager_Config                            event_manager_config )
  : m_class_name("A_CLI_Manager_Configuration"),
    m_connection_manager_configurations(connection_configs),
    m_render_driver_configs(render_driver_configs),
    m_command_parser(command_parser),
    m_event_manager_config(event_manager_config),
    m_command_queue_config(command_queue_config)
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


/********************************************/
/*          Print to Logging String         */
/********************************************/
std::string A_CLI_Manager_Configuration::To_Log_String(int offset) const
{
    std::string gap(offset, ' ');
    
    std::stringstream sin;
    
    sin << gap << " - " << m_class_name << std::endl;
    sin << gap << "     - Connection-Manager Configs (" << m_connection_manager_configurations.size() << ")" << std::endl;
    for( auto config : m_connection_manager_configurations )
    {
        sin << config->To_Log_String(offset + 4);
    }
    
    return sin.str();
}

} // End of CLI Namespace
