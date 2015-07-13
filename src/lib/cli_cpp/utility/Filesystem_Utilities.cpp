/**
 * @file    Filesystem_Utilities.cpp
 * @author  Marvin Smith
 * @date    6/30/2015
*/
#include "Filesystem_Utilities.hpp"

// Boost Filesystem
#include <boost/filesystem.hpp>

namespace bf=boost::filesystem;

namespace CLI{
namespace FS{

/*************************************************/
/*          Get the directory contents           */
/*************************************************/
std::vector<std::string> Get_Contents( const std::string&  dir_path,
                                       const bool&         basenames_only )
{
    // Temp Path
    bf::path temp_path = dir_path;

    // Create output
    std::vector<std::string> output;

    // Check dirpath
    if( bf::exists(temp_path) == false ){
        temp_path = temp_path.parent_path();
    }
    if( bf::exists(temp_path) == false ){
        return output;
    }

    // Create the directory iterators
    bf::directory_iterator it(temp_path);
    for( ; it != bf::directory_iterator(); it++ )
    {
        // Get the path
        output.push_back( it->path().native() );

    }

    // return output
    return output;
}


} // End of FS  Namespace
} // End of CLI Namespace
