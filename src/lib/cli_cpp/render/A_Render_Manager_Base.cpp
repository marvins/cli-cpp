/**
 * @file    A_Render_Manager_Base.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Render_Manager_Base.hpp"

// C++ Standard Libraries
#include <iostream>
#include <sstream>

// CLI Libraries
#include "../core/Event_Manager.hpp"
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"
#include "../utility/String_Utilities.hpp"

namespace CLI{
namespace RENDER{

/****************************/
/*      Constructor         */
/****************************/
A_Render_Manager_Base::A_Render_Manager_Base( CMD::A_Command_Parser::ptr_t command_parser )
 :  m_command_history(std::make_shared<CMD::A_Command_History>()),
    m_command_queue(nullptr),
    m_command_counter(0),
    m_render_state(nullptr),
    m_command_parser(command_parser),
    m_class_name("A_Render_Manager_Base")
{
}


/**************************************/
/*       Set the CLI Window Size      */
/**************************************/
void A_Render_Manager_Base::Set_CLI_Window_Size( const int& rows,
                                                 const int& cols )
{

    // Update Driver
    m_render_driver_context->Set_CLI_Window_Size( rows, cols );


}


/****************************************/
/*      Process the Current Command     */
/****************************************/
void A_Render_Manager_Base::Process_Command()
{

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    

    // Make sure the command is not blank
    if( UTILS::String_Trim( m_render_state->Get_Cursor_Text() ).size() <= 0 )
    {
        
        // Clear the string
        BOOST_LOG_TRIVIAL(debug) << "Empty command. Skipping action.";

        m_render_state->Clear_Cursor_Text();
        return;
    }

    // Cancel the command if we are still waiting on another command to finish
    if(  Check_Waiting_Command_Response() )
    {
        BOOST_LOG_TRIVIAL(debug) << "Waiting on response for existing command. Skipping action.";
        m_render_state->Clear_Cursor_Text();
        return;
    }

    
    // Check the command
    CMD::A_Command_Result result = m_command_parser->Evaluate_Command( m_render_state->Get_Cursor_Text() );

    
    // Create shared pointer
    CMD::A_Command_Result::ptr_t result_ptr = std::make_shared<CMD::A_Command_Result>( result );
    
    
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ << ", Command Result: " << result.To_Debug_String();

    
    // Add to history
    Add_Command_History( m_render_state->Get_Cursor_Text(), 
                         result_ptr );

    
    //  Look for CLI Shutdown
    if( result.Get_Parse_Status() == CMD::CommandParseStatus::CLI_SHUTDOWN ){
        CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_SHUTDOWN );
    }
    

    // Look for other CLI Command
    else if( CMD::Is_Valid_CLI_Command( result.Get_Parse_Status() ) == true ){
        m_render_state->Process_Command_Result( result );
    }


    // Otherwise, handle command
    else if( result.Get_Parse_Status() == CMD::CommandParseStatus::VALID ){

        // Add the command to the queue
        m_command_queue->Push_Command( result_ptr );
    
        // Wait for a completed response if response required
        if( result.Get_Command().Response_Expected() == true )
        {
            
            // Publish the notice
            Set_Waiting_Command_Response( result_ptr );
        
            // Refresh
            CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_REFRESH );

        }
    }

    // Otherwise, error
    else{
    }

    
    // Clear the cursor    
    m_render_state->Clear_Cursor_Text();
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}

/************************************/
/*      Process Keyboard Input      */
/************************************/
void A_Render_Manager_Base::Process_Keyboard_Input( const int& key )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(debug) << "Start of " << __func__ << " method. Key: " << key << ", File: " << __FILE__ << ", Line: " << __LINE__;
    

    // Check if we are sleeping. If we are just return
    if( m_render_state->Get_Sleep_Mode() == true ){
        return;
    }


    // Check if we are waiting on a command response. If we are, return
    if( Check_Waiting_Command_Response() == true ){
        return;
    }
    

    // Check if the user presses enter while paused
    if( key == (int)CORE::CLI_Event_Type::KEYBOARD_ENTER &&
        m_render_state->Get_Pause_Mode() )
    {
        
        // Reset the pause mode
        m_render_state->Reset_Pause_Mode();
        
        // Refresh the screen
        CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_REFRESH );
        
        return;
    }


    // Check the key value if enter
    if( key == (int)CORE::CLI_Event_Type::KEYBOARD_ENTER )
    {
        
        // Process the command
        Process_Command();


        // Check if we have an active queue (CLI_RUN_SCRIPT)
        while( m_render_state->Get_Active_Command_Queue_Size() > 0 ){
            
            
            // Update the current command
            m_render_state->Load_Next_Active_Command();
            
            
            // Refresh
            CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_REFRESH );
            
            
            // Wait while either waiting or sleeping
            while(  Check_Waiting_Command_Response() ||
                    m_render_state->Get_Pause_Mode() == true ||
                    m_render_state->Get_Sleep_Mode() == true )
            {
                BOOST_LOG_TRIVIAL(trace) << "Waiting on Check_Waiting_Command_Response()";
                usleep(1000);
        
                // Refresh the screen
                CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_REFRESH );
            }

            
            // Process the command
            Process_Command();
                
        }
    
        // Refresh the screen
        CORE::Event_Manager::Process_Event( (int)CORE::CLI_Event_Type::CLI_REFRESH );

        return;
    }

    
    // Check that the render state is not null.  I want this to seg fault for now so I know when a problem occurs
    if( this->m_render_state == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-State is currently nullptr. Expect a seg fault.";
    }

    
    // Process Keyboard Input
    this->m_render_state->Process_Input( key );


    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


} // End of RENDER Namespace
} // End of CLI    Namespace

