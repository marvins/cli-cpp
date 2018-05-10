/**
 * @file    SessionType.hpp
 * @author  Marvin Smith
 * @date    5/10/2018
 */
#ifndef CLI_CORE_SESSION_TYPE_HPP
#define CLI_CORE_SESSION_TYPE_HPP

// C++ Libraries
#include <cinttypes>
#include <string>

namespace CLI {
namespace CORE {

/**
 * @enum SessionType
 */
enum class SessionType : int8_t
{
    UNKNOWN = 0,
    JSON = 1,
    TELNET = 2,
};

/**
 * @brief Conver tot String
 */
std::string SessionTypeToString(SessionType tp);


/**
 * @brief Convert From String
 */
SessionType StringToSessionType(std::string tp);


} // End of CORE Namespace
} // End of CLI  Namespace

#endif