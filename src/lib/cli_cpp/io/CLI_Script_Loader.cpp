/**
 * @file    CLI_Script_Loader.cpp
 * @author  Marvin Smith
 * @date    6/30/2015
*/
#include "CLI_Script_Loader.hpp"

// Boost Filesystem 
#include <boost/filesystem.hpp>

// C++ Standard Libraries
#include <fstream>
#include <iostream>

// CLI Libraries
#include "../utility/String_Utilities.hpp"

namespace bf=boost::filesystem;

namespace CLI{
namespace IO{


/**********************************/
/*       Load a CLI Script        */
/**********************************/
std::deque<std::string> Load_CLI_Script( const std::string& script_path )
{
    // Make sure file exists
    if( bf::exists(bf::path(script_path)) == false ){
        return std::deque<std::string>();
    }

    // Create output
    std::deque<std::string> output;
    std::string line;

    // Open file
    std::ifstream fin;
    fin.open( script_path.c_str() );
    
    // Get the line
    std::getline( fin, line );

    while( fin.good() && !fin.eof() ){

        // Add the line
        line = UTILS::String_Trim(line);
        if( line.size() > 0 ){
            output.push_back(line);
        }

        // Get the data
        std::getline( fin, line );

    }


    // Close file
    fin.close();

    // Return data
    return output;
}

} // End of IO  Namespace
} // End of CLI Namespace

