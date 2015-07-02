/**
 * @file    Telnet_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/1/2015
*/
#include "Telnet_Utilities.hpp"

// CLI Libraries
#include "System_Utilities.hpp"


// C++ Standard Libraries
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>


namespace CLI{
namespace UTILS{
namespace TELNET{

/*********************************************************/
/*         Convert Telnet Input to Pretty Format         */
/*********************************************************/
std::string Telnet_To_Pretty_String( const std::string& str )
{
    // Create output
    std::string output;

    // Iterate over characters
    for( size_t i=0; i<str.size(); i++ ){

        // Check next char
        if( str[i] == IAC ){
            output += "IAC ";
        }
        else if( str[i] == WILL ){
            output += "WILL ";
        }
        else if( str[i] == WONT ){
            output += "WONT ";
        }
        else if( str[i] == DO ){
            output += "DO ";
        }
        else if( str[i] == DONT ){
            output += "DONT ";
        }
        else if( str[i] == term_size ){
            output += " term_size";
        }

        else if( str[i] == term_type ){
            output += " term_type";
        }
        
        else if( str[i] == SB ){
            output += " SB";
        }
        else if( str[i] == SE ){
            output += " SE";
        }
        else{
            output += str[i];
        }
    }
    return output;

}

/***********************************************************/
/*          Create Telnet Get Window Size Command          */
/***********************************************************/
void Telnet_Get_Window_Size( const int& fd )
{


}

} // End of TELNET Namespace
} // End of UTILS  Namespace
} // End of CLI    Namespace

