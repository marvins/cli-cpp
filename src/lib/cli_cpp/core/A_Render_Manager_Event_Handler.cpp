/**
 * @file    A_Render_Manager_Event_Handler.cpp
 * @author  Marvin Smith
 * @date    5/31/2015
*/
#include "A_Render_Manager_Event_Handler.hpp"

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
    // Send to the cli manager
    m_render_manager->Process_Keyboard_Input( event );

}


} // End of CORE Namespace
} // End of CLI  Namespace

