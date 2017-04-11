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
  : m_shutdown_system(false),
    m_timer_running(false),
    m_timer_wait(std::chrono::milliseconds(5000))
{
    // Add some assets

}


/*****************************/
/*        Destructor         */
/*****************************/
State_Manager::~State_Manager()
{

}


/**************************************************/
/*          Initialize the State Manager          */
/**************************************************/
void State_Manager::Initialize()
{
    // Start Timer Thread
    m_timer_thread = std::thread( &State_Manager::Run_Timer, this);
}

/************************************************/
/*          Finalize the State Manager          */
/************************************************/
void State_Manager::Finalize()
{
    // Stop Timer Thread
    if( m_timer_running && m_timer_thread.joinable() )
    {
        m_timer_running = false;
        m_timer_thread.join();
    }
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


/************************************/
/*          Run The TImer           */
/************************************/
void State_Manager::Run_Timer()
{
    // Start Loop
    m_timer_running = true;

    while( m_timer_running )
    {
        std::cout << "Triggering Timer" << std::endl;
        std::this_thread::sleep_for(m_timer_wait);

        if( m_cli_manager != nullptr )
        {
            m_cli_manager->Send_Asynchronous_Message( "CLI_TIMER", "Timer Triggered");
        }
        else
        {
            std::cerr << "ERROR: CLI-Manager instance is null." << std::endl;
        }
    }

    // Log Exit
    std::cout << "Exiting Run_Timer Method." << std::endl;
}
