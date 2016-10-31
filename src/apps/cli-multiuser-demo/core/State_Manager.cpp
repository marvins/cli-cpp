/**
 * @file    State_Manager.cpp
 * @author  Marvin Smith
 * @date    10/26/2016
*/
#include "State_Manager.hpp"

// C++ Libraries
#include <iostream>

/*******************************/
/*        Constructor          */
/*******************************/
State_Manager::State_Manager( )
  : m_shutdown_system(false)
{
    // Add some assets

}


/*****************************/
/*        Destructor         */
/*****************************/
State_Manager::~State_Manager()
{

}

/********************************************/
/*          Signal System Shutdown          */
/********************************************/
void State_Manager::Signal_System_Shutdown()
{

    // Notify the condition variable
    m_shutdown_cv.notify_all();

    // Set flag
    m_shutdown_system = true;

}


/************************************************/
/*          Wait Until System Shutdown          */
/************************************************/
void State_Manager::Wait_On_System_Shutdown()
{

    // If shutdown already set, skip
    if( m_shutdown_system == true ){
        return;
    }

    // wait to exit
    std::unique_lock<std::mutex> ulock( m_shutdown_mutex );
    while( m_shutdown_system == false ){
        m_shutdown_cv.wait( ulock );
    }

}


/******************************************/
/*      Notify of a CLI Session Event     */
/******************************************/
void State_Manager::Notify_Session_Event( const CLI::CORE::Session_Event& session_event )
{
    m_session_events.push_back(session_event);

}

