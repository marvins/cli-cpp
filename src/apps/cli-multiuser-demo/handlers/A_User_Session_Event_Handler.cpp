/**
 * @file    A_User_Session_Event_Handler.cpp
 * @author  Marvin Smith
 * @date    10/30/2016
 */
#include "A_User_Session_Event_Handler.hpp"


/********************************/
/*         Constructor          */
/********************************/
A_User_Session_Event_Handler::A_User_Session_Event_Handler( State_Manager& state_manager )
  : m_class_name("A_User_Session_Event_Handler"),
    m_state_manager(state_manager)
{


}

/*************************************/
/*      Process The Session Event    */
/*************************************/
void A_User_Session_Event_Handler::Process_Event( const CLI::CORE::Session_Event& session_event )
{
    
    // Push to State-Manager
    m_state_manager.Notify_Session_Event( session_event );
}


