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
A_Connection_Manager_Base::A_Connection_Manager_Base( RENDER::A_Render_Manager_Base::ptr_t render_manager )
  : m_is_running(false),
    m_render_manager(render_manager),
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


/***************************************/
/*          Start the Handler          */
/***************************************/
void A_Connection_Manager_Base::Start_Handler()
{
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
    if( m_is_running == true || 
        m_connection_thread.joinable() == true )
    {
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

