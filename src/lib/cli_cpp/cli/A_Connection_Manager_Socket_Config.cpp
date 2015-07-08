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
A_Connection_Manager_Socket_Config::A_Connection_Manager_Socket_Config( const int&     port,
                                                                        const int64_t& read_timeout_sleep_usec,
                                                                        const int&     max_connections)
  : A_Connection_Manager_Base_Config(),
    m_class_name("A_Connection_Manager_Socket_Config"),
    m_port(port),
    m_read_timeout_sleep_usec(read_timeout_sleep_usec),
    m_max_connections(max_connections)
{


}



/**************************/
/*      Destructor        */
/**************************/
A_Connection_Manager_Socket_Config::~A_Connection_Manager_Socket_Config()
{


}


} // End of CLI Namespace

