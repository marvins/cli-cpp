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
A_Connection_Manager_Base::A_Connection_Manager_Base( A_Connection_Manager_Base_Config::ptr_t configuration )
  : m_is_running(false),
    m_class_name("A_Connection_Manager_Base"),
    m_configuration(configuration)
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
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Signal that we are running
    m_is_running = true;

    // Start the thread
    m_connection_thread = std::thread( &A_Connection_Manager_Base::Run_Handler,
                                       this);
    
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/****************************************/
/*          Wait for shutdown           */
/****************************************/
void A_Connection_Manager_Base::Wait_Shutdown()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Only join if we are running
    if( m_is_running == true || 
        m_connection_thread.joinable() == true )
    {
        m_is_running = false;
        m_connection_thread.join();
    }
    
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/*************************************/
/*          Stop the Handler         */
/*************************************/
void A_Connection_Manager_Base::Signal_Shutdown()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // set the flag
    m_is_running = false;
    
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}



} // End of CLI Namespace

