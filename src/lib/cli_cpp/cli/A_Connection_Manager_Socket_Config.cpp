/** 
 * @file    A_Connection_Manager_Socket_Config.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#include "A_Connection_Manager_Socket_Config.hpp"


namespace CLI{

/**************************/
/*      Constructor       */
/**************************/
A_Connection_Manager_Socket_Config::A_Connection_Manager_Socket_Config( const int& port,
                                                                        const int& socket_read_sleep_time_usec,
                                                                        const int& socket_read_max_wait_refresh_count)
  : A_Connection_Manager_Base_Config(),
    m_class_name("A_Connection_Manager_Socket_Config"),
    m_port(port),
    m_socket_read_sleep_time_usec(socket_read_sleep_time_usec),
    m_socket_read_max_wait_refresh_count(socket_read_max_wait_refresh_count)
{


}



/**************************/
/*      Destructor        */
/**************************/
A_Connection_Manager_Socket_Config::~A_Connection_Manager_Socket_Config()
{


}


} // End of CLI Namespace

