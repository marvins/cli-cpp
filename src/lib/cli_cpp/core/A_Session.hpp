/**
 * @file    A_Session.hpp
 * @author  Marvin Smith
 * @date    10/30/2016
 */
#ifndef __CLI_CPP_CORE_A_SESSION_HPP__
#define __CLI_CPP_CORE_A_SESSION_HPP__

// C++ Libraries
#include <cinttypes>
#include <map>
#include <string>


// CLI Libraries
#include "ConnectionType.hpp"

namespace CLI{
namespace CORE{


/**
 * @enum SessionEventType
 */
enum class SessionEventType : int8_t
{
    UNKNOWN    = 0 /**< This should be an error condition.*/,
    CONNECT    = 1 /**< User Connected to CLI.*/,
    DISCONNECT = 2 /**< User Disconnected from CLI.*/,
}; // End of SessionEventType Enumeration


/**
 * @class Session
 */
class Session
{
    public:
        
        /**
         * @brief Constructor
         */
        Session( const int&                   session_id,
                 const CORE::ConnectionType&  connection_type );
        
        
        /**
         * @brief Constructor
         *
         * @param[in] session_id
         * @param[in] connection_type
         * @param[in] connection_data
         */
        Session( const int&                               session_id,
                 const CORE::ConnectionType&              connection_type,
                 const std::map<std::string,std::string>& connection_data );


        /**
         * @brief Get Session ID.
         */
        inline uint64_t Get_Session_ID()const{
            return m_session_id;
        }


        /**
         * @brief Get the Session-Type.
         *
         * @return Connection Type state
         */
        inline CORE::ConnectionType Get_Connection_Type()const{
            return m_connection_type;
        }


        /**
         * @brief Get the Connection Data
         */
        inline std::map<std::string,std::string> Get_Connection_Data()const{
            return m_connection_data;
        }


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Session-ID
        uint64_t m_session_id;

        /// Connection Type
        CORE::ConnectionType m_connection_type;

        /// Connection Info
        std::map<std::string,std::string> m_connection_data;

}; // End of Session class


/**
 * @class Session_Event
 */
class Session_Event
{
    public:
        
        /**
         * @brief Constructor
         */
        Session_Event( const Session&           session,
                       const SessionEventType&  event_type,
                       const std::string&       message);

        
        /**
         * @brief Get the Session
         */
        inline Session Get_Session()const{
            return m_session;
        }


        /**
         * @brief Get the Event Type
         */
        inline SessionEventType Get_Event_Type()const{
            return m_event_type;
        }


        /**
         * @brief Get Message
         */
        inline std::string Get_Message()const{
            return m_message;
        }

    private:
        
        /// Class Name
        std::string m_class_name;

        /// Session
        Session m_session;

        /// Event Type
        SessionEventType m_event_type;

        /// Message
        std::string m_message;

}; // End of Session_Event Class


} // End of CORE Namespace
} // End of CLI  Namespace


#endif
