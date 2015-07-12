/**
 * @file    A_Render_Manager_Factory.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Manager_Factory.hpp"

// CLI Libraries
#include "A_Render_Manager_ASCII.hpp"
#include "../utility/Log_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace RENDER{


/***************************************/
/*      Get the Factory Instance       */
/***************************************/
A_Render_Manager_Factory& A_Render_Manager_Factory::Get_Factory_Instance()
{
    // Create static instance
    static A_Render_Manager_Factory factory_instance;

    return factory_instance;
}
    

/****************************/
/*        Initialize        */
/****************************/
void  A_Render_Manager_Factory::Initialize( CORE::ConnectionType const&             connection_type,
                                            const std::string&                      cli_title,
                                            CMD::A_Command_Parser::ptr_t            command_parser )
{
    // Create the factory
    Get_Factory_Instance() = A_Render_Manager_Factory( connection_type,
                                                       cli_title,
                                                       command_parser );

}


/**********************************/
/*        Get an Instance         */
/**********************************/
A_Render_Manager_Base::ptr_t A_Render_Manager_Factory::Instance_Of( const int& instance_id ){
    
    // Check the factory
    if( Is_Initialized() == false ){
        return nullptr;
    }

    // Get the instance
    A_Render_Manager_Factory& render_factory = Get_Factory_Instance();

    // Make sure the instance exists
    if( render_factory.m_render_managers.size() <= instance_id ){
        render_factory.m_render_managers.resize( instance_id+1, nullptr );
    }

    // Make sure the instance is not null
    if( render_factory.m_render_managers[instance_id] == nullptr ){
        render_factory.m_render_managers[instance_id] = render_factory->Create_Manager_Instance( instance_id );
    }

    // Return the instance
    return render_factory.m_render_managers[instance_id];
}


/*********************************************/
/*      Register a Custom Render Window      */
/*********************************************/
int A_Render_Manager_Factory::Register_Custom_Render_Window( An_ASCII_Render_Window_Base::ptr_t render_window ){

    // Make sure the factory exists
    if( Is_Initialized() == false ){
        return -1;
    }

    // Get the factory instance
    A_Render_Manager_Factory& render_factory = Get_Factory_Instance();

    // Add to the render list
    render_factory.m_custom_render_windows.push_back(render_window);

    // Add to existing windows
    int id;
    for( size_t i=0; i<render_factory.m_render_managers.size(); i++ ){
        id = render_factory.m_render_managers[i]->Register_Custom_Render_Window( render_window );
    }

    return id;
}


/****************************************/
/*        Check if Initialized          */
/****************************************/
bool A_Render_Manager_Factory::Is_Initialized()
{
    // Get the instance
    return Get_Factory_Instance().m_is_initialized;
}


/*******************************/
/*         Constructor         */
/*******************************/
A_Render_Manager_Factory::A_Render_Manager_Factory()
  : m_class_name("A_Render_Manager_Factory"),
    m_conn_type(CORE::ConnectionType::UNKNOWN),
    m_cli_title(""),
    m_command_parser(nullptr),
    m_is_initialized(false)
{
}


/*******************************/
/*         Constructor         */
/*******************************/
A_Render_Manager_Factory::A_Render_Manager_Factory( CORE::ConnectionType const&   connection_type,
                                                    std::string const&            cli_title,
                                                    CMD::A_Command_Parser::ptr_t  command_parser )
  : m_class_name("A_Render_Manager_Factory"),
    m_conn_type(connection_type),
    m_cli_title(cli_title),
    m_command_parser(command_parser),
    m_is_initialized(true)
{
}


/********************************/
/*      Create an Instance      */
/********************************/
A_Render_Manager_Base::ptr_t A_Render_Manager_Factory::Create_Instance( const int& instance_id )const
{

    // Create the pointer
    RENDER::A_Render_Manager_Base::ptr_t render_manager = nullptr;
 
    // Check the parser
    if( m_command_parser == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Command-Parser is currently null. File: " << __FILE__ << ", Line: " << __LINE__ << ".";
        return nullptr;
    }

    // Create the ASCII Render
    if( m_conn_type == CORE::ConnectionType::SOCKET ){
        render_manager = std::make_shared<RENDER::A_Render_Manager_ASCII>( instance_id,
                                                                           m_command_parser );
    }


    // Return Null
    else{
        return nullptr;
    }
    
    // Register the custom windows
    for( size_t i=0; i<m_custom_render_windows.size(); i++ ){
        render_manager->Register_Custom_Render_Window( m_custom_render_windows[i] );
    }


    // Return the manager
    return render_manager;
}

} // End of RENDER Namespace
} // End of CLI    Namespace

