/**
 * @file    A_CLI_Manager.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_CLI_Manager.hpp"


// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "../event.hpp"
#include "../handlers.hpp"
#include "../render/A_Render_Manager_ASCII.hpp"
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

    
    // Grab the rendering manager
    m_render_manager = m_configuration.Get_Render_Manager(); 
    
    
    // Set the Queue
    m_command_queue = std::make_shared<CMD::A_Command_Queue>( m_configuration.Get_Command_Queue_Max_Size() );
    
    
    // Grab the connection manager
    m_connection_manager = m_configuration.Get_Connection_Manager();
    m_connection_manager->Update_Command_Parser( m_configuration.Get_Command_Parser());
    m_connection_manager->Update_Command_Queue( m_command_queue );
    
    
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
    // Disconnect
    Disconnect();

}


/**********************************************/
/*          Connect the CLI Manager           */
/**********************************************/
void A_CLI_Manager::Connect()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    

    // Do not connect if thread is already running
    if( m_handler_thread_running == true ){
        BOOST_LOG_TRIVIAL(warning) << "CLI-Manager Handler thread already running.";
        return;
    }
    
    // Kick off the handler thread
    m_handler_thread = std::thread( &A_CLI_Manager::Process_Command_Results, 
                                    this );

    
    // For giggles, make sure the connection manager is not null
    if( m_connection_manager == nullptr ){
        throw std::runtime_error("Connection Manager was null.");
     }

    // Kick off the communication thread
    m_connection_manager->Start_Handler();
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
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
    if( m_connection_manager != nullptr ){
    
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
                m_command_handlers[i]->Process_Command( command_result );
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


/************************************************/
/*        Register Custom Render Window         */
/************************************************/
void A_CLI_Manager::Register_Custom_Render_Window( RENDER::An_ASCII_Render_Window_Base::ptr_t render_window,
                                                   CMD::A_Command const&                      command )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of method. File: " << __FILE__ << ", Class: " << m_class_name << ", Method: " << __func__ << ", Line: " << __LINE__;
    
    // Make sure the window is valid
    if( render_window == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render window is null. Ignoring.  File: " << __FILE__ << ", Class: " << m_class_name << ", Line: " << __LINE__;
        return;
    }
    if( m_custom_window_command_handler == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Custom Window Command Handler is null. Ignoring.  File: " << __FILE__ << ", Class: " << m_class_name << ", Line: " << __LINE__;
        return;
    }

    // Attach the window
    int window_id = m_render_manager->Register_Custom_Render_Window( render_window );

    // Add to the custom window handler
    m_custom_window_command_handler->Register_Trigger_Command( command, window_id );

    // Add to the command parser
    m_configuration.Get_Command_Parser()->Add_Command( command ); 
    
    
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of method. File: " << __FILE__ << ", Class: " << m_class_name << ", Method: " << __func__ << ", Line: " << __LINE__;
}

/******************************************************************/
/*          Register Internal Command Response Handlers           */
/******************************************************************/
void A_CLI_Manager::Register_Internal_Command_Response_Handlers() 
{

    // CLI Resize
    HANDLER::A_CLI_Resize_Command_Response_Handler::ptr_t cli_resize = std::make_shared<HANDLER::A_CLI_Resize_Command_Response_Handler>( m_render_manager );
    Register_Command_Response_Handler( cli_resize );
    
    // CLI Detailed Help
    HANDLER::A_CLI_Detailed_Help_Command_Response_Handler::ptr_t cli_help = std::make_shared<HANDLER::A_CLI_Detailed_Help_Command_Response_Handler>( m_render_manager );
    Register_Command_Response_Handler( cli_help );

    // Custom Window Command Response Handler
    if( m_custom_window_command_handler == nullptr ){
        m_custom_window_command_handler = std::make_shared<HANDLER::A_Custom_Window_Command_Response_Handler>( m_render_manager );
    }
    Register_Command_Response_Handler( m_custom_window_command_handler );
    

}


/******************************************************/
/*          Register Internal Event Handlers          */
/******************************************************/
void A_CLI_Manager::Register_Internal_Event_Handlers()
{

    // Add the Render-Manager's Event Handler
    EVT::Event_Manager::Register_CLI_Event_Handler( std::make_shared<EVT::A_Render_Manager_Event_Handler>( m_render_manager ));

    // Add the Connection Manager's Event Handler
    EVT::Event_Manager::Register_CLI_Event_Handler( std::make_shared<EVT::A_Connection_Manager_Event_Handler>( m_connection_manager ));

}


} // End of CLI Namespace

