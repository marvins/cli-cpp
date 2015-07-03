/**
 * @file    Event_Manager_Config.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include "Event_Manager_Config.hpp"

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
}



} // End of EVT Namespace
} // End of CLI Namespace

