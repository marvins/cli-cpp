/**
 * @file    A_Connection_Manager_Event_Handler.cpp
 * @author  Marvin Smith
 * @date    6/1/2015
*/
#include "A_Connection_Manager_Event_Handler.hpp"

namespace CLI{
namespace CORE{


/****************************/
/*       Constructor        */
/****************************/
A_Connection_Manager_Event_Handler::A_Connection_Manager_Event_Handler( A_Connection_Manager_Base::ptr_t connection_manager )
 : A_CLI_Event_Handler_Base(),
   m_class_name("A_Connection_Manager_Event_Handler"),
   m_connection_manager(connection_manager)
{
}


/****************************/
/*       Constructor        */
/****************************/
void A_Connection_Manager_Event_Handler::Process_Event( int const& event )
{
    // Check if we have a shutdown event
    if( event == (int)CLI_Event_Type::CLI_SHUTDOWN ){
        m_connection_manager->Set_Is_Connected_Flag( false );
    }
}


} // End of CORE Namespace
} // End of CLI  Namespace

