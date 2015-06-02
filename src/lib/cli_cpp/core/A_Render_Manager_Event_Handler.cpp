/**
 * @file    A_Render_Manager_Event_Handler.cpp
 * @author  Marvin Smith
 * @date    5/31/2015
*/
#include "A_Render_Manager_Event_Handler.hpp"

// CLI Libraries
#include "CLI_Event_Type.hpp"

// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace CORE{


/****************************/
/*       Constructor        */
/****************************/
A_Render_Manager_Event_Handler::A_Render_Manager_Event_Handler( RENDER::A_Render_Manager_Base::ptr_t render_manager )
 : A_CLI_Event_Handler_Base(),
   m_class_name("A_Render_Manager_Event_Handler"),
   m_render_manager(render_manager)
{
}


/****************************/
/*       Constructor        */
/****************************/
void A_Render_Manager_Event_Handler::Process_Event( int const& event )
{
    // Skip if a CLI Shutdown Command
    if( event == (int)CORE::CLI_Event_Type::UNKNOWN ||
        event == (int)CORE::CLI_Event_Type::CLI_SHUTDOWN )
    {
        return;
    }

    // If we have a command to show the CLI Help, then show that
    else if( event == (int)CORE::CLI_Event_Type::CLI_HELP ){
        m_render_manager->Set_Current_Window( 1 );
    }

    // If we have a command for CLI_BACK, then set the current window to the main
    else if( event == (int)CORE::CLI_Event_Type::CLI_BACK ){
        m_render_manager->Set_Current_Window(0);
    }

    // Otherwise, Process the Keyboard Input
    else{
        m_render_manager->Process_Keyboard_Input( event );
    }

}


} // End of CORE Namespace
} // End of CLI  Namespace

