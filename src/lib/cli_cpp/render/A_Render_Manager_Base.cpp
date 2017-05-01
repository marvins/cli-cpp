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
#include "A_Render_Manager_Factory.hpp"
#include "../event/Event_Manager.hpp"
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"
#include "../utility/Stopwatch.hpp"
#include "../utility/String_Utilities.hpp"


namespace CLI{
namespace RENDER{

/****************************/
/*      Constructor         */
/****************************/
A_Render_Manager_Base::A_Render_Manager_Base( const int&                   instance_id,
                                              CMD::A_Command_Parser::ptr_t command_parser,
                                              CMD::A_Command_Queue::ptr_t  command_queue )
 :  m_command_queue(command_queue),
    m_command_parser(command_parser),
    m_render_state(nullptr),
    m_instance_id(instance_id),
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
        // Clear the cursor text
        BOOST_LOG_TRIVIAL(debug) << "Waiting on response for existing command. Skipping action.";
        m_render_state->Clear_Cursor_Text();
    
        return;
    }

    
    // Check the command
    CMD::A_Command_Result::ptr_t result = m_command_parser->Evaluate_Command( m_instance_id,
                                                                              m_render_state->Get_Cursor_Text() );

    
    // Log 
    CLI_LOG_CLASS(trace, "Command Result: " + result->To_Debug_String());

    
    // Add to history
    m_render_state->Add_Command_History( m_render_state->Get_Cursor_Text(), 
                                         result );

    
    //  Look for CLI Shutdown
    if( result->Get_Parse_Status() == CMD::CommandParseStatus::CLI_SHUTDOWN )
    {
        EVT::Event_Manager::Process_Event( m_instance_id,
                                           (int)CLI_Event_Type::CLI_SHUTDOWN );
    }
    

    // Look for other CLI Command
    else if( CMD::Is_Valid_CLI_Command( result->Get_Parse_Status() ) == true )
    {
        m_render_state->Process_Command_Result( result );
    }


    // Otherwise, handle command
    else if( result->Get_Parse_Status() == CMD::CommandParseStatus::VALID ){

        // Add the command to the queue
        m_command_queue->Push_Command( result );
    
        // Wait for a completed response if response required
        if( result->Get_Command().Response_Expected() == true )
        {
            
            // Publish the notice
            Set_Waiting_Command_Response( result );
        
            // Refresh
            EVT::Event_Manager::Process_Event( m_instance_id,
                                               (int)CLI_Event_Type::CLI_REFRESH );

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
    CLI_LOG_CLASS( trace,
                   "Start of Method.  Key: " + std::to_string(key));
    Stopwatch<double> process_stopwatch;
    process_stopwatch.Start();

    // Make sure the instance is not null
    if( m_render_state == nullptr )
    {
        BOOST_LOG_TRIVIAL(error) << "Render-State for instance " << m_instance_id << " is null.";
        return;
    }


    // Check if we are sleeping. If we are just return
    if( m_render_state->Get_Sleep_Mode() == true ){
        return;
    }


    // Check if we are waiting on a command response. If we are, return
    if( Check_Waiting_Command_Response() == true ){
        return;
    }


    // Check if the user presses enter while paused
    if( key == (int)CLI_Event_Type::KEYBOARD_ENTER &&
        m_render_state->Get_Pause_Mode() )
    {
        
        // Reset the pause mode
        m_render_state->Reset_Pause_Mode();
        
        // Refresh the screen
        EVT::Event_Manager::Process_Event( m_instance_id,
                                           (int)CLI_Event_Type::CLI_REFRESH );
        
        return;
    }


    // Check the key value if enter
    if( key == (int)CLI_Event_Type::KEYBOARD_ENTER )
    {
        
        // Process the command
        Process_Command();

        // Refresh the screen
        EVT::Event_Manager::Process_Event( m_instance_id,
                                           (int)CLI_Event_Type::CLI_REFRESH );
        

        // Check if we have an active queue (CLI_RUN_SCRIPT)
        while( m_render_state->Get_Active_Command_Queue_Size() > 0 )
        {
                                        

            // Update the current command
            m_render_state->Load_Next_Active_Command();


            // Refresh
            EVT::Event_Manager::Process_Event( m_instance_id,
                                               (int)CLI_Event_Type::CLI_REFRESH );


            // Wait while either waiting or sleeping
            while(  Check_Waiting_Command_Response() ||
                    m_render_state->Get_Pause_Mode() == true ||
                    m_render_state->Get_Sleep_Mode() == true )
            {
                BOOST_LOG_TRIVIAL(trace) << "Waiting on Check_Waiting_Command_Response()";
                usleep(500000);

                // Refresh the screen
                EVT::Event_Manager::Process_Event( m_instance_id,
                                                   (int)CLI_Event_Type::CLI_REFRESH );
            }


            // Process the command
            Process_Command();

        }


        return;
    }


    // Process Keyboard Input
    m_render_state->Process_Input( key );


    // Log Exit
    process_stopwatch.Stop();
    CLI_LOG_CLASS(trace,
                  "End of Method. Time to process: " + std::to_string(process_stopwatch.Get_Duration().count()) + " seconds");
}


} // End of RENDER Namespace
} // End of CLI    Namespace

