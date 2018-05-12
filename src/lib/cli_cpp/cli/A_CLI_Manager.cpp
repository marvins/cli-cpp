/**
 * @file    A_CLI_Manager.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_CLI_Manager.hpp"


// CLI Libraries
#include "A_Connection_Manager_Socket.hpp"
#include "../event.hpp"
#include "../handlers.hpp"
#include "../render/A_Render_Driver_Context_Factory.hpp"
#include "../render/A_Render_Manager_Factory.hpp"
#include "../render/A_Render_State_Factory.hpp"
#include "../utility/Log_Utilities.hpp"


// C++ Standard Libraries
#include <iostream>


namespace CLI{


/********************************/
/*          Constructor         */
/********************************/
A_CLI_Manager::A_CLI_Manager( A_CLI_Manager_Configuration const& configuration )
  : m_class_name("A_CLI_Manager"),
    m_configuration(configuration),
    m_handler_thread_running(false),
    m_custom_window_command_handler(nullptr)
{

    // Register the event manager
    if( EVT::Event_Manager::Is_Initialized() != true ){
        EVT::Event_Manager::Initialize( configuration.Get_Event_Manager_Config() );
    }


    // Build the internal command queue
    m_command_queue = std::make_shared<CMD::A_Command_Queue>( m_configuration.Get_Command_Queue_Config() );


    // Initialize the Render-Driver Context Factory
    RENDER::A_Render_Driver_Context_Factory::Initialize( configuration.Get_Render_Configs(),
                                                         configuration.Get_CLI_Title(),
                                                         configuration.Get_Socket_Window_Rows(),
                                                         configuration.Get_Socket_Window_Cols(),
                                                         configuration.Get_Redirect_stdout(),
                                                         configuration.Get_Redirect_stdout(),
                                                         configuration.Get_Async_Message_Refresh_Time());


    // Initialize the Render-State Factory
    RENDER::A_Render_State_Factory::Initialize( m_configuration.Get_Command_Parser() );


    // Initialize the Render-Manager Factory
    RENDER::A_Render_Manager_Factory::Initialize( m_configuration.Get_Connection_Type(),
                                                  m_configuration.Get_CLI_Title(),
                                                  m_configuration.Get_Command_Parser(),
                                                  m_command_queue );


    // Initialize the connection manager
    Initialize_Connection_Manager();


    // Add the Required Event Handlers
    Register_Internal_Event_Handlers();


    // Add the Required Command Response Handler
    Register_Internal_Command_Response_Handlers();

}


/**********************************/
/*           Destructor           */
/**********************************/
A_CLI_Manager::~A_CLI_Manager()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Disconnect
    Disconnect();


    // Clear the render manager factory
    RENDER::A_Render_Manager_Factory::Finalize();


    // Clear the render state factory
    RENDER::A_Render_State_Factory::Finalize();


    // Clear the context factory
    RENDER::A_Render_Driver_Context_Factory::Finalize();


    // Finalize the Event Manager
    EVT::Event_Manager::Finalize();

    // Destroy the command queue
    m_command_queue.reset();

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/**********************************************/
/*          Connect the CLI Manager           */
/**********************************************/
void A_CLI_Manager::Connect()
{
    // Log Entry
    CLI_LOG_CLASS_ENTRY();


    // Do not connect if thread is already running
    if( m_handler_thread_running == true )
    {
        BOOST_LOG_TRIVIAL(warning) << "CLI-Manager Handler thread already running.";
        return;
    }

    // Kick off the handler thread
    m_handler_thread = std::thread( &A_CLI_Manager::Process_Command_Results,
                                    this );


    // For giggles, make sure the connection manager is not null
    if( m_connection_manager == nullptr )
    {
        throw std::runtime_error("Connection Manager was null.");
    }

    // Kick off the communication thread
    m_connection_manager->Start_Handler();

    // Log Exit
    CLI_LOG_CLASS_EXIT();
}



/**********************************************/
/*        Disconnect the CLI Manager          */
/**********************************************/
void A_CLI_Manager::Disconnect()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Disable the Event Manager
    EVT::Event_Manager::Finalize();

    // Make sure the connection manager is not already de-allocated
    if( m_connection_manager != nullptr )
    {

        // Stop the thread
        m_connection_manager->Signal_Shutdown();

        // Join the thread
        m_connection_manager->Wait_Shutdown();
    }

    BOOST_LOG_TRIVIAL(trace) << "Halting Queue Thread. Func: " << __func__ << ", File: " << __FILE__ << ", Line: " << __LINE__;

    // Stop the handler thread
    if( m_handler_thread_running == true ){

        // Set the running condition to false
        m_handler_thread_running = false;


        // Clear the queue
        if( m_command_queue != nullptr ){
            m_command_queue->Clear();
        }

        // Join the thread
        m_handler_thread.join();
    }

    // Remove all command handlers
    m_command_handlers.clear();

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

}


/************************************************/
/*      Wait for CLI Connection Shutdown        */
/************************************************/
void A_CLI_Manager::Wait_Shutdown()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;


    // Wait for the connection handler to stop
    m_connection_manager->Wait_Shutdown();


    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/************************************/
/*      Process Command Results     */
/************************************/
void A_CLI_Manager::Process_Command_Results()
{

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;


    // Misc Variables
    CMD::A_Command_Result::ptr_t command_result;


    // Set flag
    m_handler_thread_running = true;


    // Run until it is time to quit
    while( m_handler_thread_running != false ){

        // Pop the next command
        command_result = m_command_queue->Pop_Command();

        // Check if null
        if( command_result == nullptr ){
            continue;
        }

        // Process Command
        for( size_t i=0; i<m_command_handlers.size(); i++ ){
            if( m_command_handlers[i]->Is_Supported( *command_result ) == true )
            {
                m_command_handlers[i]->Process_Command( command_result, false );
            }
        }
    }

    // Set flag
    m_handler_thread_running = false;


    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/*******************************************************/
/*          Register Command Response Handler          */
/*******************************************************/
void A_CLI_Manager::Register_Command_Response_Handler( A_Command_Response_Handler_Base::ptr_t handler )
{

    // Add to the list
    m_command_handlers.push_back( handler );

}


/******************************************************/
/*          Register Session Response Handler         */
/******************************************************/
void A_CLI_Manager::Register_Session_Event_Handler( A_Session_Event_Handler_Base::ptr_t handler )
{



}


/************************************************/
/*        Register Custom Render Window         */
/************************************************/
bool A_CLI_Manager::Register_Custom_Render_Window( RENDER::An_ASCII_Render_Window_Base::ptr_t render_window,
                                                   CMD::A_Command const&                      command )
{
    // Log Entry
    CLI_LOG_CLASS_ENTRY();

    // Misc Vars
    bool result = true;

    // Make sure the window is valid
    if( render_window == nullptr ){
        CLI_LOG_CLASS( error,
                       "Render window is null. Ignoring.");
        result = false;
    }

    // Make sure the window command handler was created
    else if( m_custom_window_command_handler == nullptr )
    {
        CLI_LOG_CLASS( error,
                       "Custom Window Command Handler is null. Ignoring.");
        result = false;
    }

    // Otherwise, handle
    else
    {

        // Attach the window
        int window_id = RENDER::A_Render_Manager_Factory::Register_Custom_Render_Window( render_window );

        // Add to the custom window handler
        m_custom_window_command_handler->Register_Trigger_Command( command, window_id );

        // Add to the command parser
        m_configuration.Get_Command_Parser()->Add_Command( command );

    }

    // Log Exit and return
    CLI_LOG_CLASS_EXIT();

    return result;
}


/****************************************************/
/*           Send an Asynchronous Message           */
/****************************************************/
void A_CLI_Manager::Send_Asynchronous_Message( const std::string& topic_name,
                                               const std::string& message )
{
    // Log Entry
    CLI_LOG_CLASS_ENTRY();

    // Check the initialization status
    if( !EVT::Event_Manager::Is_Initialized() )
    {
        CLI_LOG_CLASS( error, "CLI-Manager has already been disconnected.");
    }

    else
    {
        // Attach the window
        RENDER::A_Render_Manager_Factory::Send_Asynchronous_Message(topic_name,
                                                                    message);

        // Refresh Screens
        m_connection_manager->Refresh_Screens();
    }

    // Log Exit and return
    CLI_LOG_CLASS_EXIT();

}


/************************************************/
/*          Get Active Session List             */
/************************************************/
std::vector<CORE::Session> A_CLI_Manager::Get_Active_Session_List()const
{
    // Make sure we have been connected
    if( m_connection_manager == nullptr ){
        return std::vector<CORE::Session>();
    }

    // Otherwise, continue
    return m_connection_manager->Get_Active_Session_List();
}


/******************************************************************/
/*          Register Internal Command Response Handlers           */
/******************************************************************/
void A_CLI_Manager::Register_Internal_Command_Response_Handlers()
{

    // CLI Resize
    HANDLER::A_CLI_Resize_Command_Response_Handler::ptr_t cli_resize = std::make_shared<HANDLER::A_CLI_Resize_Command_Response_Handler>();
    Register_Command_Response_Handler( cli_resize );

    // CLI Detailed Help
    HANDLER::A_CLI_Detailed_Help_Command_Response_Handler::ptr_t cli_help = std::make_shared<HANDLER::A_CLI_Detailed_Help_Command_Response_Handler>();
    Register_Command_Response_Handler( cli_help );

    // Custom Window Command Response Handler
    if( m_custom_window_command_handler == nullptr ){
        m_custom_window_command_handler = std::make_shared<HANDLER::A_Custom_Window_Command_Response_Handler>();
    }
    Register_Command_Response_Handler( m_custom_window_command_handler );


}


/******************************************************/
/*          Register Internal Event Handlers          */
/******************************************************/
void A_CLI_Manager::Register_Internal_Event_Handlers()
{

    // Add the Render-Manager's Event Handler
    EVT::Event_Manager::Register_CLI_Event_Handler( std::make_shared<EVT::A_Render_Manager_Event_Handler>());

    // Add the Connection Manager's Event Handler
    EVT::Event_Manager::Register_CLI_Event_Handler( std::make_shared<EVT::A_Connection_Manager_Event_Handler>( m_connection_manager ));

}


/*****************************************************/
/*         Initialize the Connection Manager         */
/*****************************************************/
void A_CLI_Manager::Initialize_Connection_Manager()
{

    // If we are socket, create the handler
    if( m_configuration.Get_Connection_Type() == CORE::ConnectionType::SOCKET )
    {
        m_connection_manager = std::make_shared<A_Connection_Manager_Socket>( m_configuration.Get_Connection_Manager_Config() );
    }

    else{
        throw std::runtime_error("invalid connection type.");
    }

}



} // End of CLI Namespace
