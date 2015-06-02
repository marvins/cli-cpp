/**
 * @file    ConnectionType.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_CPP_CORE_CONNECTIONTYPE_HPP__
#define __CLI_CPP_CORE_CONNECTIONTYPE_HPP__

// C++ Standard Libraries
#include <string>

namespace CLI{
namespace CORE{

/**
 * @enum ConnectionType
 */
enum class ConnectionType : uint8_t {
    UNKNOWN = 0,
    BASE    = 1,
    SOCKET  = 2,
}; // End of ConnectionType Enum


/**
 * @brief Convert String to CLI Connection Type.
 *
 * @param[in] cli_type CLI Type string.
 *
 * @return Connection Type
 */
ConnectionType StringToConnectionType( std::string const& cli_type );


/**
 * @brief Convert ConnectionType to a string.
 *
 * @param[in] cli_type CLI Connection Type.
 *
 * @return String format.
 */
std::string ConnectionTypeToString( const ConnectionType& cli_type );


} // End of CORE Namespace
} // End of CLI  Namespace

#endif
