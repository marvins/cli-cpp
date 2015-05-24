/**
 * @file    A_CLI_Manager.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_CLI_Manager.hpp"


// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "../render/A_Render_Manager_ASCII.hpp"
#include "../render/A_Render_Manager_NCurses.hpp"


// C++ Standard Libraries
#include <iostream>


namespace CLI{


/********************************/
/*          Constructor         */
/********************************/
A_CLI_Manager::A_CLI_Manager( A_CLI_Manager_Configuration const& configuration )
  : m_class_name("A_CLI_Manager"),
    m_configuration(configuration),
    m_render_driver_context(nullptr),
    m_handler_thread_running(false)
{
    
    // Call the factory
    m_render_manager = m_configuration.Get_Render_Manager(); 

    // Set the Queue
    m_command_queue = std::make_shared<CMD::A_Command_Queue>( m_configuration.Get_Command_Queue_Max_Size() );
    
    // Grab the connection handler
    m_connection_manager = m_configuration.Get_Connection_Manager();
    m_connection_manager->Update_Render_Manager( m_configuration.Get_Render_Manager() );
    m_connection_manager->Update_Command_Parser( m_configuration.Get_Command_Parser());
    m_connection_manager->Update_Command_Queue( m_command_queue );

}


/**********************************************/
/*          Connect the CLI Manager           */
/**********************************************/
void A_CLI_Manager::Connect()
{
    
    // Configure the Render Context
    m_render_manager->Update_Render_Driver_Context( m_render_driver_context );
    
    // Kick off the handler thread
    m_handler_thread = std::thread( &A_CLI_Manager::Process_Command_Results, 
                                    this );


    // Kick off the communication thread
    m_connection_manager->Start_Handler();
    
}



/**********************************************/
/*        Disconnect the CLI Manager          */
/**********************************************/
void A_CLI_Manager::Disconnect()
{
    
    // Stop the thread
    m_connection_manager->Signal_Shutdown();

    // Join the thread
    m_connection_manager->Wait_Shutdown();

    // Stop the handler thread
    if( m_handler_thread_running == true ){
        m_handler_thread_running = false;
        m_command_queue->Clear();
        m_handler_thread.join();
    }

}


/************************************************/
/*      Wait for CLI Connection Shutdown        */
/************************************************/
void A_CLI_Manager::Wait_Shutdown()
{
    // Wait for the connection handler to stop
    m_connection_manager->Wait_Shutdown();
}


/************************************/
/*      Process Command Results     */
/************************************/
void A_CLI_Manager::Process_Command_Results()
{
    
    // Misc Variables
    CMD::A_Command_Result::ptr_t command_result;

    // Set flag
    m_handler_thread_running = true;

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
}


/*******************************************************/
/*          Register Command Response Handler          */
/*******************************************************/
void A_CLI_Manager::Register_Command_Response_Handler( A_Command_Response_Handler_Base::ptr_t handler )
{

    // Add to the list
    m_command_handlers.push_back( handler );


}


} // End of CLI Namespace

