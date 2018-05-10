/**
 * @file    SessionType.cpp
 * @author  Marvin Smith
 * @date    5/10/2018
 */
#include "SessionType.hpp"


namespace CLI{
namespace CORE{

/**************************************************/
/*          Convert String to Session Type        */
/**************************************************/
std::string SessionTypeToString( SessionType tp )
{
    switch(tp)
    {
        case SessionType::JSON:
            return "JSON";
            
        case SessionType::TELNET:
            return "TELNET";
            
        case SessionType::UNKNOWN:
        default:
            return "UNKNOWN";
    }
    
    return "UNKNOWN";
}


/****************************************************/
/*          Convert Session-Type to String          */
/****************************************************/
SessionType  StringToSessionType( std::string tp )
{
    if( tp == "JSON" || tp == "json" ){
        return SessionType::JSON;
    }
    if( tp == "TELNET" || tp == "telnet" ){
        return SessionType::TELNET;
    }
    return SessionType::UNKNOWN;
}

} // End of CORE Namespace
} // End of CLI  Namespace
