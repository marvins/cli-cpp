/**
 * @file    A_Socket_Base_Instance.cpp
 * @author  Marvin Smith
 * @date    5/14/2018
*/
#include "A_Socket_Telnet_Instance.hpp"

// CLI Libraries
#include "../event/Event_Manager.hpp"
#include "../utility/Log_Utilities.hpp"


namespace CLI{


/*********************************/
/*          Constructor          */
/*********************************/
A_Socket_Instance_Config_Base::A_Socket_Instance_Config_Base( std::chrono::microseconds  read_sleep_timeout )
 : m_class_name("A_Socket_Instance_Config_Base"),
   m_read_sleep_timeout(read_sleep_timeout)
{
}


/************************************/
/*           Constructor            */
/************************************/
A_Socket_Base_Instance::A_Socket_Base_Instance( A_Socket_Instance_Config_Base::ptr_t  config,
                                                int                                   instance_id,
                                                const CORE::Session&                  session,
                                                int                                   client_fd )
    : m_instance_id(instance_id),
      m_session(session),
      m_client_fd(client_fd),
      m_is_running(false),
      m_class_name("A_Socket_Base_Instance"),
      m_config(config)
{
}


/*******************************/
/*            Start            */
/*******************************/
void A_Socket_Base_Instance::Start()
{
    m_thread = std::thread( &A_Socket_Base_Instance::Run, this );
}

/*********************************/
/*          Join Thread          */
/*********************************/
void A_Socket_Base_Instance::Join()
{
    // Set flag
    m_is_running = false;
    
    // Wait to finish
    if( m_thread.joinable() ){
        m_thread.join();
    }
}


} // End of CLI Namespace

