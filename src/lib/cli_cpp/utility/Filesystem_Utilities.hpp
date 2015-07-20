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


/**
 * @brief Check if File Exists.
 *
 * @param[in] pathname Path to evaluate.
 *
 * @return True if exists, false otherwise.
 *
 * The main use of this method is to abstract out my use of boost
 * filesystem so that users won't have to include the header file 
 * in their own applications.
*/
bool Path_Exists( const std::string& pathname );


} // End of FS  Namespace
} // End of CLI Namespace

#endif
