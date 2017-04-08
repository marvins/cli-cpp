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
    // Create instance
    static A_Render_Manager_Factory factory_instance;

    // Return the instance
    return factory_instance;
}


/****************************/
/*        Initialize        */
/****************************/
void  A_Render_Manager_Factory::Initialize( CORE::ConnectionType const&             connection_type,
                                            const std::string&                      cli_title,
                                            CMD::A_Command_Parser::ptr_t            command_parser,
                                            CMD::A_Command_Queue::ptr_t             command_queue )
{
    // Get the initial instance
    A_Render_Manager_Factory& factory_instance = Get_Factory_Instance();

    // Update the internal values
    factory_instance.m_conn_type      = connection_type;
    factory_instance.m_cli_title      = cli_title;
    factory_instance.m_command_parser = command_parser;
    factory_instance.m_command_queue  = command_queue;

    // Set the initialized value to true
    factory_instance.m_is_initialized = true;

}


/*********************************/
/*           Finalize            */
/*********************************/
void A_Render_Manager_Factory::Finalize()
{
    // Log Entry
    const std::string m_class_name = "A_Render_Manager_Factory";
    CLI_LOG_CLASS_ENTRY();

    // Get instance
    A_Render_Manager_Factory& factory_instance = Get_Factory_Instance();

    // Reset
    factory_instance = A_Render_Manager_Factory();

    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/**********************************/
/*        Get an Instance         */
/**********************************/
A_Render_Manager_Base::ptr_t A_Render_Manager_Factory::Instance_Of( const int& instance_id )
{
    // Log Entry
    const std::string m_class_name = "A_Render_Manager_Factory";
    CLI_LOG_CLASS( trace,
                   "Start of Method.  Instance-ID: "
                   + std::to_string(instance_id));

    // Misc Variables
    A_Render_Manager_Base::ptr_t result = nullptr;


    // Check the factory
    if( Is_Initialized() == false )
    {
        CLI_LOG_CLASS( error,
                       "Render-Manager Factory is uninitialized.");
    }
    else
    {

        // Get the instance
        A_Render_Manager_Factory& render_factory = Get_Factory_Instance();

        // Make sure the instance exists
        if( (int)render_factory.m_render_managers.size() <= instance_id )
        {
            render_factory.m_render_managers.resize( instance_id+1, nullptr );
        }

        // Make sure the instance is not null
        if( render_factory.m_render_managers[instance_id] == nullptr )
        {
            render_factory.m_render_managers[instance_id] = render_factory.Create_Manager_Instance( instance_id );
        }

        // Return the instance
        result = render_factory.m_render_managers[instance_id];
    }


    return result;
}


/*********************************************/
/*      Register a Custom Render Window      */
/*********************************************/
int A_Render_Manager_Factory::Register_Custom_Render_Window( An_ASCII_Render_Window_Base::ptr_t render_window )
{
    // Log Entry
    const std::string m_class_name = "A_Render_Manager_Factory";
    CLI_LOG_CLASS_ENTRY();

    // Misc Variables
    int id = -1;

    // Make sure the factory exists
    if( Is_Initialized() == false )
    {
        CLI_LOG_CLASS( error,
                       "Unable to add window as Render-Manager Factory is uninitialized.");
    }

    // Otherwise, continue
    else
    {
        // Get the factory instance
        A_Render_Manager_Factory& render_factory = Get_Factory_Instance();

        // Add to the render list
        render_factory.m_custom_render_windows.push_back(render_window);

        // Make sure we have at least one render manager
        if( render_factory.m_render_managers.size() <= 0 )
        {
            CLI_LOG_CLASS( warning,
                           "No render-managers available in render-factory.");
        }

        // Otherwise, continue
        else
        {

            // Add to existing windows
            bool exit_loop = false;
            for( size_t i=0; i<render_factory.m_render_managers.size() && !exit_loop; i++ )
            {
                id = render_factory.m_render_managers[i]->Register_Custom_Render_Window( render_window );
                exit_loop = true;
            }
        }
    }

    // Check for error
    if( id < 0 )
    {
        CLI_LOG_CLASS( error,
                       "Problem registering window. Window-ID: " + std::to_string(id));
    }


    return id;
}


/****************************************/
/*       Send Asynchronous Message      */
/****************************************/
void A_Render_Manager_Factory::Send_Asynchronous_Message( const std::string& topic_name,
                                                          const std::string& message )
{
    // Log Entry
    const std::string m_class_name = "A_Render_Manager_Factory";
    CLI_LOG_CLASS_ENTRY();


    // Make sure the factory exists
    if( Is_Initialized() == false )
    {
        CLI_LOG_CLASS( error,
                       "Unable to Send-Message as Render-Manager Factory is uninitialized.");
    }

    // Otherwise, continue
    else
    {
        // Get the factory instance
        A_Render_Manager_Factory& render_factory = Get_Factory_Instance();


        // Make sure we have at least one render manager
        if( render_factory.m_render_managers.size() <= 0 )
        {
            CLI_LOG_CLASS( warning,
                           "No render-managers available in render-factory.");
        }

        // Otherwise, continue
        else
        {

            // Send message to each render-manager.
            for( size_t i=0; i<render_factory.m_render_managers.size(); i++ )
            {
                render_factory.m_render_managers[i]->Send_Asynchronous_Message( topic_name,
                                                                                message );
            }
        }
    }

    // Log Exit
    CLI_LOG_CLASS_EXIT();
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
    m_command_queue(nullptr),
    m_is_initialized(false)
{
}


/********************************/
/*      Create an Instance      */
/********************************/
A_Render_Manager_Base::ptr_t A_Render_Manager_Factory::Create_Manager_Instance( const int& instance_id )const
{
    // Log Entry
    const std::string m_class_name = "A_Render_Manager_Factory";
    CLI_LOG_CLASS( trace,
                   "Start of Method.  Instance-ID: " + std::to_string(instance_id));

    // Create the pointer
    RENDER::A_Render_Manager_Base::ptr_t render_manager = nullptr;

    // Check the parser
    if( m_command_parser == nullptr )
    {
        CLI_LOG_CLASS( error,
                       "Command-Parser is currently null.");
    }

    // Create the ASCII Render
    else if( m_conn_type == CORE::ConnectionType::SOCKET )
    {
        render_manager = std::make_shared<RENDER::A_Render_Manager_ASCII>( instance_id,
                                                                           m_command_parser,
                                                                           m_command_queue );
    }


    // Return Null
    else
    {
        CLI_LOG_CLASS( error,
                       "Unknown Connection-Type.");
    }

    // Continue only if render-manager is not null
    if( render_manager != nullptr )
    {
        // Initialize
        render_manager->Initialize();
        int wid;

        // Register the custom windows
        for( size_t i=0; i<m_custom_render_windows.size(); i++ )
        {
            wid = render_manager->Register_Custom_Render_Window( m_custom_render_windows[i] );
        }

    }

    // Return the manager
    return render_manager;
}

} // End of RENDER Namespace
} // End of CLI    Namespace
