/**
 * @file    ConnectionType.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "ConnectionType.hpp"


namespace CLI{
namespace CORE{


/*******************************************/
/*      Convert a string to CLI type       */
/*******************************************/
ConnectionType  StringToConnectionType( const std::string& cli_type )
{
    // Base 
    if( cli_type == "BASE" ){
        return ConnectionType::BASE;
    }

    // Socket
    if( cli_type == "SOCKET" ){
        return ConnectionType::SOCKET;
    }
    
    // Socket
    if( cli_type == "CLI_SOCKET" ){
        return ConnectionType::CLI_SOCKET;
    }

    return ConnectionType::UNKNOWN;
}



/*************************************************/
/*      Convert a connection type to string      */
/*************************************************/
std::string ConnectionTypeToString( const ConnectionType& cli_type )
{
    if( cli_type == ConnectionType::BASE  ){ return "BASE"; }
    if( cli_type == ConnectionType::SOCKET ){ return "SOCKET"; }
    if( cli_type == ConnectionType::CLI_SOCKET ){ return "CLI_SOCKET"; }
    return "UNKNOWN";
}

} // End of CORE Namespace
} // End of CLI  Namespace

