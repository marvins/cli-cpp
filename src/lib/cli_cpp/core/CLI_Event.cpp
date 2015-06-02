/**
 * @file    CLI_Event.cpp
 * @author  Marvin Smith
 * @date    6/1/2015
*/
#include "CLI_Event.hpp"

namespace CLI{
namespace CORE{

/*************************************/
/*           Constructor             */
/*************************************/
CLI_Event::CLI_Event( CLI_Event_Type const& event_type )
  : m_event_type(event_type)
{
}


} // End of CORE Namespace
} // End of CLI  Namespace

