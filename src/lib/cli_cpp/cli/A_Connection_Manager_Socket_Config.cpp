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
A_Connection_Manager_Socket_Config::A_Connection_Manager_Socket_Config( int                                   port,
                                                                        int                                   max_connections,
                                                                        A_Socket_Instance_Config_Base::ptr_t instance_config )
  : A_Connection_Manager_Base_Config(),
    m_class_name("A_Connection_Manager_Socket_Config"),
    m_port(port),
    m_max_connections(max_connections),
    m_instance_config(instance_config)
{
}


/****************************************/
/*          Print to Log String         */
/****************************************/
std::string A_Connection_Manager_Socket_Config::To_Log_String(int offset) const
{
    std::string gap(offset, ' ');
    
    std::stringstream sin;
    
    sin << gap << " - " << m_class_name << std::endl;
    sin << gap << "    - port : " << m_port << std::endl;
    sin << gap << "    - max-connections: " << m_max_connections << std::endl;
    sin << m_instance_config->To_Log_String(offset+4);
    
    return sin.str();
}

} // End of CLI Namespace

