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

} // End of UTILS Namespace
} // End of CLI   Namespace

#endif
