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
    /*
    std::cout << "START" << std::endl;

    int n;
    char* buffer = new char[2048];
    
    std::string iac_do_term_type;
    iac_do_term_type += IAC;
    iac_do_term_type += DO;
    iac_do_term_type += term_type;
    
    std::string iac_get_term_type;
    iac_get_term_type += (char)IAC;
    iac_get_term_type += (char)SB;
    iac_get_term_type += (char)term_type;
    iac_get_term_type += (char)IAC;
    iac_get_term_type += (char)SE;

    std::string iac_result_01, iac_result_02;

    // Write to the socket
    std::cout << "Writing" << std::endl;
    write( fd, iac_do_term_type.c_str(), iac_do_term_type.size());

    // Get the result
    n = read( fd, buffer, 2048);
    iac_result_01 = std::string(buffer).substr(0,n);

    std::cout << "Initial Result: " << Telnet_To_Pretty_String(iac_result_01) << std::endl;
    for( int i=0; i<iac_result_01.size(); i++ ){
        std::cout << i << " : " << (int)iac_result_01[i] << std::endl;
    }
    
    // Write again
    std::cout << "Writing Output" << std::endl;
    write(fd, iac_get_term_type.c_str(), iac_get_term_type.size());
    
    // get the next result
    std::cout << "Reading Next" << std::endl;
    n = read( fd, buffer, 2048);
    iac_result_02 = std::string(buffer).substr(0,n);
    
    std::cout << "Next Result: " << Telnet_To_Pretty_String(iac_result_02) << std::endl;
    for( int i=0; i<iac_result_02.size(); i++ ){
        std::cout << i << " : " << (int)iac_result_02[i] << std::endl;
    }

    std::cout << "END" << std::endl;
    // Delete buffer
    delete [] buffer;
    */

    struct winsize ts;
    if( ioctl(fd, TIOCGSIZE, &ts) < 0 ){
        std::cout << "Unable to get term window size" << std::endl;
    }
    else{
        std::cout << "Line: " << ts.ws_row << std::endl;
        std::cout << "Cols: " << ts.ws_col << std::endl;
    }

}

} // End of UTILS Namespace
} // End of CLI   Namespace

