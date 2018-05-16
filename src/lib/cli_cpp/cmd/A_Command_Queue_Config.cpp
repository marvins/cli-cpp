/**
 * @file    A_Command_Queue_Config.cpp
 * @author  Marvin Smith
 * @date    7/11/2015
*/
#include "A_Command_Queue_Config.hpp"

// C++ Libraries
#include <iostream>
#include <sstream>


namespace CLI{
namespace CMD{

/*********************************/
/*          Constructor          */
/*********************************/
A_Command_Queue_Config::A_Command_Queue_Config( const int& max_queue_size )
  : m_class_name("A_Command_Queue_Config"),
    m_max_queue_size(max_queue_size)
{
}


/****************************************/
/*          Print to Log String         */
/****************************************/
std::string A_Command_Queue_Config::To_Log_String( int offset )const
{
    std::string gap(offset, ' ');

    std::stringstream sin;

    sin << gap << " - " << m_class_name << std::endl;
    sin << gap << "     - Max Queue Size   : " << m_max_queue_size << std::endl;

    return sin.str();
}

} // End of CMD Namespace
} // End of CLI Namespace
