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
A_CLI_Manager_Configuration::A_CLI_Manager_Configuration( CORE::ConnectionType const& cli_conn_type )
  : m_class_name("A_CLI_Manager_Configuration"),
    m_conn_type(cli_conn_type),
    m_command_parser(nullptr),
    m_render_driver_context(nullptr),
    m_render_manager(nullptr),
    m_socket_window_rows(20),
    m_socket_window_cols(80),
    m_redirect_stdout(false),
    m_redirect_stderr(false)
{
}

/***************************************************/
/*          Get the Connection Handler             */
/***************************************************/
A_Connection_Manager_Base::ptr_t  A_CLI_Manager_Configuration::Get_Connection_Manager(){

    // Make sure the configuration is not null
    if( m_connection_manager_configuration == nullptr ){
        return nullptr;
    }
        
    
    // Get the render manager
    RENDER::A_Render_Manager_Base::ptr_t render_manager = this->Get_Render_Manager();

    // If we are socket, create the handler
    if( m_conn_type == CORE::ConnectionType::SOCKET )
    {
        return std::make_shared<A_Connection_Manager_Socket>( m_connection_manager_configuration, 
                                                              render_manager );
    }

    // otherwise, return null
    return nullptr;

}


/************************************/
/*       Create NCurses Context     */
/************************************/
RENDER::A_Render_Manager_Base::ptr_t  A_CLI_Manager_Configuration::Get_Render_Manager()
{
    // Create the render driver context
    if( m_render_driver_context == nullptr ){
        m_render_driver_context = RENDER::A_Render_Driver_Context_Factory::Initialize( m_conn_type,
                                                                                       m_cli_title,
                                                                                       m_socket_window_rows,
                                                                                       m_socket_window_cols,
                                                                                       m_redirect_stdout,
                                                                                       m_redirect_stderr );
    }

    // Run the factory
    if( m_render_manager == nullptr ){
        m_render_manager = RENDER::A_Render_Manager_Factory::Initialize( m_conn_type,
                                                                         m_cli_title,
                                                                         m_command_parser,
                                                                         m_render_driver_context );
        
        // Initialize
        m_render_manager->Initialize();
    
    }

    return m_render_manager;
}


/************************************************************/
/*          Check if the configuration is valid             */
/************************************************************/
bool A_CLI_Manager_Configuration::Is_Valid()const
{
    // Check if the configuration is null
    if( m_connection_manager_configuration == nullptr ){
        return false;
    }


    // If no failures, yet, then success
    return true;
}


} // End of CLI Namespace
