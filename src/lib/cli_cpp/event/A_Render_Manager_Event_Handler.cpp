/**
 * @file    A_Render_Manager_Event_Handler.cpp
 * @author  Marvin Smith
 * @date    5/31/2015
*/
#include "A_Render_Manager_Event_Handler.hpp"

// CLI Libraries
#include "../core/CLI_Event_Type.hpp"
#include "../event/Event_Manager.hpp"
#include "../utility/Log_Utilities.hpp"


// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace EVT{


/****************************/
/*       Constructor        */
/****************************/
A_Render_Manager_Event_Handler::A_Render_Manager_Event_Handler( RENDER::A_Render_Manager_Base::ptr_t render_manager )
 : A_CLI_Event_Handler_Base(),
   m_class_name("A_Render_Manager_Event_Handler"),
   m_render_manager(render_manager)
{
}


/****************************************/
/*       Check if Supported Event       */
/****************************************/
bool A_Render_Manager_Event_Handler::Is_Supported_Event( const int& event )const{
    
    // Skip Refresh
    switch( event ){
        case (int)CLI_Event_Type::CLI_REFRESH:
        case (int)CLI_Event_Type::CLI_HELP:
            return false;
    }
    
    // Otherwise, we are fine
    return true;
}


/****************************/
/*       Constructor        */
/****************************/
void A_Render_Manager_Event_Handler::Process_Event( int const& event )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Event: " << event << ", File: " << __FILE__ << ", Line: " << __LINE__;
    
    
    // Skip if a CLI Shutdown Command
    if( event == (int)CLI_Event_Type::UNKNOWN ||
        event == (int)CLI_Event_Type::CLI_SHUTDOWN )
    {
        return;
    }

    // If we have a command to show the CLI Help, then show that
    else if( event == (int)CLI_Event_Type::KEYBOARD_F2 )
    {
        m_render_manager->Set_Current_Window(1);
    }


    // If we have a command for CLI_BACK, then set the current window to the main
    else if( event == (int)CLI_Event_Type::CLI_BACK ||
             event == (int)CLI_Event_Type::KEYBOARD_F1 )
    {
        m_render_manager->Set_Current_Window(0);
    }

    // If we have a command for CLI_LOG, then set the current window to the log
    else if( event == (int)CLI_Event_Type::CLI_LOG ||
             event == (int)CLI_Event_Type::KEYBOARD_F3 )
    {
        m_render_manager->Set_Current_Window(2);
    }

    // If we have a command for CLI_ALIAS_LIST, then set the current window to the alias list
    else if( event == (int)CLI_Event_Type::CLI_ALIAS_LIST ||
             event == (int)CLI_Event_Type::KEYBOARD_F4 )
    {
        m_render_manager->Set_Current_Window(3);
    }

    // Otherwise, Process the Keyboard Input
    else{
        m_render_manager->Process_Keyboard_Input( event );
    }

    // Refresh screen
    EVT::Event_Manager::Process_Event( (int)CLI_Event_Type::CLI_REFRESH );

}


} // End of EVT Namespace
} // End of CLI Namespace

