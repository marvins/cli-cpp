/**
 * @file    Filesystem_Utilities.hpp
 * @author  Marvin Smith
 * @date    6/30/2015
*/
#ifndef __CLI_CPP_LIB_UTILITY_FILESYSTEM_UTILITIES_HPP__
#define __CLI_CPP_LIB_UTILITY_FILESYSTEM_UTILITIES_HPP__

// C++ Standard Libraries
#include <string>
#include <vector>


namespace CLI{
namespace FS{

/**
 * @brief Get the directory contents.
 *
 * @param[in] dir_path Directory pathname.
 * @param[in] basenames_only Return the results with only the basenames.  Don't append the dir_path.
 *
 * @return List of paths in the directory.
*/
std::vector<std::string> Get_Contents( const std::string& dir_path,
                                       bool const& basenames_only = true );


} // End of FS  Namespace
} // End of CLI Namespace

#endif
