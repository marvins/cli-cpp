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


/****************************************/
/*      Process the Current Command     */
/****************************************/
void A_Render_Manager_Base::Process_Command()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Make sure the command is not blank
    if( UTILS::String_Trim( m_render_state->Get_Cursor_Text() ).size() <= 0 ){
        
        // Clear the string
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
        if( result.Get_Command().Response_Expected() == true ){
            
            // Publish the notice
            Set_Waiting_Command_Response( result_ptr );
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
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Check the key value if enter
    if( key == (int)CORE::CLI_Event_Type::KEYBOARD_ENTER ){
        Process_Command();
        return;
    }
    
    // Check that the render state is not null
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

