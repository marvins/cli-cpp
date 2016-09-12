/**
 * @file    Log_Utilities.hpp
 * @author  Marvin Smith
 * @date    5/21/2015
*/
#ifndef __CLI_CPP_UTILS_LOG_UTILITIES_HPP__
#define __CLI_CPP_UTILS_LOG_UTILITIES_HPP__


// Boost Libraries
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/trivial.hpp>

// C++ Standard Libraries
#include <string>


using namespace boost::log::trivial;


/**
 * @brief Boost-Log Macros
 */

/// General Purpose Log String Marker
#define CLI_CLASS_LOG_STR  (m_class_name + "::" + std::string(__func__) + ":" + std::to_string(__LINE__))

#define CLI_LOG_CLASS( severity, message ) BOOST_LOG_TRIVIAL(severity) << "SRC=" << CLI_CLASS_LOG_STR << ", MSG=" << message 

#define CLI_LOG_CLASS_ENTRY() CLI_LOG_CLASS( trace, "Start of Method.")
#define CLI_LOG_CLASS_EXIT()  CLI_LOG_CLASS( trace, "End of Method.")


namespace CLI{
namespace UTILS{

/**
 * @brief Initialize the Logger
 *
 * @param[in] severity Severity of messages to keep.
 * @param[in] log_path Path to logfile to write to.
 */
void Initialize_Logger( const std::string& severity,
                        const std::string& log_path );



} // End of UTILS Namespace
} // End of CLI   Namespace

#endif
