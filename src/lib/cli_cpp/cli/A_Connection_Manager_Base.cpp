/**
 * @file    A_Connection_Manager_Base.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#include "A_Connection_Manager_Base.hpp"

// C++ Standard Libraries
#include <iostream>

// CLI Libraries
#include "../utility/Log_Utilities.hpp"

namespace CLI{


/************************/
/*      Constructor     */
/************************/
A_Connection_Manager_Base::A_Connection_Manager_Base()
  : m_is_running(false),
    m_render_manager(nullptr),
    m_command_parser(nullptr),
    m_class_name("A_Connection_Manager_Base")
{
}



/*************************/
/*       Destructor      */
/*************************/
A_Connection_Manager_Base::~A_Connection_Manager_Base()
{
}


/**************************************/
/*        Process the Command         */
/**************************************/
void A_Connection_Manager_Base::Process_Command()
{
    // Make sure the command is not blank
    if( UTILS::String_Trim( this->m_render_state->Get_Cursor_Text() ).size() <= 0 ){
        
        // Clear the string
        this->m_render_state->Clear_Cursor_Text();
        return;
    }

    // Cancel the command if we are still waiting on another command to finish
    if( this->m_render_manager->Check_Waiting_Command_Response() )
    {
        BOOST_LOG_TRIVIAL(debug) << "Waiting on response for existing command. Skipping action.";
        this->m_render_state->Clear_Cursor_Text();
        return;
    }

    // Check the command
    CMD::A_Command_Result result = m_command_parser->Evaluate_Command( this->m_render_state->Get_Cursor_Text() );
        
    // Create shared pointer
    CMD::A_Command_Result::ptr_t result_ptr = std::make_shared<CMD::A_Command_Result>( result );
    
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ << ", Command Result: " << result.To_Debug_String();

    // Add to history
    this->m_render_manager->Add_Command_History( this->m_render_state->Get_Cursor_Text(), 
                                                 result_ptr );

    //  Look for CLI Shutdown
    if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_SHUTDOWN ){
        m_is_running = false;
        std::cout << "shutdown requested" << std::endl;
    }

    
    // Look for other CLI Command
    else if( CMD::Is_Valid_CLI_Command( result.Get_Parse_Status() ) == true ){
        this->m_render_state->Process_Command_Result( result );
    }


    // Otherwise, handle command
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::VALID ){

        
        // Add the command to the queue
        m_command_queue->Push_Command( result_ptr );
    
        // Wait for a completed response if response required
        if( result.Get_Command().Response_Expected() == true ){
            
            // Publish the notice
            m_render_manager->Set_Waiting_Command_Response( result_ptr );
        }
    }

    // Otherwise, error
    else{
        std::cout << "invalid command" << std::endl;
    }

    
    // Clear the cursor    
    this->m_render_state->Clear_Cursor_Text();

}


/***************************************/
/*          Start the Handler          */
/***************************************/
void A_Connection_Manager_Base::Start_Handler()
{

    // Get the current context
    if( m_render_state == nullptr ){
        return;
    }
    
    // Signal that we are running
    m_is_running = true;

    // Start the thread
    m_connection_thread = std::thread( &A_Connection_Manager_Base::Run_Handler,
                                       this);
}


/****************************************/
/*          Wait for shutdown           */
/****************************************/
void A_Connection_Manager_Base::Wait_Shutdown()
{
    // Only join if we are running
    if( m_is_running == true ){
        m_connection_thread.join();
    }
}


/*************************************/
/*          Stop the Handler         */
/*************************************/
void A_Connection_Manager_Base::Signal_Shutdown()
{
    // set the flag
    m_is_running = false;
    
    // Finalize
    m_render_manager->Finalize();
}



} // End of CLI Namespace

