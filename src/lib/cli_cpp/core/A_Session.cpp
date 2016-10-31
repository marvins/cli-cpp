/**
 * @file    A_Session.cpp
 * @author  Marvin Smith
 * @date    10/30/2016
 */
#include "A_Session.hpp"

namespace CLI{
namespace CORE{


/**********************************/
/*          Constructor           */
/**********************************/
Session::Session( const int&             session_id,
                  const ConnectionType&  connection_type )
  : m_class_name("Session"),
    m_session_id(session_id),
    m_connection_type(connection_type)
{
}


/**********************************/
/*          Constructor           */
/**********************************/
Session::Session( const int&                                session_id,
                  const ConnectionType&                     connection_type,
                  const std::map<std::string,std::string>&  connection_data )
  : m_class_name("Session"),
    m_session_id(session_id),
    m_connection_type(connection_type),
    m_connection_data(connection_data)
{
}


/*************************/
/*      Constructor      */
/*************************/
Session_Event::Session_Event( const Session&           session,
                              const SessionEventType&  event_type,
                              const std::string&       message )
  : m_class_name("Session_Event"),
    m_session(session),
    m_event_type(event_type),
    m_message(message)
{

}


} // End of CORE Namespace
} // End of CLI  Namespace
