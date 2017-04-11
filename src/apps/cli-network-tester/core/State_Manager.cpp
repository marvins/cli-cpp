/**
 * @file    State_Manager.cpp
 * @author  Marvin Smith
 * @date    6/2/2015
*/
#include "State_Manager.hpp"

// C++ Libraries
#include <iostream>

/*******************************/
/*        Constructor          */
/*******************************/
State_Manager::State_Manager( )
  : m_shutdown_system(false),
    m_network_scanner(std::make_shared<Network_Scanner>())
{
    // Add some assets
    m_network_scanner->Add_Network_Asset( "Google", "8.8.8.8", 10 );

    // Start the scanner
    m_network_scanner->Start_Scanner();

}


/*****************************/
/*        Destructor         */
/*****************************/
State_Manager::~State_Manager()
{

    // Stop the server
    m_network_scanner->Stop_Scanner();

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


