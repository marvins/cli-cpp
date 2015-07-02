/**
 * @file    Telnet_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/1/2015
*/
#include "Telnet_Utilities.hpp"

// CLI Libraries
#include "System_Utilities.hpp"


// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace UTILS{

/***********************************************************/
/*          Create Telnet Get Window Size Command          */
/***********************************************************/
std::string Create_Telnet_Window_Size_Command()
{
    std::string output;

    char* data = getenv("LINES");
    if( data != NULL ){
        std::cout << getenv("LINES") << std::endl;
    }
    else{
        std::cout << "INVALID" << std::endl;
    }

    return output;
}

} // End of UTILS Namespace
} // End of CLI   Namespace

