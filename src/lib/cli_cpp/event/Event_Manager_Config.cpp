/**
 * @file    Event_Manager_Config.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include "Event_Manager_Config.hpp"

/// CLI Libraries
#include "../core/CLI_Event_Type.hpp"

// C++ Libraries
#include <iostream>
#include <sstream>

namespace CLI{
namespace EVT{


/**********************************/
/*          Constructor           */
/**********************************/
Event_Manager_Config::Event_Manager_Config( const int& event_queue_max_capacity,
                                            const int& event_work_queue_threads )
 : m_class_name("Event_Manager_Config"),
   m_event_queue_max_capacity(event_queue_max_capacity),
   m_event_work_queue_threads(event_work_queue_threads)
{
    // Load the Event Filter List
    m_event_filter_list.insert((int)CLI_Event_Type::CLI_REFRESH);
    m_event_filter_list.insert((int)CLI_Event_Type::CLI_SHUTDOWN);

}


/****************************************/
/*          Print to Log String         */
/****************************************/
std::string Event_Manager_Config::To_Log_String( int offset )const
{
    std::string gap(offset, ' ');

    std::stringstream sin;

    sin << gap << " - " << m_class_name << std::endl;
    sin << gap << "     - Max Queue Size   : " << m_event_queue_max_capacity << std::endl;
    sin << gap << "     - Num Queue Threads: " << m_event_work_queue_threads << std::endl;
    sin << gap << "     - Event-Filter-list (Size: " << m_event_filter_list.size() << ")\n";
    for( auto id : m_event_filter_list )
    {
        sin << gap << "         - Listener: " << CLI_Event_Type_To_String(id) << std::endl;
    }

    return sin.str();
}


} // End of EVT Namespace
} // End of CLI Namespace

