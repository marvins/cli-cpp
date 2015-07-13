/**
 * @file    A_Command_Queue_Config.cpp
 * @author  Marvin Smith
 * @date    7/11/2015
*/
#include "A_Command_Queue_Config.hpp"


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


} // End of CMD Namespace
} // End of CLI Namespace
