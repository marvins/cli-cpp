/**
 * @file    System_Utilities.hpp
 * @author  Marvin Smith
 * @date    5/21/2015
*/
#ifndef __CLI_CPP_UTILS_SYSTEM_UTILITIES_HPP__
#define __CLI_CPP_UTILS_SYSTEM_UTILITIES_HPP__

namespace CLI{
namespace UTILS{

/**
 * @brief Stack Trace Signal Handler
 *
 * @param[in] signal_code Signal code that signal.h returns.
*/
void Stack_Trace_Handler( int signal_code );


/**
 * @brief execute the command on the system and return the command output.
 *
 * @param[in] command command to run.
 * @param[out] stdout_data standard output data.
 * @param[out] stderr_data standard error data.
 *
 * @return True if command executed, false if error.
*/
bool Execute_Shell_Command( const std::string& command,
                            const std::string& stdout_data,
                            const std::string& stderr_data );


} // End of UTILS Namespace
} // End of CLI   Namespace

#endif
